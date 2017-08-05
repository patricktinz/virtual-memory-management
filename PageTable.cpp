// author Janik und Patrick Tinz

#include "PageTable.h"
#include "Constants.h"
#include "VirtualMemoryManager.h"
#include <cstdlib>

using namespace std;

PageTable::PageTable() 
{
    for(int i = 0; i < pageTableSize; i++)
    {
        table.push_back(rand()%ramSize);   // init Pageframes
        presentBit.push_back(0);
        dirtyBit.push_back(0);
        rBit.push_back(0);
    }
}

PageTable::~PageTable() 
{
    
}

int PageTable::getPageFrame(int pageNumber)
{
    int pageFrame = table[pageNumber];
    return pageFrame;
}

void PageTable::setPresentBit(int index)
{
    presentBit[index] = 1;
}

int PageTable::getPresentBit(int index)
{
    return presentBit[index];
}

void PageTable::removePresentBit(int index)
{
    presentBit[index] = 0;
}

void PageTable::setReferenceBit(int index)
{
    rBit[index] = 1;
}

void PageTable::removeReferenceBit(int index)
{
    rBit[index] = 0;
}

void PageTable::setDirtyBit(int index)
{
    dirtyBit[index] = 1;
}

void PageTable::removeDirtyBit(int index)
{
    dirtyBit[index] = 0;
}