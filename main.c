#ifndef STANDARDIMPORTS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#endif
/* Contains helper functions to initialize and create the boards. Unused here; here for clarity */
#ifndef BANKO1_MISCMATH_H

#include "miscmath.h"

#endif
/* Contains all the functions utilized to generate BankoBoards */
#include "bankoboard.h"

void getNumberOfBoards(int *collSize);
void userRequestedCollection(int collectionSeed);

int main() {
    // arduino analogue randomSeed(analogRead(0)); -- just a note for later
    // with the collectionSeed it is technically possible to recreate the board sequence
    int collectionSeed = time(NULL);
    // seeding the random generator with the current time value since EPOCH
    srand(collectionSeed);

    userRequestedCollection(collectionSeed);

    return 0;
}

void userRequestedCollection(int collectionSeed){
    int *collectionSize = calloc(1, sizeof(int));
    getNumberOfBoards(collectionSize);

    if (*collectionSize != 0) {
        struct BankoBoard *boards = malloc(sizeof(struct BankoBoard) * (*collectionSize));
        // generating collection of board
        createBoardCollection(boards, *collectionSize, collectionSeed);
        /* PRINTING THE BOARDS */
        for (int i = 0; i < *collectionSize; ++i) { printBoard(boards[i]); }
        free(boards);
    } else {
        printf("You chose to not not create any number of banko boards. Exiting Program.");
    }
    free(collectionSize);
}

/* Function returns an int entered by user. If something else than an int was entered,
 * no board will be printed: 0 is returned. */
void getNumberOfBoards(int *collSize) {
    // Requesting user for number of boards to produce.
    printf("Please input number of banko boards to create and print:\t");
    scanf("%d", collSize);
}
