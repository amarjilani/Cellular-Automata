#pragma once

#include <unordered_map>
#include <algorithm>
#include "CellularAutomata.h"

/**
 * @brief Cell takes on the most common state of it's Vonn Neuman neighbors
 *
 * @tparam T Type of the state
 * @param[CA type] ca CellularAutomata to modify
 * @param [state type] states to exclude from update
 * @param radius the size of the neighborhood
 */
template <typename T>
void majorityRuleVN(CA<Cell<T>>& ca, std::vector<T> exclude={}, int radius=1) {

  std::unordered_map<T, int> state_counts;

  for (int row = 0; row < ca.getRows(); row++) {
    for (int col = 0; col < ca.getCols(); col++) {
      auto cell = ca.getCell(row, col);
      T current_state = cell->getState();

      // Dont touch anything in the exclude list
      if (std::find(exclude.begin(), exclude.end(), current_state) == exclude.end()) {
        continue;
      }

      auto neighbors = ca.getVNNeighborhood(row, col, radius);
      int sum = 0;
      for (auto n : neighbors) {
        state_counts[n->getState()] += 1;
      }

      T mode;
      int mode_count = 0;
      for (auto it : state_counts) {
        if (it->second > mode_count) {
          mode = it->first;
          mode_count = it->second;
        }
      }
      cell->setNextState(mode);
      state_counts.clear();
    }
  }
}

/**
 * @brief Cell takes on the most common state of it's More neighbors
 *
 * @tparam T Type of the state
 * @param[CA type] ca CellularAutomata to modify
 * @param [state type] states to exclude from update
 * @param radius the size of the neighborhood
 */
template <typename T>
void majorityRuleMoore(CA<Cell<T>>& ca, std::vector<T> exclude={}, int radius=1) {
  std::unordered_map<T, int> state_counts;

  for (int row = 0; row < ca.getRows(); row++) {
    for (int col = 0; col < ca.getCols(); col++) {
      auto cell = ca.getCell(row, col);
      T current_state = cell->getState();

      // Dont touch anything in the exclude list
      if (std::find(exclude.begin(), exclude.end(), current_state) == exclude.end()) {
        continue;
      }

      auto neighbors = ca.getMooreNeighborhood(row, col, radius);
      int sum = 0;
      for (auto n : neighbors) {
        state_counts[n->getState()] += 1;
      }

      T mode;
      int mode_count = 0;
      for (auto it : state_counts) {
        if (it->second > mode_count) {
          mode = it->first;
          mode_count = it->second;
        }
      }
      cell->setNextState(mode);
      state_counts.clear();
    }
  }
}


/**
 * @brief If cell's current state == start_state at time T, update to end_state for time T+1
 *
 * @tparam T state type
 * @param[CA type] ca CellularAutomata to modify
 * @param[state type] start_state state at T
 * @param[state type] end_state state at time T+1
 */
template <typename T>
void conditionalTransitionRule(CA<Cell<T>>& ca, T start_state, T end_state) {
  for (int row = 0; row < ca.getRows(); row++) {
    for (int col = 0; col < ca.getCols(); col++) {
      auto cell = ca.getCell(row, col);
      T current_state = cell->getState();

      if (current_state == start_state) {
        cell->setNextState(end_state);
      }
    }
  }
}

/**
 * @brief If cell's current state == start_state at time T, update to end_state for time T+1
 *
 * @tparam T state type
 * @param[CA type] ca CellularAutomata to modify
 * @param[map of start_state type: end_state type] transform a mapping of start_state to end_states.
 */
template <typename T>
void conditionalTransitionRule(CA<Cell<T>>& ca, std::unordered_map<T, T> transform) {
  for (int row = 0; row < ca.getRows(); row++) {
    for (int col = 0; col < ca.getCols(); col++) {
      auto cell = ca.getCell(row, col);

      cell->setNextState(transform[cell->getState()]);

    }
  }
}


/**
 * @brief If any Vonn Neuman neighbor of the current cell matches the trigger_state at time T, set this cell to new_state for time T+1
 *
 * @tparam T state type
 * @param[CA type] ca CellularAutomata to modify
 * @param[state type] trigger_state state to trigger the change
 * @param[state type] new_state the new state at T+1
 * @param [state type] states to exclude from update
 * @param radius the size of the neighborhood
 */
template <typename T>
void conditionalTransitionRuleVN(CA<Cell<T>>& ca, T trigger_state, T new_state, std::vector<T> exclude={}, int radius=1) {
  for (int row = 0; row < ca.getRows(); row++) {
    for (int col = 0; col < ca.getCols(); col++) {
      auto cell = ca.getCell(row, col);
      T current_state = cell->getState();

      // Dont touch anything in the exclude list
      if (std::find(exclude.begin(), exclude.end(), current_state) == exclude.end()) {
        continue;
      }

      auto neighbors = ca.getVNNeighborhood(row, col, radius);
      for (auto n : neighbors) {
        if (n->getState() == trigger_state) {
          cell->setNextState(new_state);
          break;
        }
      }
    }
  }
}


/**
 * @brief If any Moore neighbor of the current cell matches the trigger_state at time T, set this cell to new_state for time T+1
 *
 * @tparam T state type
 * @param[CA type] ca CellularAutomata to modify
 * @param[state type] trigger_state state to trigger the change
 * @param[state type] new_state the new state at T+1
 * @param [state type] states to exclude from update
 * @param radius the size of the neighborhood
 */
template <typename T>
void conditionalTransitionRuleMoore(CA<Cell<T>>& ca, T trigger_state, T new_state, std::vector<T> exclude={}, int radius=1) {
  for (int row = 0; row < ca.getRows(); row++) {
    for (int col = 0; col < ca.getCols(); col++) {
      auto cell = ca.getCell(row, col);
      T current_state = cell->getState();

      // Dont touch anything in the exclude list
      if (std::find(exclude.begin(), exclude.end(), current_state) != exclude.end()) {
        continue;
      }

      auto neighbors = ca.getMooreNeighborhood(row, col, radius);
      for (auto n : neighbors) {
        if (n->getState() == trigger_state) {
          cell->setNextState(new_state);
          break;
        }
      }
    }
  }
}

