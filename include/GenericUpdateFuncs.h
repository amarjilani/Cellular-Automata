#pragma once

#include "CellularAutomata.h"

template <typename T>
void majorityRuleVN(CA<T>& ca) {
  // For each cell, set state as the majority of
  // the VN Neighborhood, radius = 1
  for (int row = 0; row < ca.getRows(); row++) {
    for (int col = 0; col < ca.getCols(); col++) {
      auto cell = ca.getCell(row, col);

      auto neighbors = ca.getVNNeighborhood(row, col);
      int sum = 0;
      for (auto n : neighbors) {
        sum += n->getState();
      }

      float avg =
          static_cast<float>(sum) / static_cast<float>(neighbors.length());
      if (avg > 0.5) {
        cell->setNextState(1);
      } else {
        cell->setNextState(0);
      }
    }
  }
}

template <typename T>
void majorityRuleMoore(CA<T>& ca) {
  // For each cell, set state as the majority of
  // the Moore Neighborhood, radius = 1
  for (int row = 0; row < ca.getRows(); row++) {
    for (int col = 0; col < ca.getCols(); col++) {
      auto cell = ca.getCell(row, col);

      auto neighbors = ca.getMooreNeighborhood(row, col);
      int sum = 0;
      for (auto n : neighbors) {
        sum += n->getState();
      }

      float avg =
          static_cast<float>(sum) / static_cast<float>(neighbors.length());
      if (avg > 0.5) {
        cell->setNextState(1);
      } else {
        cell->setNextState(0);
      }
    }
  }
}

template <typename T>
void conditionalTransitionRuleVN(CA<T>& ca) {
  // For each cell, if any cell in its neighborhood
  // is state 1, set it's state to 1
  for (int row = 0; row < ca.getRows(); row++) {
    for (int col = 0; col < ca.getCols(); col++) {
      auto cell = ca.getCell(row, col);

      bool updated = false;
      auto neighbors = ca.getVNNeighborhood(row, col);
      for (auto n : neighbors) {
        if (n->getState() == 1) {
          cell->setNextState(1);
          updated = true;
          break;
        }
      }

      if (!updated) {
        cell->setNextState(0);
      }
    }
  }
}

template <typename T>
void conditionalTransitionRuleMoore(CA<T>& ca) {
  // For each cell, if any cell in its neighborhood
  // is state 1, set it's state to 1
  for (int row = 0; row < ca.getRows(); row++) {
    for (int col = 0; col < ca.getCols(); col++) {
      auto cell = ca.getCell(row, col);

      bool updated = false;
      auto neighbors = ca.getMooreNeighborhood(row, col);
      for (auto n : neighbors) {
        if (n->getState() == 1) {
          cell->setNextState(1);
          updated = true;
          break;
        }
      }

      if (!updated) {
        cell->setNextState(0);
      }
    }
  }
}

template <typename T>
void straightCOnditionalTransitionRule(CA<T>& ca) {
  // Simply increment state by 1 if state > 0
  for (int row = 0; row < ca.getRows(); row++) {
    for (int col = 0; col < ca.getCols(); col++) {
      auto cell = ca.getCell(row, col);

      if (cell->getState() > 0) {
        cell->setNextState(cell->getState() + 1);
      } else {
        cell->setNextState(0);
      }
    }
  }
}
