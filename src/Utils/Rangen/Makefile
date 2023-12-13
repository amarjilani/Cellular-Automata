# Chem 274B: Software Engineering Fundamentals for
#            Molecular Sciences 
# 
# Creator:  Tony Drummond, PhD.  Faculty
# Date Created: September, 2022
# Date Updated: September 22, 2023
#
# Directory Path: Assignment2/Utils/Rangen
#
# This makefile creates object files from 2 C++ source files that
# implement random functions. One of the files was already used in 
# Week 5, and the other file contains new C++ utility functions 
# useful for testing hash functions and tables. After compiling the
# source C++ program files, it creates a random generator library 
# (libmyrandom.a), which is relocated to Assignment2/Utils/Lib after 
# its successful creation.

# GNU C++ Compiler
CPP         = g++      

# compiler flags -g debug, -O3 optimized version -c create a library object file
CPPFLAGS    = -O3 -c    

# The directory where the include files needed to create the library objects are
INC_DIR = ../../../include

# The directory where the library object file will be moved to
LIB_DIR = ../../../lib

# The next line contains the list of random generating utilities object 
# files created with this Makefile 
RANDOM_OBJS = myrandomfs.o

MYRANDOM_LIB = libmyrandom.a

myrandomfs.o: $(INC_DIR)/myrandom.h
	$(CPP) $(CPPFLAGS) myrandomfs.cpp -I$(INC_DIR)

libmyrandom.a: $(RANDOM_OBJS)
	ar -ru $(MYRANDOM_LIB) $(RANDOM_OBJS)
	mv $(MYRANDOM_LIB) $(LIB_DIR)/.
	rm $(RANDOM_OBJS)

all: $(MYRANDOM_LIB)

cleanall:
	cd $(LIB_DIR); rm $(MYRANDOM_LIB)
