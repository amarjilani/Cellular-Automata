#pragma once

#include <vector>
#include <functional>
#include <utility>
#include <iostream>
#include <numeric>
#include <memory>
#include <iomanip>

#include "Cell.h"


// Define the allowed types of boundaries
enum Boundary {walled, periodic, none};



/********************************************
 *     Main Cellular Automata Class         *
 *******************************************/

/**
 * @brief CellularAutomata class
 * This is the main class that holds a grid of cells and provides functionality to
 * get cells by their indices, neighbors, etc and mutate their state
 *
 * @tparam CellType Type of cell to use. Should inherit from the Cell baseclass
 */
template< typename CellType>
class CA {
 private:
  int x_size_;
  int y_size_;
  std::vector<std::vector<std::shared_ptr<CellType>>> grid_;
  Boundary boundary_;

public:

    // Basic constructor
    CA(int x_size, int y_size, Boundary boundary_type)
    :   x_size_(x_size), 
        y_size_(y_size), 
        boundary_(boundary_type)
        //grid_(x_size, std::vector<CellType>(y_size)) 

    {

        // nested vector in initilalizer list is being weird, doing by hand
        // with shared pts to each cell 
        // that way we can modify them in place 
        grid_.reserve(x_size_);
        for (int x=0; x < x_size_; x++){
            
            std::vector<std::shared_ptr<CellType>> row;
            row.reserve(y_size_);
            for (int y=0; y < y_size_; y++){
                row.push_back(std::make_shared<CellType>(0));
            }
            grid_.push_back(row);
        }


        // Maybe set the default state for all cells here?
        // or maybe make that a separate method?

        // for now, lets just set the point 1, 1 to have a state of 1 since that would work for bool, int, float
        getCell(4, 4)->setNextState(1);
        getCell(4,4)->update();
    }


    int getX(){
        return x_size_;
    }

    int getY(){
        return y_size_;
    }


    /*******************
    * Methods for Getting
    * and indexing Cells
    * *******************/

    // Cell indexing
    std::shared_ptr<CellType> getCell(int x, int y){
        return grid_.at(x).at(y);
    }

    // Moore Neighborhood (includes diagonals)
    std::vector<std::shared_ptr<CellType>> getMooreNeighborhood(int x, int y, int radius=1){


        std::vector<std::shared_ptr<CellType>> neighbors;
        neighbors.reserve(radius * 8);

        // Depending on which boundary type
        // our CA has, need to get neighbors differently
        switch(boundary_){

            case none:
                // Can anticipate the number of neighbors by the radius
                // Sweep from x - radius -> x + radius
                for (int i=x - radius; i < x + radius + 1; i ++){
                    // Sweep from y - radius -> y + radius
                    for (int j = y - radius; j < y + radius + 1; j ++){

                        // Only look for cell if it is in the 
                        // bounds of our grid
                        if(0 <= i && i < x_size_ && 0 <= j && j < y_size_){
                            neighbors.push_back(getCell(i, j));
                        }
                    }
                }
                break;

            case walled:
                std::cout << "Im not implemented yet :(" << std::endl;
                break;

            case periodic:
                std::cout<< "Im not implemented yet :(" << std::endl;
                break;
        }

        return neighbors;
    }


    /**********************
    * Run and update cells
    *********************/

    void updateAll(){
      for (int x = 0; x < x_size_; x++) {
        for (int y = 0; y < y_size_; y++) {
 
                getCell(x, y)->update();
            }
        }
    }

    void run(int iterations, std::function<void(CA<CellType>&)> update_func){


        // For i iterations
        for (int i=0; i < iterations; i ++){


            // Call our update_func_
            // on ourselves
            //
            // this will mutate in-place all the cells
            // and update them to their new state
            update_func(*this);

            // Once we have computed the new
            // states, push all changes
            updateAll();
        }

    }

    void print() {
      for (int x = 0; x < x_size_; x++) {
        for (int y = 0; y < y_size_; y++) {
          std::cout << std::left << std::setw(4) << getCell(x, y)->getState() << " ";
        }

        std::cout << std::endl;
      }
      std::cout << std::endl;
    }



};


