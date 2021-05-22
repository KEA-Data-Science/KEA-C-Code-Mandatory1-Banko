//
// Created by Buddha on 19-05-2021.
//

#ifndef BANKO1_BANKOBOARD_H
#define BANKO1_BANKOBOARD_H

// bankoboard.h
#ifndef BANKOCONSTANTS
#define BANKOCONSTANTS

#define ROW_LENGTH 9 // defines row length
#define MAXDRAW 5 // defines max draws per row on board

//Next MACROS will be used to distinguish whether or not to draw number for board
#define MUST 2
#define POSS 0
#define NODRAW -1


struct BankoBoard
{
    int id;
    int row_0[ROW_LENGTH];
    int row_1[ROW_LENGTH];
    int row_2[ROW_LENGTH];
    int hitsRow_1, hitsRow_2, hitsRow_3, collectionSeed;
};

#endif



/* Banko Board Creation Section */
struct BankoBoard createBankoBoard(int id, int collectionSeed); // returns a finished banko board

void createBoardCollection(struct BankoBoard *boardArrayPointer, int collectionSize, int collectionSeed);

int calculateDrawNecessity(int columnNumber, int drawsInColumn, int rowNumber, int drawsInRow);

void drawNextNumbersForColumn(int columnNumber, int *row_0, int *row_1, int *row_2, int tens,
                              int *row_0AmountDrawn, int *row_1AmountDrawn, int *row_2AmountDrawn);

void assignNumber(int necessity, int *positionOnBoard, const int *possibles, int indexInPossibles, int *drawsInColumn,
                  int *drawsInRow);

void printRow(const int *row);

void printBoard(struct BankoBoard board);

void initBoard(struct BankoBoard *board, int id, int collectionSeed);

void deallocBoardCollection(struct BankoBoard *collection, int collectionSize);

#endif //BANKO1_BANKOBOARD_H
