// Chem 274B: Software Engineering Fundamentals for
//            Molecular Sciences 
// Creator: Cameron Hu
//
//  C++ functions for rando number generation

#include "myrandom.h"

// function: set_rseed sets the seed of C pseudo random number 
//           geneator.
//    input: random_type is the type of value to use to set
//           the random key (types are defined in myrandom.h)
//   output: no output 
//          returns RAND_ERR_SEEDTYPE if seed type is not defined
//          returns RAND_NO_ERR if successfully sets the random seed
void set_rseed( int random_type ){
    if (random_type == GEN_FIXED_RSEED)   //rseed = FIXED_RSEED
        srand(FIXED_RSEED);
    else if (random_type == GEN_NEW_RSEED) // rseed = random value
        srand(time(NULL));
}

std::default_random_engine re;

/*! Generate a random double within a given range */
double random_double(double lower_bound, double upper_bound)
{
    std::uniform_real_distribution<double> dist(lower_bound, upper_bound);
    return dist(re);
}