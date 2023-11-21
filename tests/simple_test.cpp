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

  // test we can make a cell
  MyCell c;

  // print state
  std::cout << c.getState() << std::endl;

  // put next state
  c.setNextState(2);
  // print state
  std::cout << c.getState() << std::endl;

  // actually call updaet
  c.update();

  // print state
  std::cout << c.getState() << std::endl;

  // Make a CA with 10, 10 grid, no boundary stuff, basic update function
  // that sums all states in neighborhood
  //
  //
  //  constructor will make cell 1,1 start at 1, otherwise the cells
  //  will all be 0
  MyCA ca(10, 10, boundary_type);

  // print out cell states
  ca.print();

  // run 1 iteration
  ca.run(1, update_func);

  // print out cell states
  ca.print();

  // run 1 more iterations
  ca.run(1, update_func);

  // print out cell states
  ca.print();

  // run 10 more iterations
  ca.run(3, update_func);

  // print out cell states
  ca.print();

  return 0;
}
