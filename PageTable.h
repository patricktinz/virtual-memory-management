// author Janik und Patrick Tinz

#include <vector>

using namespace std;

#ifndef PAGETABLE_H
#define PAGETABLE_H

class PageTable 
{
public:
    PageTable();
    virtual ~PageTable();
    
    int getPageFrame(int);
    
    void setPresentBit(int);
    void removePresentBit(int);
    int getPresentBit(int);
    
    void setReferenceBit(int);
    void removeReferenceBit(int);
    
    void setDirtyBit(int);
    void removeDirtyBit(int);
    
private:
    vector<int> table;
    vector<int> presentBit;
    vector<int> dirtyBit;
    vector<int> rBit;
};

#endif

