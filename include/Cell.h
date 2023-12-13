#pragma once

#include <stdexcept>
#include <string>

/**
 * @brief Cell baseclass.
 * This is the most basic cell in a Cellular Automata: it has a single state
 * attribute of the given template type. All other cell should inherit from this
 * base class
 *
 * @tparam StateType Type for the state value
 */
template <typename StateType>
class Cell {
 protected:
  StateType current_state_;
  StateType next_state_;

 public:
  void setVoidState() {}
  void setDefaultState() {}

  Cell() { setVoidState(); }
  Cell(StateType initial_state) : current_state_(initial_state) {}

  // State interface
  StateType getState() { return current_state_; }

  void setState(StateType new_state) { current_state_ = new_state; }
  void setNextState(StateType next_state) { next_state_ = next_state; }
  void update() { current_state_ = next_state_; }
};
