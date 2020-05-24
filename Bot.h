#ifndef BOT_H
#define BOT_H

#include "Position.h"
#include <string>
#include <tuple>

using namespace std;

class Bot {
    private:
        int id;
        bool alive;
        string **board;
        Position **dirDNA;
        int currentPosition;
        int size;
        tuple<int, int, int> getNextMove();
        void followDirection(Position *current);
        int fatherId;
        int motherId;

    public:
        Bot();
        Bot(string **board, int size, int id);
        Bot(string **board, int size, Position **_dna, int id);

        bool isAlive();        
        void setAlive(bool newAlive);
        int getCurrentPosition();
        void move();

        int getFatherId();
        void setFatherId(int id);

        int getMotherId();
        void setMotherId(int id);

        Position* getDnaByPosition(int position);
        Position** getDNA();

        int getSizeDNA();
        string printDNA();        
        string toString();
        int getId();
        string getTextToPrint();

        Position* createRandomMove();
};


#endif