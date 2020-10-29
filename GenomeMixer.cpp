#include "GenomeMixer.h"
#include "Position.h"
#include "Random.h"

#include <iostream>
#include <future>
#include <thread>

GenomeMixer::GenomeMixer() {}

int GenomeMixer::mergeDNA(Position p1, Position p2)
{
    Random generator = Random();
    int initialPercentage = generator.number(1, 100);

    //case where both are undefined
    if (p1.getDirection() == Position::UNDEFINED && p2.getDirection() == Position::UNDEFINED)
    {   
        return Position::UNDEFINED;
    }

    //case where one of parents is undefined
    if (p1.getDirection() == Position::UNDEFINED || p2.getDirection() == Position::UNDEFINED)
    {
        Position *active = &p1;

        if (p1.getDirection() == Position::UNDEFINED)
        {
            active = &p2;
        };

        return initialPercentage >= 70 ? generator.number(1, 4)  : (*active).getDirection();
    }

    // case both parents have the same genome 10% of mutation
    if (p1.getDirection() == p2.getDirection())
    {
        return initialPercentage >= 90 ? generator.number(1, 4) : p1.getDirection();
    }

    // case both parents have a different genome but both are different to undefined
    int changeDominant = generator.number(1, 100) % 2;
    Position *dominant = &p1;
    Position *recessive = &p2;

    //dominant is the second parent
    if (changeDominant == 0)
    {
        dominant = &p2;
        recessive = &p1;
    }

    if (initialPercentage > 75)
    {
        return initialPercentage > 90 ? generator.number(1, 4) : (*recessive).getDirection();
    }

    return initialPercentage > 90 ? generator.number(1, 4) : (*dominant).getDirection();
};

Position** GenomeMixer::mergeListDNA(Bot* b1, Bot* b2, int sizeDNA) {
    Position** b1DNA = b1->getDNA();
    Position** b2DNA = b2->getDNA();
    Random generator = Random();

    int lengthB1 = b1->getCurrentPosition() - 1;
    int lengthB2 = b2->getCurrentPosition() - 1;
    int percentage = generator.number(1, 100);

    Position **newDNA = new Position *[sizeDNA];

    //if the percentage is smaller than 45% then Bot2 will be dominant on first position
    Position *currP = b1->getDnaByPosition(0);
    
    if (percentage <= 45) {
        currP = b2->getDnaByPosition(0);
    }
    
    Position *initialPos = new Position(currP->getI(), currP->getJ(), 0);
    *(newDNA) = initialPos;

    //iterate each item in the DNA
    for(int i = 1; i < sizeDNA; i++) {

        Position *currentDnaB1 = b1->getDnaByPosition(i);
        Position *currentDnaB2 = b2->getDnaByPosition(i);
        
        Position *pos = new Position();
        (*pos).setDirection(GenomeMixer::mergeDNA(
            *currentDnaB1,
            *currentDnaB2
        ));

        *(newDNA + i) = pos;        
    }
    

    return newDNA;
};

int GenomeMixer::mergePosition(Position p1, Position p2) {
    Random generator = Random();
    int initialPercentage = generator.number(1, 100);

    //case where both are undefined
    if (p1.getDirection() == Position::UNDEFINED && p2.getDirection() == Position::UNDEFINED)
    {   
        return Position::UNDEFINED;
    }

    //case where one of parents is undefined
    if (p1.getDirection() == Position::UNDEFINED || p2.getDirection() == Position::UNDEFINED)
    {
        Position *active = &p1;

        if (p1.getDirection() == Position::UNDEFINED)
        {
            active = &p2;
        };

        return initialPercentage >= 70 ? generator.number(1, 4)  : (*active).getDirection();
    }

    // case both parents have the same genome 10% of mutation
    if (p1.getDirection() == p2.getDirection())
    {
        return initialPercentage >= 90 ? generator.number(1, 4) : p1.getDirection();
    }

    // case both parents have a different genome but both are different to undefined
    int changeDominant = generator.number(1, 100) % 2;
    Position *dominant = &p1;
    Position *recessive = &p2;

    //dominant is the second parent
    if (changeDominant == 0)
    {
        dominant = &p2;
        recessive = &p1;
    }

    if (initialPercentage > 75)
    {
        return initialPercentage > 90 ? generator.number(1, 4) : (*recessive).getDirection();
    }

    return initialPercentage > 90 ? generator.number(1, 4) : (*dominant).getDirection();
};

void GenomeMixer::mergeRangeDNAAsync(Bot* b1, Bot* b2, int sizeDNA, int start, int end, Position **DNA) {
    for(int i = start; i < end; i++) {
        Position *DNA1 = b1->getDnaByPosition(i);
        Position *DNA2 = b2->getDnaByPosition(i);

        Position *pos = new Position();
        pos->setDirection(GenomeMixer::mergePosition(*DNA1, *DNA2));


        *(DNA + i) = pos;
    }
}

void GenomeMixer::mergeListDNAAsync(Bot* b1, Bot* b2, int sizeDNA, promise<Position**> && promise) {
    Position** b1DNA = b1->getDNA();
    Position** b2DNA = b2->getDNA();
    Random generator = Random();

    int lengthB1 = b1->getCurrentPosition() - 1;
    int lengthB2 = b2->getCurrentPosition() - 1;
    int percentage = generator.number(1, 100);

    Position **newDNA = new Position *[sizeDNA];

    //if the percentage is smaller than 45% then Bot2 will be dominant on first position
    Position *currP = b1->getDnaByPosition(0);
    
    if (percentage <= 45) {
        currP = b2->getDnaByPosition(0);
    }
    
    Position *initialPos = new Position(currP->getI(), currP->getJ(), 0);
    *(newDNA) = initialPos;

    int step = sizeDNA / 4;
    int threadNumber = 0;

    thread threads[4];
    
    
    for(int i = 1; i < sizeDNA; i += step) {
        int end = (i + step > sizeDNA) ?sizeDNA : i + step;
        threads[threadNumber] = thread(GenomeMixer::mergeRangeDNAAsync, b1, b2, sizeDNA, i, end, newDNA);
        threadNumber++;
    }    

    for(int i=0; i < 4; i++) {
       threads[i].join();
    }

    promise.set_value(newDNA);
};