//
// Created by Buddha on 22-05-2021.
//

#ifndef STANDARDIMPORTS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#endif

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



int drawOrNoDraw() {
    return rand() % 2;
}