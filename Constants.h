// author Janik und Patrick Tinz

#ifndef CONSTANTS_H
#define CONSTANTS_H

const int pageTableSize = 256;
const int offsetLength = 256;

const int ramSize = 128;   // Page 256 Byte  128 * 256 = 32768 Byte = 32KB

// Virtual addresses
const unsigned int pageNumberMask = 0xFF00;   // 1111 1111 0000 0000, mask 8 bits top
const unsigned int offsetMask = 0x00FF;   // 0000 0000 1111 1111, mask 8 bits down

// Frequent addresses for our generator 
const unsigned int frequentAddresses = 50;

#endif

