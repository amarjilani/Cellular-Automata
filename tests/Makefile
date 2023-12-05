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
CPPFLAGS    = -g -O0

# The directory where the include files needed to create the library objects are
INC_DIR = ../include

# The bin directory to put exes
BIN_DIR = ../bin

ALLTESTS = test_simple test_walled_boundary test_none_boundary test_periodic_boundary

test_simple: test_simple.cpp $(INC_DIR)/Cell.h $(INC_DIR)/CellularAutomata.h
	$(CPP) $(CPPFLAGS) test_simple.cpp -o $(BIN_DIR)/test_simple -I$(INC_DIR)

test_simple_valgrind: test_simple
	valgrind --leak-check=yes ../bin/test_simple

test_walled_boundary: test_walled_boundary.cpp $(INC_DIR)/Cell.h $(INC_DIR)/CellularAutomata.h
	$(CPP) $(CPPFLAGS) test_walled_boundary.cpp -o $(BIN_DIR)/test_walled_boundary -I$(INC_DIR)

test_none_boundary: test_none_boundary.cpp $(INC_DIR)/Cell.h $(INC_DIR)/CellularAutomata.h
	$(CPP) $(CPPFLAGS) test_none_boundary.cpp -o $(BIN_DIR)/test_none_boundary -I$(INC_DIR)

test_periodic_boundary: test_periodic_boundary.cpp $(INC_DIR)/Cell.h $(INC_DIR)/CellularAutomata.h
	$(CPP) $(CPPFLAGS) test_periodic_boundary.cpp -o $(BIN_DIR)/test_periodic_boundary -I$(INC_DIR)


make all: $(ALLTESTS)
