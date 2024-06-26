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
INC_DIR = ../../include
EX_INC_DIR = ../include

# The bin directory to put exes
EX_BIN_DIR = ../bin

# The Lib directory 
LIB_DIR = ../../lib

###################################################################################

ALLTESTS = test_CarCell test_traffic test_traffic_change_lanes test_traffic_change_lanes_speed test_forest_fire

###################################################################################

test_CarCell: test_CarCell.cpp $(INC_DIR)/Cell.h $(INC_DIR)/CellularAutomata.h $(EX_INC_DIR)/CarCell.h
	$(CPP) $(CPPFLAGS) test_traffic.cpp -o $(EX_BIN_DIR)/test_traffic -I$(INC_DIR) -I$(EX_INC_DIR) -L$(LIB_DIR) -lmyrandom

test_traffic: test_traffic.cpp $(INC_DIR)/Cell.h $(INC_DIR)/CellularAutomata.h $(EX_INC_DIR)/CarCell.h $(EX_INC_DIR)/Traffic.h
	$(CPP) $(CPPFLAGS) test_traffic.cpp -o $(EX_BIN_DIR)/test_traffic -I$(INC_DIR) -I$(EX_INC_DIR) -L$(LIB_DIR) -lmyrandom

test_traffic_change_lanes: test_traffic_change_lanes.cpp $(INC_DIR)/Cell.h $(INC_DIR)/CellularAutomata.h $(EX_INC_DIR)/CarCell.h $(EX_INC_DIR)/Traffic.h
	$(CPP) $(CPPFLAGS) test_traffic_change_lanes.cpp -o $(EX_BIN_DIR)/test_traffic_change_lanes -I$(INC_DIR) -I$(EX_INC_DIR) -L$(LIB_DIR) -lmyrandom

test_traffic_change_lanes_speed: test_traffic_change_lanes_speed.cpp $(INC_DIR)/Cell.h $(INC_DIR)/CellularAutomata.h $(EX_INC_DIR)/CarCell.h $(EX_INC_DIR)/Traffic.h
	$(CPP) $(CPPFLAGS) test_traffic_change_lanes_speed.cpp -o $(EX_BIN_DIR)/test_traffic_change_lanes_speed -I$(INC_DIR) -I$(EX_INC_DIR) -L$(LIB_DIR) -lmyrandom

test_forest_fire: test_forest_fire.cpp $(INC_DIR)/Cell.h $(INC_DIR)/CellularAutomata.h
	$(CPP) $(CPPFLAGS) test_forest_fire.cpp -o $(EX_BIN_DIR)/test_forest_fire -I$(INC_DIR) -I$(EX_INC_DIR) -L$(LIB_DIR) -lmyrandom

make all: $(ALLTESTS)

cleanall:
	cd ${EX_BIN_DIR}; rm ${ALLTESTS}
