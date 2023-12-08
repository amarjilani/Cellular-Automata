/*
Simple test of CSV output functionality
*/
#include <iostream>

#include "CellularAutomata.h"

typedef Cell<int> MyCell;
typedef CA<MyCell> MyCA;

void basic_update(MyCA& ca) {
  // Loop over all cells
  for (int x = 0; x < ca.getX(); x++) {
    for (int y = 0; y < ca.getY(); y++) {
      auto cell = ca.getCell(x, y);

      // Get neighbors
      auto neighbors = ca.getMooreNeighborhood(x, y);

      int sum = 0;
      for (auto n : neighbors) {
        sum += n->getState();
      }

      // Limit the state to 100
      if (sum > 100) {
        sum = 100;
      }

      cell->setNextState(sum);
    }
  }
}

std::function<void(MyCA&)> update_func = basic_update;

int main() {
  Boundary boundary_type = none;

  MyCA ca(10, 10, boundary_type);

  // enables writing to output 
  ca.enableCSV("test.csv"); 

  // run for 10 iterations 
  for (int i = 0; i < 10; i++) {
    ca.run(1, update_func); 
  }

  // test disable functionality 
  ca.disableCSV();

  // should not appear in the csv file 
  for (int i = 0; i < 10; i++) {
    ca.run(1, update_func); 
  }

  return 0;
}
