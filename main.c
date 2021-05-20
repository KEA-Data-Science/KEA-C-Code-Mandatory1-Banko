#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXDRAW 5 // defines max draws per row on board
#define ROW_LENGTH 9 // defines row length

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

/* Memory Handling Section */
void callocIntArray(int *array, int size);

void deallocIntArray(int *array, int size);

/* General Math and Array Helper Functions Section */
int drawOrNoDraw(); // returns either 1 or 0.   0 is no, 1 is yes
void draw3RandomNumbers(int *array, int baseNumber);

void adjustOutOfRangeValues(int *array, int arraySize, int lowAccept, int highAccept);

void sortIntArrayAscending(int *array, int arrayLength);

void fillArrayWithValue(int *array, int arraySize, int fillValue);

/* Variable state helps determine if a generated board was well-formed */
int boardCorrupt = 0; // 0 == good      1 == bad

int main() {

    int collectionSeed = time(NULL);
    // seeding the random generator with the current time value since EPOCH
    srand(collectionSeed);

    int collectionSize = 20;
    struct BankoBoard boards[collectionSize];
    createBoardCollection(boards, collectionSize, collectionSeed);

    /* PRINTING THE BOARDS */
    for (int i = 0; i < collectionSize; ++i) { printBoard(boards[i]); }

    return 0;
}

void createBoardCollection(struct BankoBoard *boardArrayPointer, int collectionSize,int collectionSeed) {

    struct BankoBoard *allocCounter = boardArrayPointer;
    allocCounter--;

allocCounter = malloc(sizeof(struct BankoBoard)*collectionSize);


    for (int i = 0; i < collectionSize; ++i) {
        printf("malloc address: %d", &allocCounter);
        allocCounter = );
        allocCounter++;
    }

    int corruptCounter = 0; // tracking number of corrupted boards generated and thrown away.

    for (int i = 0; i < collectionSize; ++i) {
        boardCorrupt = 0; // each board gets a new chance
        printf("Printing Board\t%d\n", i);
        struct BankoBoard newBoard;

        newBoard = createBankoBoard(i,collectionSeed);

        if (boardCorrupt >= 1) { // no corruption tolerated
            printf("BOARD THROWN OUT, CREATING EXTRA : #%d\n", corruptCounter++);
            i--;
            continue;
        }

        *(boardArrayPointer + i) = newBoard;
    }
    printf("Corrupt counter reached: %d", corruptCounter);
}

struct BankoBoard createBankoBoard(int boardID, int collectionSeed) {
    struct BankoBoard board;
    initBoard(&board, boardID, collectionSeed);

    int drawsRow_0 = 0; // these keep track of the number of numbers drawn in each row
    int drawsRow_1 = 0;
    int drawsRow_2 = 0;


    // creating numbers for each row, taking already created values into account
    for (int i = 0; i < ROW_LENGTH; ++i) {
        drawNextNumbersForColumn(i,
                                 board.row_0 + i, board.row_1 + i, board.row_2 + i,
                                 i * 10,
                                 &drawsRow_0, &drawsRow_1, &drawsRow_2);
    }

    adjustOutOfRangeValues(board.row_0, 9, 0, 89);
    adjustOutOfRangeValues(board.row_1, 9, 0, 89);
    adjustOutOfRangeValues(board.row_2, 9, 0, 89);

    if (drawsRow_0 + drawsRow_1 + drawsRow_2 != 15) { boardCorrupt = 1; }

    return board;
}

/*
*/
void drawNextNumbersForColumn(int columnNumber,
                              int *row_0,
                              int *row_1,
                              int *row_2,
                              int tens,
                              int *row_0AmountDrawn,
                              int *row_1AmountDrawn,
                              int *row_2AmountDrawn) {

    int possibles[3]; // numbers that might go on the board
    // draw 3 different number in interval, to choose from
    draw3RandomNumbers(possibles, tens);

    // figure out whether to 'draw' each of the three column-places
    int necessityRow_0;
    int necessityRow_1;
    int necessityRow_2;

    int drawsInColumn = 0;
    // draw for 0
    necessityRow_0 = calculateDrawNecessity(columnNumber, drawsInColumn, 0, *row_0AmountDrawn);
    assignNumber(necessityRow_0, row_0, possibles, 0, &drawsInColumn, row_0AmountDrawn);
    // draw for 1
    necessityRow_1 = calculateDrawNecessity(columnNumber, drawsInColumn, 1, *row_1AmountDrawn);
    assignNumber(necessityRow_1, row_1, possibles, 1, &drawsInColumn, row_1AmountDrawn);
    // draw for 2
    necessityRow_2 = calculateDrawNecessity(columnNumber, drawsInColumn, 2, *row_2AmountDrawn);
    assignNumber(necessityRow_2, row_2, possibles, 2, &drawsInColumn, row_2AmountDrawn);

}

void assignNumber(int necessity, int *positionOnBoard, const int *possibles, int indexInPossibles, int *drawsInColumn,
                  int *drawsInRow) {
    switch (necessity) {
        case MUST:
//            printf("MUST\tDrawing\t%d\n", possibles[indexInPossibles]);
            *positionOnBoard = possibles[indexInPossibles];
            *drawsInColumn = (*drawsInColumn) + 1;
            *drawsInRow = (*drawsInRow) + 1;
            break;
        case POSS :
            if (drawOrNoDraw() == 1) {
//                printf("POSS\tDrawing\t%d\n", possibles[indexInPossibles]);
                *positionOnBoard = possibles[indexInPossibles];
                *drawsInColumn = (*drawsInColumn) + 1;
                *drawsInRow = (*drawsInRow) + 1;
            }
            break;
        case NODRAW:
//            printf("Nodraw\n");
            *positionOnBoard = 0;
            break;
        default:
//            printf("::drawNextNumbersForColumn::\t Bad Necessity Value Provided: For row 0: %d", necessity);
            break;
    }
}

int calculateDrawNecessity(int columnNumber, int drawsInColumn, int rowNumber, int drawsInRow) {
    int necessity; // 2 = must, 1 = possible, 0 = cannot draw
    // figure out which of these scenarios is the case:
    // if less have been drawn in row than necessary
    if (drawsInRow < MAXDRAW) { necessity = POSS; }
    // * if there are more row places up for assignment than number of assignments needed to reach 5; necessity = 1
    if (drawsInRow < MAXDRAW && columnNumber >= 5) { necessity = MUST; }
    // * if as many row places are up for assignment as there are assignments needed to reach 5; necessity = 2
    if (drawsInRow >= MAXDRAW) { necessity = NODRAW; }
    // * if assignment is needed to achieve at least 1 member in each column; necessity = 2
    if (rowNumber == 2 && drawsInColumn == 0) {
        // this checking is not essential, for debugging
        if (necessity == NODRAW) {
//            printf("There was a conflict when calculating draw necessity; no more draws allowed, but needed for column integrity.");
            boardCorrupt = 1;
        }
        // debugging end

        necessity = MUST;
    }

    // * if the maximum number of draws for row has been reached; necessity = 0
    return necessity;
}

void printBoard(struct BankoBoard board) {
    printf("\n\tBoard [ ID: %d ]\n", board.id);
    printRow(board.row_0);
    printRow(board.row_1);
    printRow(board.row_2);
    printf("\n");
}

void printRow(const int *array) {
    printf("Indexes: [%d]\t[%d]\t[%d]\t[%d]\t[%d]\t[%d]\t[%d]\t[%d]\t[%d]\n",
           *(array + 0), *(array + 1), *(array + 2), *(array + 3), *(array + 4),
           *(array + 5), *(array + 6), *(array + 7), *(array + 8));
}

void initBoard(struct BankoBoard *board, int id, int collectionSeed) {
    (*board).id = id;
    (*board).collectionSeed = collectionSeed;
    (*board).hitsRow_1 = (int) calloc(1, sizeof(int));
    (*board).hitsRow_2 = (int) calloc(1, sizeof(int));
    (*board).hitsRow_3 = (int) calloc(1, sizeof(int));

    callocIntArray(board->row_0, 9);
    callocIntArray(board->row_1, 9);
    callocIntArray(board->row_2, 9);
    fillArrayWithValue(board->row_0, 9, 0);
    fillArrayWithValue(board->row_1, 9, 0);
    fillArrayWithValue(board->row_2, 9, 0);
}

/* MEMORY HANDLING SECTION */

void callocIntArray(int *array, int size) {
    for (int i = 0; i < size; ++i) {
        array[i] = (int) calloc(1, sizeof(int));
    }
}

void deallocIntArray(int *array, int size) {
    for (int i = 0; i < size; ++i) {
        free((array + i));
    }
}

/* ARRAY AND MATH HELPER METHODS SECTION */

void adjustOutOfRangeValues(int *array, int arraySize, int lowAccept, int highAccept) {
    for (int i = 0; i < arraySize; ++i) {

        if (*(array + i) < lowAccept || *(array + i) > highAccept) {
            printf("Found odd value: %d\n", *(array + i));
            *(array + i) = 0;
        }
    }
}

void draw3RandomNumbers(int *array, int baseNumber) {
    if (baseNumber == 0) {
        do {
            baseNumber = 1;
            *(array) = baseNumber + (rand() % 9);
            *(array + 1) = baseNumber + (rand() % 9);
            *(array + 2) = baseNumber + (rand() % 9);
        } while (*(array) == *(array + 1) || *(array) == *(array + 2) || *(array + 1) == *(array + 2));
    } else {
        do {
            *(array) = baseNumber + (rand() % 10);
            *(array + 1) = baseNumber + (rand() % 10);
            *(array + 2) = baseNumber + (rand() % 10);
        } while (*(array) == *(array + 1) || *(array) == *(array + 2) || *(array + 1) == *(array + 2));
    }
    sortIntArrayAscending(array, 3);
}

void fillArrayWithValue(int *array, int arraySize, int fillValue) {
    for (int i = 0; i < arraySize; i++) {
        array[i] = fillValue;
    }
}

void sortIntArrayAscending(int *array, int arrayLength) {
    int high;
    // for each of the members of the array
    for (int i = 0; i < arrayLength; ++i) {
        // check all numbers in front of it, shifting any lower numbers to ealier places in the array
        for (int j = i + 1; j < arrayLength; ++j) {
            // if ealier number is higher than later number, change their places
            if (*(array + i) > *(array + j)) {
                high = *(array + i);
                *(array + i) = *(array + j);
                *(array + j) = high;
            }
        }
    }
}

int drawOrNoDraw() {
    return rand() % 2;
}