// author Janik und Patrick Tinz

#include "Statistics.h"

Statistics::Statistics()
{
    numberOfMemoryRead = 0;
    numberOfMemoryWrite = 0;
    numberOfRamRead = 0;
    numberOfRamWrite = 0;
    numberOfPageFaults = 0;
    numberOfPageReplacements = 0;
    numberOfTranslatedAdresses = 0;
    numberOfAccessRam = 0;
}

Statistics::~Statistics() 
{
    
}

void Statistics::incrementNumberOfMemoryRead() 
{
    numberOfMemoryRead++;
}

void Statistics::incrementNumberOfMemoryWrite()
{
    numberOfMemoryWrite++;
}

int Statistics::getNumberOfMemoryWrite() 
{
    return numberOfMemoryWrite;
}

void Statistics::incrementNumberOfRamRead()
{
    numberOfRamRead++;
}

int Statistics::getNumberOfMemoryRead() 
{
    return numberOfMemoryRead;
}

int Statistics::getNumberOfRamRead() 
{
    return numberOfRamRead;
}

void Statistics::incrementNumberOfRamWrite()
{
    numberOfRamWrite++;
}
int Statistics::getNumberOfRamWrite()
{
    return numberOfRamWrite;
}

void Statistics::incrementNumberOfPageFaults() 
{
    numberOfPageFaults++;
}

double Statistics::getPageFaultRate() 
{
    return ((double)numberOfPageFaults / (double)numberOfAccessRam) * 100;
}

int Statistics::getNumberOfPageFaults() 
{
    return numberOfPageFaults;
}

void Statistics::incrementNumberOfPageReplacements() 
{
    numberOfPageReplacements++;
}


int Statistics::getNumberOfPageReplacements() 
{
    return numberOfPageReplacements;
}

void Statistics::incrementNumberOfTranslatedAddresses()
{
    numberOfTranslatedAdresses++;
}
        
int Statistics::getNumberOfTranslatedAddresses()
{
    return numberOfTranslatedAdresses;
}

// Setter
void Statistics::setNumberOfMemoryRead(int numberOfMemoryRead)
{
    this->numberOfMemoryRead = numberOfMemoryRead;
}

void Statistics::setNumberOfMemoryWrite(int numberOfMemoryWrite)
{
    this->numberOfMemoryWrite = numberOfMemoryWrite;
}

void Statistics::setNumberOfPageFaults(int numberOfPageFaults)
{
    this->numberOfPageFaults = numberOfPageFaults;
}

void Statistics::setNumberOfPageReplacements(int numberOfPageReplacements)
{
    this->numberOfPageReplacements = numberOfPageReplacements;
}

void Statistics::setNumberOfRamRead(int numberOfRamRead)
{
    this->numberOfRamRead = numberOfRamRead;
}

void Statistics::setNumberOfRamWrite(int numberOfRamWrite)
{
    this->numberOfRamWrite = numberOfRamWrite;
}

void Statistics::setNumberOfTranslatedAddresses(int numberOfTranslatedAdresses)
{
    this->numberOfTranslatedAdresses = numberOfTranslatedAdresses;
}

void Statistics::incrementNumberOfAccessRam()
{
    numberOfAccessRam++;
}

int Statistics::getNumberOfAccessRam()
{
    return numberOfAccessRam;
}

void Statistics::setNumberOfAccessRam(int numberOfAccessRam)
{
    this->numberOfAccessRam = numberOfAccessRam;
}