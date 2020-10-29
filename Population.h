#ifndef POPULATION_H
#define POPULATION_H

#include "Bot.h"
#include "Position.h"

#include <string>
#include <vector>
#include <future>

using namespace std;

class Population {
    int quantity;
    int boardSize;
    bool allFinished;
    string **board;
    Bot **dirBots;
    int generation;

    public:
        Population(int quantity, int boardSize,string **board);
        void start();
        string toString();
        void sortPopulation();
        void reproduce();
        void iterate();

        Bot* mergeBots(Bot *b1, Bot *b2, int id);
        Bot* getBest();

};

#endif