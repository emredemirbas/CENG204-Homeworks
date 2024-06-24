/*
    Name Surname: 
    Student ID:
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define M 256
#define B 8
#define S 4
#define E 2

typedef struct{
    bool validity;
    unsigned char tag;
    int block[B];
}line;

typedef struct{
    line lines[E];
}set;

set myCache[S];

int lookforCache(unsigned char memIndex, unsigned char *memory) 
{
    // student code
    // You need to fill the cache according to the rules given in the document.

    return 0; //  Return 0 -> miss , Return 1 -> hit
}

void initializeData(int data[M]) 
{
    for (int i=0; i<M; i++) {
        data[i] = 512 + (rand() % M);
    }
}

void printArray(unsigned char data[M]){
    for (int i=0; i<M; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

void initializeRandomSequence(unsigned char data[M]) 
{
    for (int i=0; i<M; i++) {
        data[i] = rand() % M;
    }
}

void printCache(){
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
    for(int i=0;i<S; i++){
        printf("Set %d -->", i);
        for(int l=0; l < E; l++){
            printf(" Line %d: ", (l+1));
            printf("v: %d - ", myCache[i].lines[l].validity);
            printf("tag: %d - block: ", myCache->lines[l].tag);
            for(int j = 0; j < B; j++){
                printf("%d ", myCache[i].lines[l].block[j]);
            }
            printf("|");
        }
        printf("\n"); 
    }
    printf("-------------------------------------------------------------------------------------------------------------------------\n");

}

void freeCache(){
    for(int i=0;i<S; i++){
        for(int l=0; l < E; l++){
            myCache[i].lines[l].validity=0;
        }
    }
}

int main()
{
    int seed = time(0);
    unsigned char data[M];  

    srand(seed);
    initializeRandomSequence(data);

    printf("Cache at the begining\n");
    printCache();

    // You can test your code by changing following lines after you complete lookforCache function
    // Your code will be tested with a different main function.

    int res = lookforCache(9, data);
    if(res == 1)
        printf("Cache Hit For 9\n");
    else
        printf("Cache Miss For 9\n");
    printCache();


    res = lookforCache(12, data);
    if(res == 1)
        printf("Cache Hit For 12\n");
    else
        printf("Cache Miss For 12\n");
    printCache();

    res = lookforCache(33, data);
    if(res == 1)
        printf("Cache Hit For 33\n");
    else
        printf("Cache Miss For 33\n");
    printCache();

    return 0;
}
