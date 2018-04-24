// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Library General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <iostream>
#include <sstream>
#include "BufferControl.h"

std::vector<int> BufferControl::explode(char sep, std::string src) {
    std::cout << "BufferControl::explode INI" << std::endl;
    std::cout << "BufferControl::explode params: src-> " + src << std::endl;
    std::cout << "BufferControl::explode params: sep-> " + sep << std::endl;
	std::vector<int> output;
	char temp[10];
	int count;
	int i = 0;
	for (count = 0; count < src.size(); count++) {
		if (src[count] != sep) {
			temp[i] = src[count];
			i++;
		} else {
			temp[i] = '\0';
			output.push_back(atoi(temp));
			i = 0;
		}
	}
	if (i > 0) {
			temp[i] = '\0';
			output.push_back(atoi(temp));
	}
    std::cout << "BufferControl::explode END" << std::endl;
	return output;
}

std::vector<int> BufferControl::explodeHex(char sep, std::string src) {
    std::cout << "BufferControl::explodeHex INI" << std::endl;
    std::cout << "BufferControl::explodeHex params: src-> " + src << std::endl;
    std::cout << "BufferControl::explodeHex params: sep-> " + sep << std::endl;
	std::vector<int> output;
	char temp[10];
	int intTemp;
	int count;
	int i = 0;
	for (count = 0; count < src.size(); count++) {
		if (src[count] != sep) {
			temp[i] = src[count];
			i++;
		} else {
			temp[i] = '\0';
			sscanf (temp,"%X",&intTemp);
			output.push_back(intTemp);
			i = 0;
		}
	}
	if (i > 0) {
			temp[i] = '\0';
			sscanf (temp,"%X",&intTemp);
			output.push_back(intTemp);
	}
    std::cout << "BufferControl::explodeHex END" << std::endl;
	return output;
}

void BufferControl::init(int size) {
    std::cout << "BufferControl::init INI" << std::endl;
	int i = 0;
	bufferSize = size;
	buffer = (unsigned char *) malloc(size*sizeof(unsigned char));
	for (i=0;i<size;i++) buffer[i] =  0;
    std::cout << "BufferControl::init END" << std::endl;
}

void BufferControl::setAppendIndex(int data) {
    std::cout << "BufferControl::setAppendIndex INI" << std::endl;
	appendIndex = data;
    std::cout << "BufferControl::setAppendIndex END" << std::endl;
}

void BufferControl::printBuffer(void) {
    std::cout << "BufferControl::printBuffer INI" << std::endl;
	int i=0;
	printf("\n Buffer: \n");
	for (i=0;i<bufferSize;i++) printf(" %d ",buffer[i]);
	printf("\n");
    std::cout << "BufferControl::printBuffer END" << std::endl;
}

void BufferControl::printHexBuffer(void) {
    std::cout << "BufferControl::printHexBuffer INI" << std::endl;
	int i=0;
	printf("\n Buffer: \n");
	for (i=0;i<bufferSize;i++) printf(" %x ",buffer[i]);
	printf("\n");
    std::cout << "BufferControl::printHexBuffer END" << std::endl;
}

void BufferControl::printCharBuffer(void) {
    std::cout << "BufferControl::printCharBuffer INI" << std::endl;
	int i=0;
	printf("\n Buffer: \n");
	for (i=0;i<bufferSize;i++) printf(" %c ",buffer[i]);
	printf("\n");
    std::cout << "BufferControl::printCharBuffer INI" << std::endl;
}

void BufferControl::insertString(int pos, std::string insert) {
    std::cout << "BufferControl::insertString INI" << std::endl;
    std::cout << "BufferControl::insertString params: insert-> " + insert << std::endl;
	int i = 0;
	for (i =0;i<insert.length();i++) {
		buffer[pos] = insert[i];
		pos++;
		appendIndex++;
	}
    std::cout << "BufferControl::insertString END" << std::endl;
}

void BufferControl::insertAppendIndexString(std::string insert) {
    std::cout << "BufferControl::insertAppendIndexString INI" << std::endl;
    std::cout << "BufferControl::insertAppendIndexString params: insert-> " + insert << std::endl;
	int i = 0;
	for (i =0;i<insert.length();i++) {
		buffer[appendIndex] = insert[i];
		appendIndex++;
	}
    std::cout << "BufferControl::insertAppendIndexString END" << std::endl;
}

void BufferControl::insertAppendIndexValue(unsigned char value) {
    std::cout << "BufferControl::insertAppendIndexValue INI" << std::endl;
	buffer[appendIndex] = value;
	appendIndex++;
    std::cout << "BufferControl::insertAppendIndexValue END" << std::endl;
}

void BufferControl::valDump(const void *obj, size_t size, int little_endian,int position) {
    std::cout << "BufferControl::valDump INI" << std::endl;
	int offset = 0;
	int i;
    const unsigned char *byte = (unsigned char *) obj;

   	if ( little_endian ) byte += size - 1;

   	while ( size-- ) {
    	buffer[position+offset] = (unsigned char)*byte;
		byte += little_endian ? -1 : 1;
      	offset++;
   	}
    std::cout << "BufferControl::valDump END" << std::endl;
}

void BufferControl::insertArrayString(std::string insert,int pos) {
    std::cout << "BufferControl::insertArrayString INI" << std::endl;
	int index;
	std::vector<int> codec = explode(',', insert);
	for(index=0;index<codec.size();index++)
		buffer[pos+index] = codec[index];
    std::cout << "BufferControl::insertArrayString END" << std::endl;
}

void BufferControl::insertArrayStringHex(std::string insert,int pos) {
    std::cout << "BufferControl::insertArrayStringHex INI" << std::endl;
	int index;
	std::vector<int> codec = explodeHex(',', insert);
	for(index=0;index<codec.size();index++)
		buffer[pos+index] = codec[index];
    std::cout << "BufferControl::insertArrayStringHex END" << std::endl;
}

void BufferControl::freeBuffer(void) {
    std::cout << "BufferControl::freeBuffer INI" << std::endl;
	free(buffer);
    std::cout << "BufferControl::freeBuffer END" << std::endl;
}

unsigned char* BufferControl::getBuffer(void) {
    std::cout << "BufferControl::getBuffer INI" << std::endl;
	return buffer;
    std::cout << "BufferControl::getBuffer END" << std::endl;
}

void BufferControl::setBuffer(int pos, unsigned char value) {
    std::cout << "BufferControl::setBuffer INI" << std::endl;
	buffer[pos] = value;
    std::cout << "BufferControl::setBuffer END" << std::endl;
}
