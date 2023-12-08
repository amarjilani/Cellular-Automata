# Chem 274B: Software Engineering Fundamentals for
#            Molecular Sciences
#
# Creator:  Patrick Neal, Cameron Hu, Aamar Jilani
#
# Directory Path> 274B-Final/tests

# GNU C++ Compiler
CPP         = g++ -std=c++11      # C++ Compiler

# compiler flags -g debug, -O2 optimized version -c create a library object
CPPFLAGS    = -g -O0

# The directory where the include files needed to create the library objects are
INC_DIR = ../include

# The bin directory to put exes
BIN_DIR = ../bin

ALLTESTS = test_simple test_walled_boundary test_none_boundary test_periodic_boundary test_csv test_cell

# The Lib directory 
LIB_DIR = ../lib

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

test_csv: test_csv.cpp $(INC_DIR)/Cell.h $(INC_DIR)/CellularAutomata.h
	$(CPP) $(CPPFLAGS) test_csv.cpp -o $(BIN_DIR)/test_csv -I$(INC_DIR)

test_cell: test_cell.cpp $(INC_DIR)/Cell.h $(INC_DIR)/CellularAutomata.h
	$(CPP) $(CPPFLAGS) test_cell.cpp -o $(BIN_DIR)/test_cell -I$(INC_DIR) -L$(LIB_DIR) -lmyrandom

make all: $(ALLTESTS)
