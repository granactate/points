#ifndef POSITION_H
#define POSITION_H

#include <string>

using namespace std;

class Position
{
    private:
        int i;
        int j;

        /*
        * direction explain the direction from the move if this apply initially will be 0, the possible values that this will take are:
        * 1. left
        * 2. right
        * 3. above
        * 4. bottom
        */
        int direction;


    protected:
        const string DIRECTION_NAMES[5] = {"","L", "R", "A", "B"};

    public:
        Position();
        Position(int currentI, int currentJ);
        Position(int currentI, int currentJ, int _direction);

        string toString();
        bool isAnInvalidPosition();

        void setI(int i);
        int getI();

        void setJ(int j);
        int getJ();

        void setDirection(int direction);
        int getDirection();
        string getDirectionName();

        string getTextToPrint();

        static const int LEFT = 1;
        static const int RIGHT = 2;
        static const int ABOVE = 3;
        static const int BOTTOM = 4;
        static const int UNDEFINED = -1;


};


#endif