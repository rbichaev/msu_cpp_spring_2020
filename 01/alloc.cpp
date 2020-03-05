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
    cout << "Создание аллокатора размера " << maxS << " байт...\n";
    maxSize = maxS;
    currSize = 0;
    beginPointer = (char *)malloc(maxSize);
    endPointer = beginPointer;
}

char *alloc(size_t size)
{
    if ((currSize + size) > maxSize)
    {
        return nullptr;
    }
    currSize += size;
    endPointer += size;
    return endPointer;
}

void reset()
{
    currSize = 0;
    endPointer = beginPointer;
}

void freeAllocator()
{
    cout << "Удаление аллокатора размера " << maxSize << " байт...\n";
    maxSize = 0;
    currSize = 0;
    endPointer = nullptr;
    free(beginPointer);
}