#include <iostream>

#include "CarCell.h"
#include "CellularAutomata.h"
#include "Traffic.h"

int main() {
  Boundary boundary_type = periodic;

  int rows;
  int cols;
  std::cout << "Number of rows:";
  std::cin >> rows;
  std::cout << "Number of columns:";
  std::cin >> cols;

  CA<CarCell> ca(rows, cols, boundary_type);

  float prob;
  std::cout << "Probability of cell being a car:";
  std::cin >> prob;
  ca.randomInit(prob);

  std::string csv;
  std::cout << "Output file:";
  std::cin >> csv;
  ca.enableCSV(csv);

  int iter;
  std::cout << "Iterations to run:";
  std::cin >> iter;

  ca.run(iter, trafficUpdateChangeLanesPlusSpeed);

  return 0;
}
