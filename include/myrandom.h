#include <random> // for random numbers

// LIST OF FLAGS AND SYMBOLS:
// Predefined value for seed of the C pseudo random 
// number generator.  
#define FIXED_RSEED  123

// Possible integer values for random_type, which 
// sets or resets the C pseudo random number generator
// if random_type=1, uses FIXED_RSEED to set the rseed
// if random_type=2, uses the system time to randomly set
//                   rseed
#define GEN_FIXED_RSEED    1
#define GEN_NEW_RSEED      2

// LIST OF FUNCTIONS AND AVAILABLE FUNCTIONALITIES:
// function: set_rseed sets the seed of C pseudo random number 
//           geneator.
//    input: random_type is the type of value to use to set
//           the random key (types are defined in myrandom.h)
//   output: no output 
//   When a invalid random_type is passed, it returns error -4
void set_rseed( int random_type );

/*! Generate a random double within a given range */
double random_double(double lower_bound, double upper_bound);