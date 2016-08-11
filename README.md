# accumulate
In the sample, I try the C++11 thread facilities by accumulating a very 
large size of vector by using <code>std::packaged_task</code>, <code>std::async</code>, and raw 
method.

The following tables shows the time elapse of 10 runs of the sample.
This program accumulate the vector of integer of the size 134 million.
As shown in the table, <code>std::packaged_task</code> is better than 
<code>std::async</code> and <code>std::async</code> is better than the 
raw method.
<table>
  <tr>
    <th></th>
    <th>raw method (ms)</th>
    <th>std::packaged_task (ms)</th>
    <th>std::async (ms)</th>
  </tr>
  <tr>
    <td>1</td>
    <td>85.061</td>
    <td>57.541</td>
    <td>74.553</td>
  </tr>
  <tr>
    <td>2</td>
    <td>90.564</td>
    <td>57.541</td>
    <td>62.545</td>
  </tr>
  <tr>
    <td>3</td>
    <td>89.564</td>
    <td>48.535</td>
    <td>63.544</td>
  </tr>
  <tr>
    <td>4</td>
    <td>87.563</td>
    <td>49.535</td>
    <td>61.544</td>
  </tr>
  <tr>
    <td>5</td>
    <td>88.063</td>
    <td>50.035</td>
    <td>62.544</td>
  </tr>
  <tr>
    <td>6</td>
    <td>80.558</td>
    <td>50.536</td>
    <td>62.544</td>
  </tr>
  <tr>
    <td>7</td>
    <td>85.061</td>
    <td>57.540</td>
    <td>75.552</td>
  </tr>
  <tr>
    <td>8</td>
    <td>89.064</td>
    <td>50.535</td>
    <td>63.046</td>
  </tr>
  <tr>
    <td>9</td>
    <td>89.564</td>
    <td>48.534</td>
    <td>62.544</td>
  </tr>
  <tr>
    <td>10</td>
    <td>87.062</td>
    <td>50.036</td>
    <td>63.045</td>
  </tr>
  <tr>
    <td>AVG</td>
    <td>87.212</td>
    <td>52.037</td>
    <td>65.146</td>
</table>
