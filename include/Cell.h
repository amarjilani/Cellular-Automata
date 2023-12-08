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
  void setVoidState(){}
  void setDefaultState(){}
  
  Cell(){setVoidState();}
  Cell(StateType initial_state) : current_state_(initial_state) {}

  // State interface
  StateType getState() { return current_state_; }

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
 * 0 = Road cell, no car. Everything = 0
 * 1 = Stopped means velocity = 0, no acceleration
 * 2 = Constant means no acceleration, constant velocity > 0
 * 3 = FlatTire means velocity, acceleration = 0, flatCount > 0
*/

// enum CarStates {Stopped, Constant, Accelerating, Braking, OnFire};

/**
 * @brief CarCell class, contains a Cell<CarStates> object
*/
class CarCell : public Cell<int> {

    private:
        int velocity_;
        int acc_;
        bool road_;
        bool flat_;
        int flatCount_;

    public:

        // Default constructor
        CarCell() 
        : velocity_(0), acc_(0), road_(true), flat_(false), flatCount_(0) 
        {current_state_ = 0;}

        // Constructor that takes in velocity, acceleration
        CarCell(int velocity) 
        : velocity_(velocity), acc_(0), road_(false), flat_(false), flatCount_(0)
        {current_state_ = 2;}

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
        // std::string model() const {
        //     return model_;
        // }

        // Road boolean getter/setter function
        bool& road() {
            return road_;
        }

        // Const Road boolean getter function
        bool road() const {
            return road_;
        }

        // Flat boolean getter/setter function
        bool& flat() {
            return flat_;
        }

        // FlatCount int getter/setter function
        int& flatCount() {
            return flatCount_;
        }

        /***********************
        * State Related Methods
        ************************/

       /**
        * Method to give the car a flat tire
        * Sets state to 3, velocity to 0, flat_ to true, and flatCount to 3
        */
       void makeFlat() {
            // Check that there exists a car
            if (current_state_ == 0) {
                throw std::invalid_argument("No car exists at this cell!");
            }

            // Check that the car doesn't already have a flat
            if (current_state_ == 3) {
                throw std::invalid_argument("Car already has a flat tire");
            }

            current_state_ = 3;
            velocity_ = 0;
            flat_ = true;
            flatCount_ = 3;
       }


       /**
        * For a car with a flat tire, decrement the flat tire counter
        * If the flatCount reaches 0, set velocity = 1 and restore
        * the Car's state to be driving (2)
        */
       void flatCountDecrement() {
            // Check that there exists a car
            if (current_state_ == 0) {
                throw std::invalid_argument("No car exists at this cell!");
            }

            // Check that the car has a flatTire
            if ( (flat_ != true) || (current_state_ != 3) ) {
                throw std::invalid_argument("flatCountDecrement can only be called on a car with a flat tire");
            }

            // Decrement flatCount
            flatCount_--;

            // If flatCount = 0, restore the car to a normal driving car
            if (flatCount_ == 0) {
                flat_ = false;
                velocity_ = 1;
                current_state_ = 2;
            }
       }

        // Set state default function. Sets the current cell to 2 (Driving)
        void setDefaultState() {
            current_state_ = 2;
            velocity_ = 1;
            road_ = false;
            flat_ = false;
            flatCount_ = 0;
        }

        // Set state void function. Sets the current cell to 0 (Road cell)
        void setVoidState() {
            current_state_ = 0;
            velocity_ = 0;
            road_ = true;
            flat_ = false;
            flatCount_ = 0;
        }
};
