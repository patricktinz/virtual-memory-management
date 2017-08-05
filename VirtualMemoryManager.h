// author Janik und Patrick Tinz

#include "Statistics.h"
#include "PageTable.h"
#include "Page.h"
#include "Constants.h"
#include <cstdlib>
#include <string>
#include <vector>
#include <list>

using namespace std;

#ifndef VIRTUALMEMORYMANAGER_H
#define VIRTUALMEMORYMANAGER_H

class VirtualMemoryManager {
public:
    VirtualMemoryManager();
    virtual ~VirtualMemoryManager();

    void init();
    void popPage();
    void writeRam(Page insertPage);
    void writeMemory(Page newPage);
    void fifo();
    void lru();
    void operatingSystem(Page insertPage);
    void readRam();
    bool mmu(Page actualPage, string);
    void readMemory(Page page);
    int generateVirtualAddress();
    Page generatePage(int);
    void cpu();
    void run(double);
    void report();
    void menuSettings();
    int mainMenu();
    
    int processNumber;
    int actualProcessNumber;
    int algo;   // default lru
    int addressGenerator;
    vector<int> newAddressVector;

    list<Page> ram;   // example: Page 256 Byte  128 * 256 = 32768 Byte = 32KB
    vector<Page> memory;   
    vector<PageTable> tables;
private:
    Statistics st;
};

#endif 

