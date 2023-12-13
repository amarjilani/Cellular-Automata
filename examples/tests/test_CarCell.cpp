#include <iostream>

#include "CarCell.h"
#include "CellularAutomata.h"

int main() {
  CarCell c;
  CarCell c1(10);

  Boundary boundary_type = none;
  CA<CarCell> ca(10, 10, none);

  std::cout << "Num X is " << ca.getX() << std::endl;
  std::cout << "Num Y is " << ca.getY() << std::endl;

  double prob = 1;
  ca.randomInit(prob);
  ca.print();

  CA<CarCell> ca1(10, 10, none);
  prob = 0.1;
  ca1.randomInit(prob);
  ca1.print();

  for (int i = 0; i < ca1.getX(); i++) {
    for (int j = 0; j < ca1.getY(); j++) {
      auto cellPtr = ca1.getCell(i, j);
      if (!cellPtr->road()) {
        std::cout << "Cell at (" << i << ", " << j
                  << ") is a car with velocity ";
        std::cout << cellPtr->velocity() << std::endl;
        ;
      }
    }
  }

  std::cout << std::endl;

  // Get first cell and make it a driving car
  auto cellPtr = ca1.getCell(0, 0);
  cellPtr->setState(1);
  cellPtr->makeFlat();
  cellPtr->update();
  ca1.print();

  std::cout << std::endl;
  cellPtr->flatCountDecrement();
  cellPtr->flatCountDecrement();
  cellPtr->flatCountDecrement();
  cellPtr->update();
  ca1.print();

  cellPtr->update();
  ca1.print();
  try {
    cellPtr->flatCountDecrement();
  } catch (std::invalid_argument) {
    std::cout << "Decrementing non flat tire errored properly" << std::endl;
  }

  return 0;
}
