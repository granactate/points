#include "Bot.h"
#include "Position.h"
#include "Random.h"

#include <string>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <tuple>
#include "utils/HashTable.h"

using namespace std;

Bot::Bot()
{
    alive = true;
    size = 0;
    currentPosition = 0;
    dirDNA = new Position *[1];
    for (int i = 0; i < 1; i++)
    {
        *(dirDNA + i) = new Position();
    }
    id = -1;
    fatherId = -1;
    motherId = -1;
}

//https://www.youtube.com/watch?v=l_d-jZYLvx8&list=PLWtYZ2ejMVJlUu1rEHLC0i_oibctkl0Vh&index=89&ab_channel=Programaci%C3%B3nATS
Bot::Bot(string **currentboard, int _size, int _id)
{
    alive = true;
    board = currentboard;
    currentPosition = 0;
    size = _size;
    int total = size * size;
    dirDNA = new Position *[total];
    for (int i = 0; i < total; i++)
    {
        *(dirDNA + i) = new Position();
    }
    id = _id;
    fatherId = -1;
    motherId = -1;
};

Bot::Bot(string **currentboard, int currSize, Position **_dna, int _id)
{
    alive = true;
    board = currentboard;
    currentPosition = 0;
    size = currSize;
    dirDNA = _dna;
    id = _id;
    fatherId = -1;
    motherId = -1;
}

bool Bot::isAlive()
{
    return alive;
}

void Bot::setAlive(bool newValue)
{
    alive = newValue;
}

tuple<int, int, int> Bot::getNextMove()
{
    Random r = Random();
    int newMove = (r.number() % 4) + 1;

    int beforeIndex = currentPosition - 1;
    Position *before = *(dirDNA + beforeIndex);

    int newI = (*before).getI();
    int newJ = (*before).getJ();

    switch (newMove)
    {
        case 1:
        {
            newJ--;
        }
        break;

        case 2:
        {
            newJ++;
        }
        break;

        case 3:
        {
            newI--;
        }
        break;

        case 4:
        {
            newI++;
        }
        break;
    }

    return {newI, newJ, newMove};
}

Position *Bot::createRandomMove()
{
    Random r = Random();

    int i = r.number() % size;
    int j = r.number() % size;

    if (i == 0)
    {
        i++;
    }

    if (j == 0)
    {
        j++;
    }

    if (i == size - 1)
    {
        i--;
    }

    if (j == size - 1)
    {
        j--;
    }

    return new Position(i, j, 0);
}

void Bot::followDirection(Position *current)
{   
    int beforeIndex = currentPosition -1;
    Position *before = *(dirDNA + beforeIndex);
    int newI = (*before).getI();
    int newJ = (*before).getJ();

    switch ( (*current).getDirection() )
    {
        case 1:
        {
            newJ--;
        }
        break;

        case 2:
        {
            newJ++;
        }
        break;

        case 3:
        {
            newI--;
        }
        break;

        case 4:
        {
            newI++;
        }
        break;
    }

    if (*(*(board + newI) + newJ) == "#")
    {
        setAlive(false);
    }
    else
    {
        (*current).setI(newI);
        (*current).setJ(newJ);
    }
}

void Bot::move()
{
    if (!isAlive())
    {
        cout << "☠ This is a dead bot ☠" << endl;
        return;
    }

    if (currentPosition >= size * size)
    {
        setAlive(false);
        return;
    }

    Position *currentP = *(dirDNA + currentPosition);
    if ((*currentP).isAnInvalidPosition() && (*currentP).getDirection() == -1)
    {
        if (currentPosition == 0)
        {
            *(dirDNA + currentPosition) = createRandomMove();
        }
        else
        {
            int newI, newJ, newMove;
            tie(newI, newJ, newMove) = getNextMove();

            if (*(*(board + newI) + newJ) == "#")
            {
                setAlive(false);
            }
            else
            {
                *(dirDNA + currentPosition) = new Position(newI, newJ, newMove);
            }
        }
    }
    else if ((*currentP).isAnInvalidPosition() && (*currentP).getDirection() != 0)
    {   
        followDirection(currentP);
    }

    currentPosition++;
}

int Bot::getCurrentPosition()
{
    return currentPosition;
}

string Bot::printDNA()
{
    std::stringstream ss;

    int i;
    ss << "Bot " << id << " ::: " << endl;
    for (i = 0; i < currentPosition; i++)
    {
        Position *p = *(dirDNA + i);
        int direcction = (*p).getDirection();

        if (direcction == -1 || direcction == 0)
        {
            ss << "\t"
               << "(" << (*p).getI() << "," << (*p).getJ() << ")";
        }
        else
        {
            ss << " " << (*p).getDirectionName();
        }
    }

    ss << endl
       << endl;

    return ss.str();
}

Position *Bot::getDnaByPosition(int position)
{
    if (position >= size * size)
    {
        return new Position();
    }

    return *(dirDNA + position);
}

int Bot::getSizeDNA()
{
    return currentPosition;
}

Position **Bot::getDNA()
{
    return dirDNA;
}

string Bot::toString()
{
    std::stringstream ss;
    string m = alive ? "true" : "false";
    ss << "Bot {\n\t'id' :" << id << ","
       << "\n\t'alive' : " << m << ","
       << "\n\t'currentPosition' :" << currentPosition << ","
       << "\n\t'size' : " << size << "\n}"
       << endl;

    return ss.str();
}

int Bot::getId()
{
    return id;
}

void Bot::setFatherId(int id) 
{
    fatherId = id;
}

int Bot::getFatherId()
{
    return fatherId;
}

void Bot::setMotherId(int id )
{
    motherId = id;
}


int Bot::getMotherId()
{
    return motherId;
}

string Bot::getTextToPrint() {
    std::stringstream ss;

    ss << "{\"id\" :" << id << ", \"dna\": [";
    for( int i = 0; i < currentPosition; i++) 
    {
        Position *current = *(dirDNA + i);
        string  separator = (i != currentPosition - 1) ? "," : "";
        ss << (*current).getTextToPrint() << separator;
    }
    ss << "],\"fatherId\":" << fatherId << ",\"motherId\":" << motherId << "}";

    return ss.str();
}

/*
void Bot::calculateWeight() {
    HashTable table;
    
    for( int i = 0; i < currentPosition; i++) 
    {
        Position *current = *(dirDNA + i);
        table.addTuple(current->getI(), current->getJ());        
    }
}

*/