#include <stdio.h>
#include <cstdlib>
#include <math.h>

// Returns a random exponentially distributed number with input average
double exp_rand(double avg) {
    // l is 1/avg (input)
    double l = 1 / avg;
    // explain
    //((double) rand() / (RAND_MAX+1)) * (max-min+1) + min
    double randnum = (double) rand() / ((double) RAND_MAX + 1);
    // Explain formula alteration with avg input
    //double exp_randnum = log(1 - randnum) / ((-1) * l);
    // ena apo ta 2
    double exp_randnum = log(1 - randnum) * ((-1) * avg);
    return exp_randnum;
}
