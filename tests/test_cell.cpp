#include <iostream>

#include "CellularAutomata.h"

int main() {

  CarCell c;
  CarCell c1(1, 1);


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

  return 0;
}