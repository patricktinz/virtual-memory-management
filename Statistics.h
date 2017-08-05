// author Janik und Patrick Tinz

#ifndef STATISTICS_H_
#define STATISTICS_H_

class Statistics 
{
public:
        Statistics();
        virtual ~Statistics();

        // Disk
        void incrementNumberOfMemoryRead();
        int getNumberOfMemoryRead();
        void setNumberOfMemoryRead(int);
        void incrementNumberOfMemoryWrite();
        int getNumberOfMemoryWrite();
        void setNumberOfMemoryWrite(int);

        // RAM
        void incrementNumberOfRamRead();
        int getNumberOfRamRead();
        void setNumberOfRamRead(int);
        void incrementNumberOfRamWrite();
        int getNumberOfRamWrite();
        void setNumberOfRamWrite(int);
        void incrementNumberOfPageFaults();
        int getNumberOfPageFaults();
        void setNumberOfPageFaults(int);
        double getPageFaultRate();

        void incrementNumberOfPageReplacements();
        int getNumberOfPageReplacements();
        void setNumberOfPageReplacements(int);
        void incrementNumberOfTranslatedAddresses();
        int getNumberOfTranslatedAddresses();
        void setNumberOfTranslatedAddresses(int);
        
        void incrementNumberOfAccessRam();
        int getNumberOfAccessRam();
        void setNumberOfAccessRam(int);
        
private:
        int numberOfMemoryRead;
        int numberOfMemoryWrite;
        int numberOfRamRead;
        int numberOfRamWrite;
        int numberOfPageFaults;
        int numberOfPageReplacements;
        int numberOfTranslatedAdresses;
        int numberOfAccessRam;
};

#endif 



