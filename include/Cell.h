#pragma once
#include <string>

/**
 * @brief Cell baseclass. 
 * This is the most basic cell in a Cellular Automata: it has a single state attribute of the given template type.
 * All other cell should inherit from this base class
 *
 * @tparam StateType Type for the state value
 */
template <typename StateType>
class Cell {
 protected:
  StateType current_state_;
  StateType next_state_;

 public:
  Cell(){current_state_=0;}
  Cell(StateType initial_state) : current_state_(initial_state) {}

  // State interface
  StateType getState() { return current_state_; }

  void defaultSetState() {
    current_state_ = 1;
    }
  void setNextState(StateType new_state) {
        next_state_ = new_state; 
    }
  void update() {
        current_state_ = next_state_; 
    }
};


/**
 * @brief CarStates
 * Contains the possible states a CarCell
 * 0 = Stopped means velocity = 0, no acceleration
 * 1 = Constant means no acceleration, constant velocity > 0
 * 2 = Acceleratiing means acceleration > 0
 * 3 = Braking means acceleration < 0
 * 4 = OnFire means velocity and acceleration = 0 and cannot be changed
*/

// enum CarStates {Stopped, Constant, Accelerating, Braking, OnFire};

/**
 * @brief CarCell class, contains a Cell<CarStates> object
*/
class CarCell : public Cell<int> {

    private:
        int velocity_;
        int acc_;
        const std::string model_;

    public:

        // Default constructor
        CarCell() : velocity_(0), acc_(0), model_("Unknown") {current_state_ = 0;}

        // Constructor that only takes in a state
        CarCell(int initial_state) {current_state_ = initial_state;}

        // Constructor that takes in velocity, acceleration
        CarCell(int velocity, int acc) 
        : velocity_(velocity), acc_(acc), model_("Unknown")
        {current_state_ = 0;}

        // Constructor that takes in velocity, acceleration, and model
        CarCell(int velocity, int acc, std::string model) 
        : velocity_(velocity), acc_(acc), model_(model)
        {current_state_ = 0;}

        // Getter/setter function for velocity
        int& velocity() {
            return velocity_;
        }

        // Const getter function for velocity
        int velocity() const {
            return velocity_;
        }

        // Getter/setter function for acceleration
        int& acceleration() {
            return acc_;
        }

        // Const getter function for acceleration
        int acceleration() const {
            return acc_;
        }

        // Const getter function for model
        std::string model() const {
            return model_;
        }

        // Set state default function. Sets the current cell to constant (Driving)
        void defaultSetState() {
            current_state_ = 1; 
        }
};
