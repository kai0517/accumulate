# Makefile to build the std::packaged_task and std::async sample using g++ with C++11 features
# Auther : Wen-Kai, Chang
#
CC=g++
DEBUGFLAGS=-g -std=c++11
RELEASEFLAGS=-std=c++11 -O3
SRCDIR=accumulate/
DEBUGDIR=./Debug/
RELEASEDIR=./Release/
DEBUGOBJS=$(DEBUGDIR)main.o
RELEASEOBJS=$(RELEASEDIR)main.o
OUTPUT=accumulate.out
MKDIR_P=mkdir -p

all : debug release

#####################
# Debug build
#####################

debug : debug_dir $(DEBUGDIR)$(OUTPUT)

debug_dir : $(DEBUGDIR)
	
$(DEBUGDIR) : 
	$(MKDIR_P) $(DEBUGDIR)

$(DEBUGDIR)$(OUTPUT) : $(DEBUGOBJS)
	$(CC) $(DEBUGFLAGS) $(DEBUGOBJS) -o $(DEBUGDIR)$(OUTPUT)

$(DEBUGDIR)main.o : $(SRCDIR)main.cpp
	$(CC) $(DEBUGFLAGS) -c $(SRCDIR)main.cpp -o $(DEBUGDIR)main.o

cleandebug :
	rm -rf $(DEBUGDIR)


#####################
# Release build
#####################

release : release_dir $(RELEASEDIR)$(OUTPUT)

release_dir : $(RELEASEDIR)

$(RELEASEDIR) : 
	$(MKDIR_P) $(RELEASEDIR)

$(RELEASEDIR)$(OUTPUT) : $(RELEASEOBJS)
	$(CC) $(RELEASEFLAGS) $(RELEASEOBJS) -o $(RELEASEDIR)$(OUTPUT)

$(RELEASEDIR)main.o : $(SRCDIR)main.cpp
	$(CC) $(RELEASEFLAGS) -c $(SRCDIR)main.cpp -o $(RELEASEDIR)main.o

cleanrelease :
	rm -rf $(RELEASEDIR)

clean : cleandebug cleanrelease
