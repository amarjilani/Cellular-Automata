# /Tests README

University of California, Berkeley  
Chem 274B: Software Engineering Fundamentals for Molecular Sciences  
December 2023  
Creator:  Patrick Neal, Amar Jilani, Cameron Hu  
Date Created: December 2023  
Directory Path: /tests

The tests directory for the general purpose CA library.
Contains tests for the generic library functionality, including boundary conditions
and CSV outputting.

## LIST OF SUBDIRECTORIES IN THIS DIRECTORY

- None
  
## LIST OF FILES IN THIS DIRECTORY

- README - this file
- Makefile - contains useful make targets for compiling the test source code into binary executables
- test_csv.cpp - Tests the CSV outputting of the CA
- test_none_boundary.cpp - Tests the none boundary condition of the CA
- test_periodic_boundary.cpp - Tests the periodic boundary conditions of the CA
- test_walled_boundary.cpp - Tests the walled boundary conditions of the CA
- test_simple.cpp - Tests a simple example of a CA generated from this library