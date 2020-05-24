#include "Position.h"

#include <sstream>

using namespace std;

Position::Position()
{
    i = -1;
    j = -1;
    direction = -1;
}

Position::Position(int _i, int _j)
{
    i = _i;
    j = _j;
    direction = 0;
}


Position::Position(int _i, int _j, int _direction)
{
    i = _i;
    j = _j;
    direction = _direction;
}

void Position::setI(int newI)
{
    i = newI;
}

void Position::setJ(int newJ)
{
    j = newJ;
}

int Position::getI()
{
    return i;
}

int Position::getJ()
{
    return j;
}

string Position::toString()
{
    std::stringstream ss;
    ss << "\n(i,j, direction) = (" << i << "," << j << "," << direction <<  ")\n";
    return ss.str();
}

bool Position::isAnInvalidPosition()
{
    return i == -1 || j == -1;
}

void Position::setDirection(int _direction) 
{
    direction = _direction;
}

int Position::getDirection() 
{
    return direction;
}

string Position::getDirectionName() 
{
    if (direction == -1) {
        return "emtpy";
    }

    if (direction == 0) {
        return "initial";
    }

    return DIRECTION_NAMES[direction];
}

string Position::getTextToPrint() 
{
    std::stringstream ss;
    ss << "{\"i\":" << i << ",\"j\":" << j << "}";
    return ss.str();
}