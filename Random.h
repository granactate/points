#ifndef RANDOM_H
#define RANDOM_H

using namespace std;

class Random {
    public: 
        Random();

        int number();
        int number(int min, int max);
};

#endif