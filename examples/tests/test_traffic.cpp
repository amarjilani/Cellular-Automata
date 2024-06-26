#define DEBUG 1

#include <cassert>

#include "CarCell.h"
#include "CellularAutomata.h"
#include "Traffic.h"

int main() {
  Boundary boundary_type = periodic;
  CA<CarCell> ca(3, 10, boundary_type);

  ca.enableCSV("test_traffic.csv");

  // Put single car at 0,0 and check that it moves correctly
  ca.getCell(0, 0)->setDefaultState();

  // Run single iteration, expect car to now be at 1, 0
  ca.run(1, trafficUpdate);
  assert(ca.getCell(0, 0)->road());
  assert(!ca.getCell(0, 1)->road());

  // After 9 more iterations, with periodic boundary
  // should return to 0, 0
  ca.run(9, trafficUpdate);
  assert(!ca.getCell(0, 0)->road());

  // No other cells should have non-zero states
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 10; col++) {
      if (row == 0 && col == 0) {
        continue;
      } else {
        assert(ca.getCell(row, col)->getState() == 0);
      }
    }
  }

  // Test flat tire
  ca.getCell(0, 0)->makeFlat();
  ca.getCell(0, 0)->update();

  ca.run(1, trafficUpdate);
  assert(ca.getCell(0, 0)->getState() == 3);
  // No other cells should have non-zero states
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 10; col++) {
      if (row == 0 && col == 0) {
        continue;
      } else {
        assert(ca.getCell(row, col)->getState() == 0);
      }
    }
  }

  // Should remain flat for 3 iterations total
  ca.run(1, trafficUpdate);
  assert(ca.getCell(0, 0)->getState() == 3);
  ca.run(1, trafficUpdate);

  // On fourth iteration should move forward again
  ca.run(1, trafficUpdate);
  assert(ca.getCell(0, 0)->road());
  assert(!ca.getCell(0, 1)->road());

  // Test car stopping behind car with flat tire
  // put car with flat tire 1 space ahead
  // or car at 0, 1
  ca.getCell(0, 3)->setDefaultState();
  ca.getCell(0, 3)->makeFlat();
  ca.getCell(0, 3)->update();
  assert(ca.getCell(0, 3)->flatCount() == 3);

  ca.run(1, trafficUpdate);
  assert(!ca.getCell(0, 2)->road());
  assert(ca.getCell(0, 3)->flat());
  assert(ca.getCell(0, 3)->flatCount() == 2);

  ca.run(1, trafficUpdate);
  assert(!ca.getCell(0, 2)->road());
  assert(ca.getCell(0, 3)->flat());
  assert(ca.getCell(0, 3)->flatCount() == 1);
  assert(ca.getCell(0, 2)->velocity() == 0);

  ca.run(1, trafficUpdate);
  assert(!ca.getCell(0, 2)->road());
  assert(!ca.getCell(0, 3)->road());
  assert(ca.getCell(0, 2)->velocity() == 0);
  assert(ca.getCell(0, 3)->velocity() == 1);

  // Now the flat should be resolved
  // and the car in front should move next cycle
  ca.run(1, trafficUpdate);
  assert(!ca.getCell(0, 4)->road());
  assert(!ca.getCell(0, 2)->road());
  assert(ca.getCell(0, 3)->road());

  // Now that the space in front is open
  // car behind should start moving again
  ca.run(1, trafficUpdate);
  assert(ca.getCell(0, 2)->velocity() == 1);
  assert(!ca.getCell(0, 5)->road());

  ca.run(1, trafficUpdate);
  ca.run(1, trafficUpdate);

  std::cout << "ALL TESTS PASSED" << std::endl;
  return 0;
}
