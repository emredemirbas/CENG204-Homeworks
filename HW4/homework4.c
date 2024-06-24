/*
    Name Surname: Emre Demirbaş
    Student ID: 21050111069
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#define M 256
#define B 8
#define S 4
#define E 2

typedef struct {
    bool validity;
    unsigned char tag;
    int block[B];
} line;

typedef struct {
    line lines[E];
} set;

set myCache[S];

int lookforCache(unsigned char memIndex, unsigned char *memory) {
    // Since there are S=4 sets, setIndex must have 2 bits. (2^2 = 4)
    // Similarly, as there are B=8 bytes/block, blockOffset must have 3 bits. (2^3 = 8)
    // And since we have total of 8 bits for memIndex, leading 3 bits (8 - 2 - 3) represents the tagValue.

    int setIndexSize = (int) log2(S); // 2 (s)
    int blockOffsetSize = (int) log2(B); // 3 (b)
    int tagValueSize = 8 - (setIndexSize + blockOffsetSize); // 3 (t)

    // t = 3 | s = 2 | b = 3
    //  xxx  |  xx   |  xxx
    unsigned char tMask = 0b11100000;
    unsigned char sMask = 0b00011000;
    unsigned char bMask = 0b00000111;

    unsigned char tagValue = (memIndex & tMask) >> (setIndexSize + blockOffsetSize);
    unsigned char setIndex = (memIndex & sMask) >> blockOffsetSize;
    unsigned char blockOffset = (memIndex & bMask);

    set *currentSet = &myCache[setIndex];
    for (int j = 0; j < E; j++) {
        // in the currentSet, if v = 1 and tagValue matches with the tag in any line, then it'setIndex cache hit.
        if (currentSet->lines[j].validity && currentSet->lines[j].tag == tagValue) {
            return 1;
        }
    }

    // find line index to update.
    int lineIndexToUpdate = -1;
    for (int j = 0; j < E; j++) {
        if (!currentSet->lines[j].validity) {
            lineIndexToUpdate = j;
            break;
        }
    }

    // After the iteration above, if lineIndexToUpdate stays -1, it means that all lines are valid in the currentSet.
    // According to Homework file, if all lines are valid and a line must be removed (Assuming E = 2),
    // Line 0 must be removed if memIndex is even.
    // Line 1, otherwise.
    if (lineIndexToUpdate == -1) {
        lineIndexToUpdate = memIndex % 2;
    }

    line *lineToUpdate = &currentSet->lines[lineIndexToUpdate];

    lineToUpdate->validity = 1;
    lineToUpdate->tag = tagValue;

    int beginningIndex = memIndex - blockOffset;
    for (int j = 0; j < B; j++) {
        lineToUpdate->block[j] = memory[beginningIndex + j];
    }

    return 0;
}

void initializeData(int data[M]) {
    for (int i = 0; i < M; i++) {
        data[i] = 512 + (rand() % M);
    }
}

void printArray(unsigned char data[M]) {
    for (int i = 0; i < M; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

void initializeRandomSequence(unsigned char data[M]) {
    for (int i = 0; i < M; i++) {
        data[i] = rand() % M;
        // data[i] = i; // for testing purposes.
    }
}

void printCache() {
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < S; i++) {
        printf("Set %d -->", i);
        for (int l = 0; l < E; l++) {
            printf(" Line %d: ", (l + 1));
            printf("v: %d - ", myCache[i].lines[l].validity);
            printf("tag: %d - block: ", myCache[i].lines[l].tag);
            for (int j = 0; j < B; j++) {
                printf("%d ", myCache[i].lines[l].block[j]);
            }
            printf("|");
        }
        printf("\n");
    }
    printf("-------------------------------------------------------------------------------------------------------------------------\n");

}

void freeCache() {
    for (int i = 0; i < S; i++) {
        for (int l = 0; l < E; l++) {
            myCache[i].lines[l].validity = 0;
        }
    }
}

int main() {
    int seed = time(0);
    unsigned char data[M];

    srand(seed);
    initializeRandomSequence(data);

    printf("Cache at the beginning\n");
    printCache();

    // You can test your code by changing following lines after you complete lookforCache function
    // Your code will be tested with a different main function.


    int res = lookforCache(9, data);
    if (res == 1)
        printf("Cache Hit For 9\n");
    else
        printf("Cache Miss For 9\n");
    printCache();


    res = lookforCache(12, data);
    if (res == 1)
        printf("Cache Hit For 12\n");
    else
        printf("Cache Miss For 12\n");
    printCache();

    res = lookforCache(33, data);
    if (res == 1)
        printf("Cache Hit For 33\n");
    else
        printf("Cache Miss For 33\n");
    printCache();


    /*
    lookforCache(0, data);
    printCache();

    lookforCache(32, data);
    printCache();

    lookforCache(97, data);
    printCache();
     */

    return 0;
}
