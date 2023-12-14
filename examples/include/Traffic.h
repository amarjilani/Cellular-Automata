#include "CarCell.h"
#include "CellularAutomata.h"

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


void trafficUpdateChangeLanes(CA<CarCell>& ca) {
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
        } else if (!cell->flat() && ca.getRelativeCell(row, col, 1, 0)->road()){
          DEBUG_MSG("Car in front, but lane below is free!");
          auto next_cell = ca.getRelativeCell(row, col, 1, 0);
          next_cell->setNextDefaultState();

          cell->setNextVoidState();
        } else if (!cell->flat() && ca.getRelativeCell(row, col, -1, 0)->road()){
          DEBUG_MSG("Car in front, but lane above is free!");
          auto next_cell = ca.getRelativeCell(row, col, -1, 0);
          next_cell->setNextDefaultState();

          cell->setNextVoidState();

        } else {
          DEBUG_MSG("can't move at all, car in front!");
        }

        DEBUG_MSG(std::endl << std::endl);
      }
    }
  }
}



