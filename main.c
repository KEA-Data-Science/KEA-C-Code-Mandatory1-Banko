#ifndef STANDARDIMPORTS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#endif

#ifndef BANKO1_MISCMATH_H
#include "miscmath.h"
#endif

#include "bankoboard.h"

int main() {
    // arduino analogue randomSeed(analogRead(0)); //
    int collectionSeed = time(NULL);
    // seeding the random generator with the current time value since EPOCH
    srand(collectionSeed);

    int collectionSize = 20;
    struct BankoBoard *boards = malloc(sizeof (struct BankoBoard)*collectionSize);
    createBoardCollection(boards, collectionSize, collectionSeed);

    /* PRINTING THE BOARDS */
    for (int i = 0; i < collectionSize; ++i) { printBoard(boards[i]); }

    free(boards);

    return 0;
}
