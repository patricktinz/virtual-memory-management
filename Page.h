// author Janik und Patrick Tinz

#include <vector>

using namespace std;

#ifndef PAGE_H
#define PAGE_H

class Page 
{
public:
    Page();
    Page(int, int);
    virtual ~Page();
    
    int getPageNumber();
    void setPageNumber(int); 
    
    void setPageFrame(int);
    int getPageFrame();

    void setValue(int);
    int getValue() const;
      
private:    
    int pageNumber;
    int pageFrame;
    vector<int> offset;
    int value;
};

#endif

