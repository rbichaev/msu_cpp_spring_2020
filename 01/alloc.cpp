#include <iostream>
#include <cstdlib>
#include "alloc.h"

using namespace std;

char *beginPointer;
char *endPointer;
size_t maxSize;
size_t currSize;

void makeAllocator(size_t maxS)
{
    maxSize = maxS;
    currSize = 0;
    if (!(beginPointer = (char *)malloc(maxSize)))
    {
        cout << "Ошибка!\n";
        return;
    }
    endPointer = beginPointer;
}

char *alloc(size_t size)
{
    if ((currSize + size) > maxSize)
    {
        return nullptr;
    }
    currSize += size;
    char *currPointer = endPointer;
    endPointer += size;
    return currPointer;
}

void reset()
{
    currSize = 0;
    endPointer = beginPointer;
}

void freeAllocator()
{
    maxSize = 0;
    currSize = 0;
    endPointer = nullptr;
    free(beginPointer);
}