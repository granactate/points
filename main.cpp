#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Bot.h"
#include "Position.h"
#include "Population.h"
#include "Random.h"
#include "GenomeMixer.h"
#include "FileWriter.h"

using namespace std;


string printArray(string array[], int size)
{
    if (size == 0)
    {
        return "Empty Array";
    }

    std::stringstream ss;
    int i;

    for (i = 0; i < size; i++)
    {
        ss << array[i];
        if (i < size - 1)
        {
            ss << ",";
        }
    }

    ss << endl;
    return ss.str();
}

string **getBoard(int m, int n)
{
    string **board = new string *[m];
    int i;
    int j;

    for (i = 0; i < m; i++)
    {
        board[i] = new string[n];
        for (j = 0; j < n; j++)
        {
            if(i == 0 || j == 0 || i == m -1 || j == n -1) {
                *(*(board + i) + j)  = "#";
            } else {
                *(*(board + i) + j)  = " ";
            }
        }
    }

    return board;
}

void testMergeDNA() {
    Position **dna1 = new Position *[25];
    Position **dna2 = new Position *[25];

    string **tmp  = getBoard( 5,  5);
    for (int i = 0; i < 5; i++) {
        for(int j = 0 ; j < 5; j++) {
            cout << *(*(tmp + i) + j) << " ";
        }
        cout << endl;
    }


    *(dna1 + 0) = new Position(1,1, 0);
    *(dna1 + 1) = new Position(1,2, Position::RIGHT);
    *(dna1 + 2) = new Position(1,3, Position::RIGHT);
    *(dna1 + 3) = new Position(2,3, Position::BOTTOM);
    *(dna1 + 4) = new Position(-1,-1, Position::RIGHT);
    for(int i = 5; i < 25; i++) {
        *(dna1 + i) = new Position();
    }

    *(dna2 + 0) = new Position(2,2, 0);
    *(dna2 + 1) = new Position(3,2, Position::BOTTOM);
    *(dna2 + 2) = new Position(3,3, Position::RIGHT);
    *(dna2 + 3) = new Position(-1,-1, Position::RIGHT);
    for(int i = 4; i < 25; i++) {
        *(dna2 + i) = new Position();
    }


    Bot *b1 = new Bot(tmp, 3, dna1, 1);
    Bot *b2 = new Bot(tmp, 3, dna2, 2);

    GenomeMixer gm = GenomeMixer();
    Position **newDNA = gm.mergeListDNA(b1, b2, 25);

    for(int i = 0; i < 25; i++) {
        Position *p = *(newDNA + i);
        if(i == 0) {
            cout << (*p).toString();
        } else if ((*p).getDirection() != -1){
            cout << (*p).getDirectionName() << " ";
        }
        
    }

    cout << endl;
}

int main()
{   
    int boardSize = 20;
    string **board  = getBoard( boardSize,  boardSize);

    int i ;
    int populationSize = 2000;
    Population population = Population(populationSize, boardSize, board);
    population.start();
    cout << "Population Initialized" << endl;
    
    for(int i=0; i< 100; i++) {
        population.iterate();
        cout << "Iteration #" << i + 1 << endl;
    }    

    return 0;
}