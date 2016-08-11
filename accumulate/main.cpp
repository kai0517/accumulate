// This sample compares the performance of accumulate a very large vector by
// using std::packaged_task, std::async, and raw method.
#include <iostream>
#include <vector>
#include <numeric>
#include <future>
#include <random>

template <typename T>
inline T accum(T const* beg, T const* end, T init)
{
    return std::accumulate(beg, end, init);
}

template <typename T>
inline T simple_accum(std::vector<T> const& v)
{
    return std::accumulate(v.begin(), v.end(), T());
}

template <typename T>
T accum_use_packaged_task(std::vector<T> const& v)
{
    using Task_type = T(T const*, T const*, T);

    std::packaged_task<Task_type> pt0 {accum<T>};
    std::packaged_task<Task_type> pt1 {accum<T>};

    std::future<T> f0 {pt0.get_future()};
    std::future<T> f1 {pt1.get_future()};

    auto beg = &v[0];
    auto sz  = v.size();

    std::thread t1 {std::move(pt0), beg,      beg+sz/2, T()};
    std::thread t2 {std::move(pt1), beg+sz/2, beg+sz,   T()};
    
    t1.join();
    t2.join();

    return f0.get()+f1.get();
}

template <typename T>
T accum_use_async(std::vector<T>& v)
{
    auto beg = &v[0];
    auto sz  = v.size();
    if (sz<10000)
    {
        return accum(beg, beg+sz, T());
    }

    auto f0 = std::async(accum<T>, beg,        beg+sz/4,   T());
    auto f1 = std::async(accum<T>, beg+sz/4,   beg+sz/2,   T());
    auto f2 = std::async(accum<T>, beg+sz/2,   beg+sz*3/4, T());
    auto f3 = std::async(accum<T>, beg+sz*3/4, beg+sz,     T());

    return f0.get()+f1.get()+f2.get()+f3.get();
}

int main()
{
    std::vector<unsigned int> v;
    
    auto die = std::bind(std::uniform_int_distribution<>{1, 2147483647}, 
        std::default_random_engine{});

    for (int i=0; i<134000000; ++i)
    {
        v.push_back(die());
    }

    // Simply calling std::accumulate for whole vector
    auto start = std::chrono::high_resolution_clock::now();
    
    std::cout << "The result using simple accumulate is " 
              << simple_accum(v) << std::endl;
    auto end = std::chrono::high_resolution_clock::now();
   
    std::cout << "simple_accum takes " 
              << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() 
              << " microseconds" << std::endl;

    // Divide the vector into 4 sections and accumute the portion 
    // by using 2 different threads and std::packaged_task 
    start = std::chrono::high_resolution_clock::now();

    std::cout << "\nThe result using packaged_task is " 
              << accum_use_packaged_task(v) << std::endl;

    end = std::chrono::high_resolution_clock::now();
    
    std::cout << "use_packaged_task takes "
              << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() 
              << " microseconds" << std::endl;

    // Divide the vector into 4 sections and accumute the portion 
    // by using 4 different threads and std::async
    start = std::chrono::high_resolution_clock::now();
    
    std::cout << "\nThe result using packaged_task is " 
              << accum_use_async(v) << std::endl;
    
    end = std::chrono::high_resolution_clock::now();
    
    std::cout << "use_async takes " 
              << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() 
              << " microseconds" << std::endl;
}
