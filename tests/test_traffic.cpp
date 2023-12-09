#include <iostream>
#include "Cell.h"
#include "CellularAutomata.h"

void trafficUpdate(CA<CarCell>& ca) {
  for (int x = 0; x < ca.getX(); x++) {
    for (int y = 0; y < ca.getY(); y++) {
      auto cell = ca.getCell(x, y);

      if (!cell->road()) {
        // Handle flats
        if (cell->flat()) {
          cell->flatCountDecrement();
        } else if (rand() % 100 == 0) {
          cell->makeFlat();
        }

        // check how far in front we are allowed to move
        int dx;
        for (dx = 1; dx <= cell->velocity(); dx++) {
          auto cell_in_front = ca.getRelativeCell(x, y, dx, 0);

          if (!cell_in_front->road()) {
            cell->velocity() = cell_in_front->velocity();
            dx--;  // stop at the cell *before* this one
            break;
          }
        }

        // If we are allowed to move, set new cell
        if (dx > 0 && !cell->flat()) {
          auto next_cell = ca.getRelativeCell(x, y, dx, 0);
          next_cell->road() = false;
          next_cell->velocity() = cell->velocity();

          cell->setVoidState();
        }
      }
    }
  }
}

std::function<void(CA<CarCell>&)> trafficUpdateFunc = trafficUpdate;

int main() {
  Boundary boundary_type = periodic;

  CA<CarCell> ca(100, 3, boundary_type);

  // Set ~10% of cells to have cars
  ca.randomInit(0.1);

  // Set the output
  ca.enableCSV("test_traffic.csv");

  // Run some iterations!
  ca.run(10, trafficUpdateFunc);

  return 0;
}
