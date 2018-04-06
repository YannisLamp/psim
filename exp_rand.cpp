#include <stdio.h>
#include <cstdlib>
#include <math.h>

// Returns a random exponentially distributed number with input average (rounded up)
int exp_rand(double avg) {
    // Generate a random number in [0, 1)
    double randnum = (double) rand() / ((double) RAND_MAX + 1.0);
    // Lambda is 1 / average and the formula for  a random
    // exponentially distributed number is
    // double exp_randnum = (-1) * log(1 - randnum) / lambda
    // and since the function input is the average,
    double exp_randnum = (-1) * log(1 - randnum) * avg;
    double for_round = exp_randnum + 0.5;
    int output = (int)for_round;
    return output;
}
