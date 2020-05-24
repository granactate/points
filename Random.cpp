#include "Random.h"

#include <random>
#include <iostream>
using namespace std;

Random::Random() {}

int Random::number() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6);
    return dist6(rng);
}

int Random::number(int min, int max) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6);

    int counter = ( (max * 2) / 6 ) + 1;
    int total = 1;

    for(int i =0; i < counter; i++) {
        int value = (int) dist6(rng);
        int max = std::max(1, value);
        total += value;
    }

    int valueToReturn = total % ( max + 1 );

    if( valueToReturn < min) {
        return min;
    }
    
    return valueToReturn;
}