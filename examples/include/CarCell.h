#pragma once

#include "Cell.h"

/**
 * @brief CarStates
 * Contains the possible states a CarCell
 * 0 = Road cell, no car. Everything = 0
 * 1 = Stopped means velocity = 0
 * 2 = Constant means moving, constant velocity > 0
 * 3 = FlatTire means velocity = 0, flatCount > 0
 */

// enum CarStates {Stopped, Constant, Accelerating, Braking, OnFire};

/**
 * @brief CarCell class, contains a Cell<CarStates> object
 */
class CarCell : public Cell<int> {
 private:
  int velocity_;
  int flatCount_;
  int next_velocity_;
  int next_flatCount_;

 public:
  // Default constructor
  CarCell() { current_state_ = 0; }

  // Constructor that takes in velocity
  CarCell(int velocity) : velocity_(velocity), flatCount_(0) {
    current_state_ = 2;
  }

  // Getter/setter function for next velocity
  int& next_velocity() { return next_velocity_; }

  // Const getter function for velocity
  int velocity() const { return velocity_; }

  // // Road boolean getter/setter function
  // bool& road() { return road_; }
  bool road() const { return (current_state_ == 0); }

  // // Const Road boolean getter function
  // bool road() const { return road_; }

  // // Flat boolean getter/setter function
  // bool& flat() { return flat_; }
  bool flat() const { return (current_state_ == 3); }

  // next_FlatCount int getter/setter function
  int& next_flatCount() { return next_flatCount_; }

  int flatCount() const { return flatCount_; }
  //

  // Getter/setter function for acceleration
  // int& acceleration() { return acc_; }

  // Const getter function for acceleration
  // int acceleration() const { return acc_; }

  // Const getter function for model
  // std::string model() const {
  //     return model_;
  // }

  /***********************
   * State Related Methods
   ************************/

  /**
   * Update Method: updates current_state_ to be the stored next_state
   * and updates the attributes of the CarCell based off
   * the value of next_state_. If no next_state_ is defined, next_state_
   * is always defaulted to be 0: road cell
   */
  void update() {
    current_state_ = next_state_;
    velocity_ = next_velocity_;
    flatCount_ = next_flatCount_;
  }

  /**
   * Method to give the car a flat tire
   * Sets state to 3, velocity to 0, flat_ to true, and flatCount to 3
   */
  void makeFlat() {
    // Check that there exists a car
    if (road()) {
      throw std::invalid_argument("No car exists at this cell!");
    }

    // Check that the car doesn't already have a flat
    if (flat()) {
      throw std::invalid_argument("Car already has a flat tire");
    }

    next_state_ = 3;
    next_velocity_ = 0;
    next_flatCount_ = 3;
  }

  /**
   * For a car with a flat tire, decrement the flat tire counter
   * If the flatCount reaches 0, set velocity = 1 and restore
   * the Car's state to be driving (2)
   */
  void flatCountDecrement() {
    // Check that there exists a car
    if (road()) {
      throw std::invalid_argument("No car exists at this cell!");
    }

    // Check that the car has a flatTire
    // if ((flat_ != true) || (current_state_ != 3)) {
    if (!flat()) {
      throw std::invalid_argument(
          "flatCountDecrement can only be called on a car with a flat tire");
    }

    // Decrement flatCount
    next_flatCount_--;

    // If flatCount = 0, restore the car to a normal driving car next turn
    if (next_flatCount_ == 0) {
      setNextDefaultState();
    }
  }

  // Set state default function: set's the cell's current attributes. Sets the
  // current cell to 2 (Driving)
  void setDefaultState() {
    current_state_ = 2;
    velocity_ = 1;
    flatCount_ = 0;
  }

  // Sets the current cell's next state to be the Default state (driving)
  void setNextDefaultState() {
    next_state_ = 2;
    next_velocity_ = 1;
    next_flatCount_ = 0;
  }

  // Set state void function: set's the cell's current attributes. Sets the
  // current cell to 0 (Road cell)
  void setVoidState() {
    current_state_ = 0;
    velocity_ = 0;
    flatCount_ = 0;
  }

  // Sets the current cell's next state to be the Void state (road)
  void setNextVoidState() {
    next_state_ = 0;
    next_velocity_ = 0;
    next_flatCount_ = 0;
  }
};
