# Chem 274B: Software Engineering Fundamentals for
#            Molecular Sciences
#
# Creator:  Tony Drummond, PhD.  Faculty
# Date Created: September, 2022
# Date Updated: September 22, 2023
#
# Directory Path: Assignment2/Source/Datatypes
# This makefile creates objects and a library from OO Classes that
# implement Data structures. Here is an example of archiving object
# files (see DATA_OBJS) into a library object file (DATA_LIB)

# GNU C++ Compiler
CPP         = g++      # C++ Compuler

# compiler flags -g debug, -O2 optimized version -c create a library object
CPPFLAGS    = -O3

# The directory where the include files needed to create the library objects are
INC_DIR = ../include

# The bin directory to put exes
BIN_DIR = ../bin


simple_test: simple_test.cpp $(INC_DIR)/Cell.h $(INC_DIR)/CellularAutomata.h
	$(CPP) simple_test.cpp -o $(BIN_DIR)/simple_test -I$(INC_DIR)
