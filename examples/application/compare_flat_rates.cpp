// #define FLATODDS 1000000
// #define FLATODDS 1000
// #define FLATODDS 100
// #define FLATODDS 50
// #define FLATODDS 10
#define FLATODDS 3

#include "CarCell.h"
#include "CellularAutomata.h"
#include "Traffic.h"

int main() {
  Boundary boundary_type = periodic;

  CA<CarCell> ca(3, 100, boundary_type);

  ca.getCell(1, 0)->setDefaultState();
  ca.getCell(1, 20)->setDefaultState();
  ca.getCell(1, 40)->setDefaultState();
  ca.getCell(1, 60)->setDefaultState();
  ca.getCell(1, 80)->setDefaultState();

  ca.enableCSV("compare_flat_rates.csv");

  ca.run(100, trafficUpdateChangeLanesPlusSpeedReport);

  return 0;
}
