#include "Population.h"
#include "Position.h"
#include "Random.h"
#include "GenomeMixer.h"
#include "FileWriter.h"

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

Population::Population(int size, int _boardSize, string **_board)
{
    quantity = size;
    board = _board;
    dirBots = new Bot *[size];
    boardSize = _boardSize;

    for (int i = 0; i < quantity; i++)
    {
        Bot *b = new Bot(board, boardSize, i + 1);
        *(dirBots + i) = b;
    }
    generation = 0;
}

string Population::toString()
{

    std::stringstream ss;

    cout << "THE bots size is : " << quantity << endl;
    for (int i = 0; i < quantity; i++)
    {
        Bot *current = *(dirBots + i);
        ss << (*current).printDNA() << " CurrentPosition: "
           << (*current).getCurrentPosition() << endl;
    }

    return ss.str();
}

void Population::start()
{
    for (int i = 0; i < quantity; i++)
    {
        Bot *current = *(dirBots + i);
        while ((*current).isAlive())
        { 
            (*current).move();
        }
    }

    FileWriter fw = FileWriter();
    string filename = fw.createFile("gen_0");
    std::stringstream ss;

    ss << "{\"gen\":" << generation << ", \"bots\" :[";

    for (int i= 0; i < quantity; i++)
    {
        Bot *current = *(dirBots + i);
        string separator = (i != quantity -1) ? "," : "" ;
        ss << (*current).getTextToPrint() << separator;
    }

    ss << "]}";

    fw.printText(ss.str(), filename);
    generation++;
}

void Population::sortPopulation() {

    for(int i = 0; i < quantity; i++) {
        for(int j= 0; j < quantity; j++) {
            Bot *botI = *(dirBots + i);
            Bot *botJ = *(dirBots + j);

            if ((*botI).getCurrentPosition() > (*botJ).getCurrentPosition() ) {
                Bot *temp = botI;
                *(dirBots + i) = *(dirBots + j);
                *(dirBots + j) = temp;
            }
        }
    }
}

Bot* Population::mergeBots(Bot *b1, Bot *b2, int id) {
    GenomeMixer gm = GenomeMixer();
    int total = boardSize * boardSize;
    Position **newDNA = gm.mergeListDNA(b1, b2, total);
    Bot *newB1 = new Bot(board, boardSize, newDNA, id);

    (*newB1).setFatherId((*b1).getId());
    (*newB1).setMotherId((*b2).getId());
    return newB1;
}

void Population::reproduce() {
    int half = quantity / 2;
    half = half % 2 == 0 ?  half : half -1;
    Bot **newBotsPopulation = new Bot *[quantity];

    int i;

    int iTotal = 0;
    for( i=0; i < half; i ++) {
        Bot *b1 = *(dirBots + i);
        Bot *b2 = *(dirBots + i + 1);
        Bot *b3 = *(dirBots + i + 2);

        if ( iTotal < quantity ) {
            *(newBotsPopulation + iTotal) = Population::mergeBots(b1, b2, iTotal + 1 );
        }        
        iTotal++;

        if ( iTotal < quantity ) {
            *(newBotsPopulation + iTotal) = Population::mergeBots(b1, b2, iTotal + 2 );
        }
        iTotal++;

        if ( iTotal < quantity ) {
            *(newBotsPopulation + iTotal) = Population::mergeBots(b1, b2, iTotal + 3 );
        }
        iTotal++;
    }
    dirBots = newBotsPopulation;
}

void Population::iterate() {
    sortPopulation();
    cout << "Population Sort" << endl;

    reproduce();
    cout << "Population Reproduced" << endl;

    for (int i = 0; i < quantity; i++)
    {
        Bot *current = *(dirBots + i);
        int j = 0;
        while ((*current).isAlive())
        {
            (*current).move();
        }
    }

    FileWriter fw = FileWriter();
    
    std::stringstream file;
    file << "gen_" << generation;
    generation++;


    string filename = fw.createFile(file.str());
    std::stringstream ss;

    ss << "{\"gen\":" << generation << ", \"bots\" :[";

    for (int i= 0; i < quantity; i++)
    {
        Bot *current = *(dirBots + i);
        string separator = (i != quantity -1) ? "," : "" ;
        ss << (*current).getTextToPrint() << separator;
    }

    ss << "]}";

    fw.printText(ss.str(), filename);
}

Bot* Population::getBest() {
    return *(dirBots + 0);
}

