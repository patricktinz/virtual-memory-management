// author Janik und Patrick Tinz

#include "Page.h"
#include "Constants.h"
#include <vector>
#include <cstdlib>

using namespace std;

Page::Page()
{

}

Page::Page(int value, int pageNumber) 
{
    this->pageNumber = pageNumber;
    this->value = value;
    this->pageFrame = -1;
    
    for(int i = 0; i < offsetLength; i++)
    {
        offset.push_back(i);
    }
}

Page::~Page() 
{
    
}

int Page::getPageNumber()
{
    return this->pageNumber;
}

void Page::setPageNumber(int pageNumber)
{
    this->pageNumber = pageNumber;
}

void Page::setPageFrame(int pageFrame)
{
    this->pageFrame = pageFrame;
}

int Page::getPageFrame()
{
    return this->pageFrame;
}

void Page::setValue(int value) {
        this->value = value;
    }

int Page::getValue() const {
        return value;
    }