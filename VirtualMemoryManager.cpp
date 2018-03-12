// author Janik und Patrick Tinz

#include "VirtualMemoryManager.h"
#include "Page.h"
#include "PageTable.h"
#include "Statistics.h"
#include "Page.h"
#include "Constants.h"
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <vector>
#include <list>
#include <string>

using namespace std;

VirtualMemoryManager::VirtualMemoryManager() 
{
    processNumber = 2;
    actualProcessNumber = 0;
    algo = 1;   // default lru
    addressGenerator = 2;   // our address generator
    
    for(int i = 0; i < frequentAddresses; i++)   // create frequent addresses
    {
        newAddressVector.push_back(rand()%65536);
    }
    st = Statistics();  
}

VirtualMemoryManager::~VirtualMemoryManager() 
{
    
}

void VirtualMemoryManager::init()
{  
    for(int j = 0; j < processNumber; j++)
    {
        PageTable newPageTable = PageTable();
        tables.push_back(newPageTable);
    }
    
    st.setNumberOfMemoryRead(0);
    st.setNumberOfMemoryWrite(0);
    st.setNumberOfPageFaults(0);
    st.setNumberOfPageReplacements(0);
    st.setNumberOfRamRead(0);
    st.setNumberOfRamWrite(0);
    st.setNumberOfTranslatedAddresses(0);
    st.setNumberOfAccessRam(0);
    
    ram.clear();
    memory.clear();
}

void VirtualMemoryManager::popPage()
{
    if(algo == 1)
    {
        Page removePage = ram.back();
        int process = removePage.getValue();
        tables[process].removePresentBit(removePage.getPageNumber());   // remove present Bit on page number
        tables[process].removeReferenceBit(removePage.getPageNumber());   // remove reference Bit on page number
        writeMemory(removePage);
        ram.pop_back();
    }
    if(algo == 2)
    {
        Page removePage = ram.front();
        int process = removePage.getValue();
        tables[process].removePresentBit(removePage.getPageNumber());   // remove present Bit on page number
        writeMemory(removePage);
        ram.pop_front();
    }
}

void VirtualMemoryManager::writeRam(Page insertPage)
{  
    if(algo == 1)  // lru
    {
        ram.push_front(insertPage);
    }
    if(algo == 2)   // fifo
    {
        ram.push_back(insertPage);
    }
    
    tables[actualProcessNumber].setPresentBit(insertPage.getPageNumber());   // set present Bit on page number
    st.incrementNumberOfRamWrite();
}

void VirtualMemoryManager::writeMemory(Page newPage)
{
    int process = newPage.getValue();
    tables[process].removePresentBit(newPage.getPageNumber());   // remove present Bit on page number
    tables[process].removeReferenceBit(newPage.getPageNumber());   // remove reference Bit on page number
    memory.push_back(newPage);
    st.incrementNumberOfMemoryWrite();
}

void VirtualMemoryManager::fifo()
{
    Page removePage = ram.front();
    writeMemory(removePage);
    ram.pop_front();   
}

void VirtualMemoryManager::lru()
{
    Page removePage = ram.back();
    writeMemory(removePage);
    ram.pop_back();   
}

void VirtualMemoryManager::operatingSystem(Page insertPage)
{
    if(algo == 1)
        lru();
    if(algo == 2)
        fifo();
    
    writeRam(insertPage);
    st.incrementNumberOfPageReplacements();
}

void VirtualMemoryManager::readRam()
{
    st.incrementNumberOfRamRead();   
}

bool VirtualMemoryManager::mmu(Page actualPage, string operation)   // TODO: reverse page table
{  
    int pageNumber = actualPage.getPageNumber();
    int pageFrame = tables[actualProcessNumber].getPageFrame(pageNumber);
    actualPage.setPageFrame(pageFrame);
    st.incrementNumberOfTranslatedAddresses();
    
    bool checkInRam = false;
    list<Page>::iterator iter;
    for (iter = ram.begin(); iter != ram.end(); iter++)
    {
        int actualPageFrame = (*iter).getPageFrame();
        if(actualPageFrame == pageFrame)   // PageFrame is in RAM
        {
            checkInRam = true;
            if((*iter).getValue() == actualProcessNumber)
            {
                if(tables[actualProcessNumber].getPresentBit(pageNumber) == 1)
                {
                    if(algo == 1)   // lru
                    {
                        tables[actualProcessNumber].setReferenceBit(pageNumber);
                        tables[actualProcessNumber].setPresentBit(pageNumber);
                       
                        ram.erase(iter);
                        ram.push_front(actualPage);
                    }
                    //cout << "lru" << endl;   
                    return true;
                }
                else
                {
                    writeMemory(*iter);
                    ram.erase(iter);
                    readMemory(actualPage);
                    writeRam(actualPage);
                    break;
                }
            }
            else
            {
                //cout << "Prozess " << actualProcessNumber << " wollte auf den Speicherbereich von Prozess " << (*iter).getValue() << " zugreifen. " << endl;
                if(ram.size() == ramSize)
                    popPage();
         
                break;
            }
        }
    }
    if(checkInRam == false && ram.size() != 0)
    {
        readMemory(actualPage);
        if(operation == "read")
            operatingSystem(actualPage);
        if(operation == "write")
            writeRam(actualPage);
    }
    
    if(ram.size() == 0)
        writeRam(actualPage);
    
    return false;
}

void VirtualMemoryManager::readMemory(Page page)
{
    int pageNumber = page.getPageNumber();
    
    for(int i = 0; i < memory.size(); i++)
    {
        if(pageNumber == memory[i].getPageNumber() && page.getValue() == memory[i].getValue())
        {
            st.incrementNumberOfMemoryRead();
            memory.erase(memory.begin() + i);
            break;   // found in Memory
        }
    }   
}

int VirtualMemoryManager::generateVirtualAddress()
{
    int newAddress;
    // First address generator
    if(addressGenerator == 1)
    {
        newAddress = rand()%65536;   // 2^16 addresses
    }
    
    // Second address generator
    if(addressGenerator == 2)
    {
        int random = rand()%3;
        if(random == 0 || random == 1)
        {
            int index = rand()%frequentAddresses;
            newAddress = newAddressVector[index]; 
        }
        else
        {
            newAddress = rand()%65536;
        }
    }
    //int address = newAddress;
    //cout << "Address: 0x" << hex << address << endl;
    //cout << newAddress << endl;
    return newAddress;
}

Page VirtualMemoryManager::generatePage(int address)
{
    int pageNumber = ((address & pageNumberMask) >> 8);
    //cout << pageNumber << endl;
    Page page = Page(actualProcessNumber, pageNumber);
    //cout << actualProcessNumber << endl;
    return page;
}

void VirtualMemoryManager::cpu()
{
    int counter = rand()%8;
    // Read RAM
    if(counter < 3)   
    {
        int address = generateVirtualAddress();
        
        Page page = generatePage(address);
        
        bool pageInRam = mmu(page, "read");

        readRam();
        st.incrementNumberOfAccessRam();
        if(pageInRam == false)
            st.incrementNumberOfPageFaults();
    }
    // Write RAM
    else if(counter > 2 && counter < 6)    
    {
        int address = generateVirtualAddress();
        
        Page page = generatePage(address); 
        
        bool pageInRam = mmu(page, "write");
        st.incrementNumberOfAccessRam();
        if(pageInRam == false)
            st.incrementNumberOfPageFaults();
        
    }
    else
    {
        actualProcessNumber = rand()%processNumber;
    }   
}

void VirtualMemoryManager::run(double stop_time)
{
    time_t start, finish;
    time(&start);
    bool value = true;
    while(value)
    {
        cpu();
        time(&finish);
        double tend= difftime(finish, start);   // Time calculate
        if(tend >= stop_time)
            value = false;
    }   
}

void VirtualMemoryManager::report()
{
    cout << "-----------------------------------------------" << endl;
    cout << "                 Statistics                    " << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "Number of Page Faults = " << st.getNumberOfPageFaults() << endl;
    cout << "Page Fault Rate = " << st.getPageFaultRate() << " % " << endl;
    cout << "Number of Page Replacements = " << st.getNumberOfPageReplacements() << endl;
    cout << "Number of Translated Addresses = " << st.getNumberOfTranslatedAddresses() << endl;
    cout << endl;
}

void VirtualMemoryManager::menuSettings()
{
    int input = 4;
    while(true)
    {
        cout << "(1) Choose number of processes" << endl;
        cout << "(2) Choose page replacement algorithm" << endl;
        cout << "(3) Choose address generator" << endl;
        cout << "(4) Back" << endl;
        cin >> input;
        cout << endl;
        
        switch(input)
        {
            case 1:
                cout << "Number of process: ";
                cin >> processNumber;
                break;
            case 2:
                cout << "Page replacement algorithm: " << endl;
                cout << "(1) LRU " << endl;
                cout << "(2) FIFO " << endl;
                cin >> algo;
                break;
            case 3:
                cout << "Address Generator: " << endl;
                cout << "(1) Random generator" << endl;
                cout << "(2) Our generator" << endl;
                cin >> addressGenerator;
                break;
            case 4:
                return;
                break;
            default:
                cout << "!!!Invalid input!!!" << endl;
                break;
        }
    }
}

int VirtualMemoryManager::mainMenu() 
{
    int input = 0;
    double stop_time = 0;
  
    while(true)
    {
        cout << "################################################" << endl;
        cout << "             Virtual Memory Manager             " << endl;
        cout << "################################################" << endl;
        cout << "(1) Start (default: proccesses -> 2, LRU, Our address generator)" << endl;
        cout << "(2) Settings" << endl;
        cout << "(3) Exit" << endl;
        cin >> input;

        switch(input)
        {
            case 1:
            {
                cout << "Runtime (Sec): " << endl;
                cin >> stop_time;
                init();
                run(stop_time);
                report();
            }
                break;
            case 2:
                menuSettings();
                break;
            case 3:
                return 0;
                break;
            default:
                cout << "!!!Invalid input!!!" << endl;
                break;
        }      
    }
    return 0;
}

