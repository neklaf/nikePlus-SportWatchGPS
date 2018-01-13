/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */
#ifndef BUFFER_CONTROL_H
#define BUFFER_CONTROL_H

#include <string>
#include <vector>
class BufferControl {
	private:
	unsigned char * buffer;
	int bufferSize;
	int appendIndex;
	std::vector<int> explode(char, std::string);
	std::vector<int> explodeHex(char, std::string);
	public:
	void init(int);
	void setAppendIndex(int);
	void printBuffer(void);
	void	printHexBuffer(void);
	void printCharBuffer(void);	
	void insertString(int,std::string);
	void insertAppendIndexString(std::string);
	void insertAppendIndexValue(unsigned char);
	void valDump(const void *, size_t, int,int);
	void insertArrayString(std::string,int);
	void insertArrayStringHex(std::string,int);
	void freeBuffer(void);	
	unsigned char* getBuffer(void);
	void setBuffer(int, unsigned char);
};
#endif