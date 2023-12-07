#pragma once

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
 private:
  StateType current_state_;
  StateType next_state_;

 public:
  Cell() { current_state_ = 0; }
  Cell(const StateType initial_state) : current_state_(initial_state) {}

  // State interface
  StateType getState() const { return current_state_; }
  void setNextState(StateType new_state) { next_state_ = new_state; }
  void update() { current_state_ = next_state_; }
};
