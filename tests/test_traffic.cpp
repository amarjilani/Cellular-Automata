#include <cassert>
#include <iostream>
#include "Cell.h"
#include "CellularAutomata.h"

#define DEBUG 0

#ifdef DEBUG
#define DEBUG_MSG(str)             \
  do {                             \
    std::cout << str << std::endl; \
  } while (false)
#define FLATODDS 10000000
#else
#define DEBUG_MSG(str) \
  do {                 \
  } while (false)
#endif

#ifndef FLATODDS
#define FLATODDS 100
#endif

void trafficUpdate(CA<CarCell>& ca) {
  for (int row = 0; row < ca.getRows(); row++) {
    for (int col = 0; col < ca.getCols(); col++) {
      auto cell = ca.getCell(row, col);

      if (!cell->road()) {
        // Handle flats
        if (cell->flat()) {
          cell->flatCountDecrement();
        } else if (rand() % FLATODDS == 0) {
          cell->makeFlat();
          continue;
        }

        // check how far in front we are allowed to move
        DEBUG_MSG("Checking space in front of " << row << ", " << col
                                                << std::endl);
        DEBUG_MSG("Current velocity is " << cell->velocity());
        int dcol;
        for (dcol = 1; dcol <= cell->velocity(); dcol++) {
          auto cell_in_front = ca.getRelativeCell(row, col, 0, dcol);

          if (!cell_in_front->road()) {
            DEBUG_MSG("space " << dcol << " in front is a car!");
            cell->next_velocity() = cell_in_front->velocity();
            DEBUG_MSG("setting next velocity to << "
                      << cell_in_front->velocity());
            dcol--;  // stop at the cell *before* this one
            break;
          } else {
            cell->next_velocity() = cell->velocity();
            DEBUG_MSG("space " << dcol << "in front is empty!");
          }
        }
        dcol--;

        DEBUG_MSG("Decided that we can move "
                  << dcol << " spaces forward and next velocity will be "
                  << cell->next_velocity());

        // If we are allowed to move, set new cell
        if (dcol > 0 && !cell->flat()) {
          DEBUG_MSG("We are allowed to move, so setting next state for cell at "
                    << row << ", " << col + dcol);
          auto next_cell = ca.getRelativeCell(row, col, 0, dcol);
          next_cell->setNextDefaultState();
          next_cell->next_velocity() = cell->velocity();

          cell->setNextVoidState();
        }
        // If there is no car in front, we are not flat, and velocity is zero
        // we can start moving again
        else if (!cell->flat() && cell->velocity() == 0 &&
                 ca.getRelativeCell(row, col, 0, 1)->road()) {
          DEBUG_MSG(
              "Wont move forward this iteration, but setting velocity "
              "back to normal for next");
          cell->setNextDefaultState();
        } else {
          DEBUG_MSG("can't move at all, car in front!");
        }

        DEBUG_MSG(std::endl << std::endl);
      }
    }
  }
}

std::function<void(CA<CarCell>&)> trafficUpdateFunc = trafficUpdate;

int main() {
  Boundary boundary_type = periodic;
  CA<CarCell> ca(3, 10, boundary_type);

  // Put single car at 0,0 and check that it moves correctly
  ca.getCell(0, 0)->setDefaultState();

  // Run single iteration, expect car to now be at 1, 0
  ca.run(1, trafficUpdateFunc);
  assert(ca.getCell(0, 0)->road());
  assert(!ca.getCell(0, 1)->road());

  // After 9 more iterations, with periodic boundary
  // should return to 0, 0
  ca.run(9, trafficUpdateFunc);
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

  ca.run(1, trafficUpdateFunc);
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
  ca.run(1, trafficUpdateFunc);
  assert(ca.getCell(0, 0)->getState() == 3);
  ca.run(1, trafficUpdateFunc);

  // On fourth iteration should move forward again
  ca.run(1, trafficUpdateFunc);
  assert(ca.getCell(0, 0)->road());
  assert(!ca.getCell(0, 1)->road());

  // Test car stopping behind car with flat tire
  // put car with flat tire 1 space ahead
  // or car at 0, 1
  ca.getCell(0, 3)->setDefaultState();
  ca.getCell(0, 3)->makeFlat();
  ca.getCell(0, 3)->update();

  ca.run(1, trafficUpdateFunc);
  assert(!ca.getCell(0, 2)->road());
  assert(ca.getCell(0, 3)->flat());

  ca.run(1, trafficUpdateFunc);
  assert(!ca.getCell(0, 2)->road());
  assert(ca.getCell(0, 3)->flat());
  assert(ca.getCell(0, 2)->velocity() == 0);

  ca.run(1, trafficUpdateFunc);
  assert(!ca.getCell(0, 2)->road());
  assert(!ca.getCell(0, 3)->road());
  assert(ca.getCell(0, 2)->velocity() == 0);
  assert(ca.getCell(0, 3)->velocity() == 1);

  // Now the flat should be resolved
  // and the car in front should move next cycle
  ca.run(1, trafficUpdateFunc);
  assert(!ca.getCell(0, 4)->road());
  assert(!ca.getCell(0, 2)->road());
  assert(ca.getCell(0, 3)->road());

  // Now that the space in front is open
  // car behind should start moving again
  ca.run(1, trafficUpdateFunc);
  assert(ca.getCell(0, 2)->velocity() == 1);
  assert(!ca.getCell(0, 5)->road());

  std::cout << "ALL TESTS PASSED" << std::endl;
  return 0;
}
