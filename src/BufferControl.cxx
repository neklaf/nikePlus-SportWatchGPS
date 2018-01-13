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
#include <sstream>
#include "BufferControl.h"

std::vector<int> BufferControl::explode(char sep, std::string src) {
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
	return output;
}

std::vector<int> BufferControl::explodeHex(char sep, std::string src) {
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
	return output;
}

void BufferControl::init(int size) {
	int i = 0;
	bufferSize = size;
	buffer = (unsigned char *) malloc(size*sizeof(unsigned char));
	for (i=0;i<size;i++) buffer[i] =  0;
}

void BufferControl::setAppendIndex(int data) {
	appendIndex = data;
}

void BufferControl::printBuffer(void) {
	int i=0;
	printf("\n Buffer: \n");
	for (i=0;i<bufferSize;i++) printf(" %d ",buffer[i]);
	printf("\n");
}

void BufferControl::printHexBuffer(void) {
	int i=0;
	printf("\n Buffer: \n");
	for (i=0;i<bufferSize;i++) printf(" %x ",buffer[i]);
	printf("\n");
}

void BufferControl::printCharBuffer(void) {
	int i=0;
	printf("\n Buffer: \n");
	for (i=0;i<bufferSize;i++) printf(" %c ",buffer[i]);
	printf("\n");
}

void BufferControl::insertString(int pos, std::string insert) {
	int i = 0;
	for (i =0;i<insert.length();i++) {
		buffer[pos] = insert[i];
		pos++;
		appendIndex++;
	}
}

void BufferControl::insertAppendIndexString(std::string insert) {
	int i = 0;
	for (i =0;i<insert.length();i++) {
		buffer[appendIndex] = insert[i];
		appendIndex++;
	}
}

void BufferControl::insertAppendIndexValue(unsigned char value) {
	buffer[appendIndex] = value;
	appendIndex++;
}

void BufferControl::valDump(const void *obj, size_t size, int little_endian,int position) {
	int offset = 0;
	int i;
    const unsigned char *byte = (unsigned char *) obj;

   	if ( little_endian ) byte += size - 1;

   	while ( size-- ) {
    	buffer[position+offset] = (unsigned char)*byte;
		byte += little_endian ? -1 : 1;
      	offset++;
   	}
}

void BufferControl::insertArrayString(std::string insert,int pos) {
	int index;
	std::vector<int> codec = explode(',', insert);
	for(index=0;index<codec.size();index++)
		buffer[pos+index] = codec[index];
}

void BufferControl::insertArrayStringHex(std::string insert,int pos) {
	int index;
	std::vector<int> codec = explodeHex(',', insert);
	for(index=0;index<codec.size();index++)
		buffer[pos+index] = codec[index];
}

void BufferControl::freeBuffer(void) {
	free(buffer);
}

unsigned char* BufferControl::getBuffer(void) {
	return buffer;
}

void BufferControl::setBuffer(int pos, unsigned char value) {
	buffer[pos] = value;
}