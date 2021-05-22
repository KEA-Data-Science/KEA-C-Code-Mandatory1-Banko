//
// Created by Buddha on 19-05-2021.
//

#ifndef BANKO1_MISCMATH_H
#define BANKO1_MISCMATH_H


/* Memory Handling Section */
void callocIntArray(int *array, int size);

void deallocIntArray(int *array, int size);

/* General Math and Array Helper Functions Section */
int drawOrNoDraw(); // returns either 1 or 0.   0 is no, 1 is yes
void draw3RandomNumbers(int *array, int baseNumber);

void adjustOutOfRangeValues(int *array, int arraySize, int lowAccept, int highAccept);

void sortIntArrayAscending(int *array, int arrayLength);

void fillArrayWithValue(int *array, int arraySize, int fillValue);


#endif //BANKO1_MISCMATH_H
