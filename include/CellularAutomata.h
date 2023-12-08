#pragma once

#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <numeric>
#include <utility>
#include <vector>

#include "Cell.h"
#include "myrandom.h"

// Define the allowed types of boundaries
enum Boundary { walled, periodic, none };

/********************************************
 *     Main Cellular Automata Class         *
 *******************************************/

/**
 * @brief CellularAutomata class
 * This is the main class that holds a grid of cells and provides functionality
 * to get cells by their indices, neighbors, etc and mutate their state
 *
 * @tparam CellType Type of cell to use. Should inherit from the Cell baseclass
 */
template <typename CellType>
class CA {
 private:
  const int x_size_;
  const int y_size_;
  std::vector<std::vector<std::shared_ptr<CellType>>> grid_;
  Boundary boundary_;
  bool csv_output_ = false;
  std::string csv_filename_;

 public:
  // Basic constructor, initializes each cell to the "void" state
  CA(int x_size, int y_size, Boundary boundary_type)
      : x_size_(x_size), y_size_(y_size), boundary_(boundary_type) {
    // Grid init
    grid_.reserve(x_size_);
    for (int x = 0; x < x_size_; x++) {
      std::vector<std::shared_ptr<CellType>> row;
      row.reserve(y_size_);
      for (int y = 0; y < y_size_; y++) {
        // auto cell = std::make_shared<CellType>();
        // cell -> setVoidState();
        // row.push_back(cell);
        row.push_back(std::make_shared<CellType>());
      }
      grid_.push_back(row);
    }
  }

  // // Constructor that also takes in an initial state for all cells
  // CA(int x_size, int y_size, Boundary boundary_type, StateType state)
  //     : x_size_(x_size), y_size_(y_size), boundary_(boundary_type) {
  //   // Grid init
  //   grid_.reserve(x_size_);
  //   for (int x = 0; x < x_size_; x++) {
  //     std::vector<std::shared_ptr<CellType>> row;
  //     row.reserve(y_size_);
  //     for (int y = 0; y < y_size_; y++) {
  //       row.push_back(std::make_shared<CellType>(state));
  //     }
  //     grid_.push_back(row);
  //   }
  // }

  inline int getX() { return x_size_; }

  inline int getY() { return y_size_; }

  /*******************
   * Methods for Getting
   * and indexing Cells
   * *******************/

  // Initialization function that iterates through every
  // cell and changes it to its "default" initialization state
  // with a given probability probd
  void randomInit(double prob) {
    for (int x = 0; x < x_size_; x++) {
      for (int y = 0; y < y_size_; y++) {
        double rand = random_double(0, 1);
        // std::cout << "Rand is: " << rand << std::endl;
        if (rand < prob) {
          getCell(x, y)->setDefaultState();
        }
      }
    }
  }

  // Cell indexing
  inline std::shared_ptr<CellType> getCell(const int x, const int y) {
    return grid_.at(x).at(y);
  }

  inline bool insideBoundary(const int x, const int y) const {
    if (boundary_ == periodic) {
      return true;
    }
    return (x >= 0 && x < x_size_ && y >= 0 && y < y_size_);
  }

  inline bool atBoundary(const int x, const int y) const {
    if (boundary_ == periodic) {
      return false;
    } else if ((x == x_size_ - 1 || x == 0 || y == 0 || y == y_size_ - 1) &&
               insideBoundary(x, y)) {
      return true;
    }

    return false;
  }

  // not sure this is the best way,
  // but didn't want to have 4 separate logic functions
  // bc in my tinkering I kept forgetting to switch the - to + etc
  std::shared_ptr<CellType> getRelativeCell(const int x,
                                            const int y,
                                            const int Dx,
                                            const int Dy) {
    int newx = x + Dx;
    int newy = y + Dy;

    switch (boundary_) {
      case walled:
      case none:
        if (insideBoundary(newx, newy)) {
          return getCell(newx, newy);
        }
        break;

      case periodic:
        return getCell(((newx % x_size_) + x_size_) % x_size_,
                       ((newy % y_size_) + y_size_ % y_size_));
        break;
    }

    return nullptr;
  }

  // Moore Neighborhood (includes diagonals)
  std::vector<std::shared_ptr<CellType>>
  getMooreNeighborhood(const int x, const int y, const int radius = 1) {
    std::vector<std::shared_ptr<CellType>> neighbors;

    // Can anticipate the number of neighbors by the radius
    neighbors.reserve(radius * 8);

    switch (boundary_) {
      case walled:
      case none:
        // Sweep from x - radius -> x + radius
        for (int i = x - radius; i < x + radius + 1; i++) {
          // Sweep from y - radius -> y + radius
          for (int j = y - radius; j < y + radius + 1; j++) {
            if (insideBoundary(i, j)) {
              neighbors.push_back(getCell(i, j));
            }
          }
        }
        break;

      case periodic:
        // Sweep from x - radius -> x + radius
        for (int i = 0; i < radius + 1; i++) {
          // Sweep from y - radius -> y + radius
          for (int j = 0; j < radius + 1; j++) {
            neighbors.push_back(getRelativeCell(x, y, i, j));
          }
        }
        break;
    }

    return neighbors;
  }

  std::vector<std::shared_ptr<CellType>>
  getVNNeighborhood(const int x, const int y, const int radius = 1) {
    // First get the Moore neighborhood with radius -1
    auto neighbors = getMooreNeighborhood(x, y, radius - 1);

    // Then fill out the outer edges (not including diagonal)
    auto right = getRelativeCell(x, y, radius, 0);
    if (right != nullptr) {
      neighbors.push_back(right);
    }

    auto left = getRelativeCell(x, y, -radius, 0);
    if (left != nullptr) {
      neighbors.push_back(left);
    }

    auto up = getRelativeCell(x, y, 0, radius);
    if (up != nullptr) {
      neighbors.push_back(up);
    }

    auto down = getRelativeCell(x, y, 0, -radius);
    if (down != nullptr) {
      neighbors.push_back(down);
    }

    return neighbors;
  }

  /**********************
   * Run and update cells
   *********************/

  void updateAll() {
    for (int x = 0; x < x_size_; x++) {
      for (int y = 0; y < y_size_; y++) {
        getCell(x, y)->update();
      }
    }
  }

  void run(const int iterations,
           const std::function<void(CA<CellType>&)> update_func) {
    // For i iterations
    for (int i = 0; i < iterations; i++) {
      // Call our update_func_
      // on ourselves
      //
      // this will mutate in-place all the cells
      // and update them to their new state
      update_func(*this);

      // Once we have computed the new
      // states, push all changes
      updateAll();
      if (csv_output_)
        writeToCSV();
    }
  }

  /**********************
   *   Printing State
   *********************/

  void print() const {
    for (int x = 0; x < x_size_; x++) {
      for (int y = 0; y < y_size_; y++) {
        std::cout << std::left << std::setw(4) << getCell(x, y)->getState()
                  << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

  void enableCSV(std::string filename) {
    csv_output_ = true;
    csv_filename_ = filename;
    std::ofstream file(csv_filename_, std::ofstream::trunc);

    if (file.is_open()) {
      file << x_size_ << ',' << y_size_ << std::endl;
    } else {
      std::cerr << "Unable to open file for writing headers: " << csv_filename_
                << std::endl;
    }
  }

  void disableCSV() { csv_output_ = false; }

  void writeToCSV() {
    std::ofstream file(csv_filename_, std::ofstream::app);
    if (file.is_open()) {
      for (int x = 0; x < x_size_; x++) {
        for (int y = 0; y < y_size_; y++) {
          file << getCell(x, y)->getState();
          if (y < y_size_ - 1)
            file << ",";
        }
        file << std::endl;
      }
      file << std::endl;
    } else {
      std::cerr << "Unable to open file for appending data: " << csv_filename_
                << std::endl;
    }
  }
};
