/*
 * Code from here: https://www.learncpp.com/cpp-tutorial/59-random-number-generation/ 
 */

#include "random.h"

namespace MyRandom {
	// Initialize our mersenne twister with a random seed based on the clock (once at system startup)
	std::mt19937 mersenne(static_cast<std::mt19937::result_type>(std::time(nullptr)));
}

int coinFlip() {
	std::uniform_int_distribution<> die(0, 1);
        return die(MyRandom::mersenne);
}

double generateRandomProb() {
    std::uniform_real_distribution<> dis(0,1);
    return dis(MyRandom::mersenne);
}