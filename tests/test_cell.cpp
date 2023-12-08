#include <iostream>

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
      if ( ! cellPtr->isRoad() ) {
        std::cout << "Cell at (" << i << ", " << j << ") is a car with velocity ";
        std::cout << cellPtr->velocity() << std::endl;; 
      }
    }
  }

  return 0;
}