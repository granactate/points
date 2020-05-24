#ifndef GENOME_MIXER_H
#define GENOME_MIXER_H

#include "Position.h"
#include "Bot.h"

using namespace std;

class GenomeMixer {
    public:
        GenomeMixer();
        int mergeDNA(Position p1, Position p2);
        Position** mergeListDNA(Bot* b1, Bot* b2, int sizeDNA);
};

#endif
