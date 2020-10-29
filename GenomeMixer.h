#ifndef GENOME_MIXER_H
#define GENOME_MIXER_H

#include "Position.h"
#include "Bot.h"

#include <future>

using namespace std;

class GenomeMixer {
    public:
        GenomeMixer();
        int mergeDNA(Position p1, Position p2);
        Position** mergeListDNA(Bot* b1, Bot* b2, int sizeDNA);
        static void mergeListDNAAsync(Bot* b1, Bot* b2, int sizeDNA, promise<Position**> && promise);
        static void mergeRangeDNAAsync(Bot* b1, Bot* b2, int sizeDNA, int initial, int end, Position **DNA);
        static int mergePosition(Position p1, Position p2);
};

#endif
