# Chem 274B: Software Engineering Fundamentals for
#            Molecular Sciences
#
# Creator:  Patrick Neal, Cameron Hu, Aamar Jilani
#
# Directory Path> 274B-Final/tests

# GNU C++ Compiler
CPP         = g++ -std=c++11      # C++ Compiler

# compiler flags -g debug, -O2 optimized version -c create a library object
CPPFLAGS    = -O3

# The directory where the include files needed to create the library objects are
INC_DIR = ../../include
EX_INC_DIR = ../include

# The bin directory to put exes
EX_BIN_DIR = ../bin

# The Lib directory 
LIB_DIR = ../../lib

###################################################################################

ALLAPPS = traffic_simulation compare_flat_rates

###################################################################################

traffic_simulation: traffic_simulation.cpp $(INC_DIR)/Cell.h $(INC_DIR)/CellularAutomata.h $(EX_INC_DIR)/CarCell.h $(EX_INC_DIR)/Traffic.h
	$(CPP) $(CPPFLAGS) traffic_simulation.cpp -o $(EX_BIN_DIR)/traffic_simulation -I$(INC_DIR) -I$(EX_INC_DIR) -L$(LIB_DIR) -lmyrandom

compare_flat_rates: compare_flat_rates.cpp $(INC_DIR)/Cell.h $(INC_DIR)/CellularAutomata.h $(EX_INC_DIR)/CarCell.h $(EX_INC_DIR)/Traffic.h
	$(CPP) $(CPPFLAGS) compare_flat_rates.cpp -o $(EX_BIN_DIR)/compare_flat_rates -I$(INC_DIR) -I$(EX_INC_DIR) -L$(LIB_DIR) -lmyrandom

make all: $(ALLAPPS)
