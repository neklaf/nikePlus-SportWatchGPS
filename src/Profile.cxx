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
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "Profile.h"

std::string Profile::convertString(char* str) {
	int i;
	std::string convert(str);
	std::string out;
	for (i=0; i < convert.length(); i++)
		if ((convert.at(i) > 31) && (convert.at(i) < 127)) out.push_back(convert.at(i));
	return out;
}

int Profile::find(unsigned char *data, int size,char value) {
	int i;
	for (i=0;i<size;i++)
		if (data[i] == value) return i;
	return -1;
}

int Profile::findFrom(unsigned char *data, int from,int size,char value) {
	int i;
	for (i=from;i<size;i++)
		if (data[i] == value) return i;
	return -1;
}

void Profile::setMilles(char value) {
	if (value == 0) milles=true;
		else milles=false;
}

bool Profile::getMilles(void) {
	return milles;
}

void Profile::setPounds(char value) {
	if (value == 0) pounds=true;
		else pounds=false;
}

bool Profile::getPounds(void) {
	return pounds;
}

void Profile::setGender(char value) {
	if (value == 0) gender=true;
		else gender=false;
}

bool Profile::getGender(void) {
	return gender;
}

void Profile::setPin(unsigned char * value) {
	std::string temp;
	int index = 9;
	while(value[index]!=16) {
		temp+= value[index];
		index++;
		if (index > 63) {
			pin.assign("11111111-1111-1111-1111-111111111111");
			return;
		}
	}
	pin.assign(temp);
}

std::string Profile::getPin(void) {
	return pin;
}

void Profile::setUser(unsigned char *value) {
	std::string temp;
	int index = findFrom(value,8,64,16);
	if (index > -1) {
		index++;
		while(value[index] != 0) {
			temp+= value[index];
			index++;
			if (index > 63) {
				user.assign("noName@no.no");
				return;
			}
		}
		user.assign(temp);
	} else user.assign("noName@no.no");
	return;
}

std::string Profile::getUser(void) {
	return user;
}

void Profile::setBirth(unsigned char * value) {
	std::string temp;
	int i;
	int pos;

	pos = findFrom(value,8,32,6);
	if (pos > -1) {
		for (i=9;i<pos;i++) temp+=value[i];
		birth.assign(temp);

	} else birth.assign("2010/10/10");
}

std::string Profile::getBirth(void) {
	return birth;
}

void Profile::setLogUser(unsigned char *value) {
	std::string temp;
	int pos;
	
	pos = find(value,32,6);
	if (pos > -1) {
		pos++;
		while(value[pos] != 0) {
			temp+=value[pos];
			pos++;
		}
		logUser.assign(temp);
	} else logUser.assign("nouser");
}

std::string Profile::getLogUser(void) {
	return logUser;
}

void Profile::setCode(int pos,bool value) {
	codes[pos] = value;	
}

void Profile::setCodes(unsigned char *value) {
	char temp[255];
	int index = 3;
	bool end = false;
	std::string tempCode;
	while ((end == false) || (value[index] != 0)) {
		if (value[index] == 3) end=true;
		temp[index-3] = value[index]+48;
		index++;
	}
	temp[index-3] = '\0';
	tempCode.assign(temp);
	if (tempCode.find('0') > 20) codes[0] = false;
		else codes[0] = true;
	if (tempCode.find('1') > 20) codes[1] = false;
		else codes[1] = true;
	if (tempCode.find('2') > 20) codes[2] = false;
		else codes[2] = true;
	if (tempCode.find('4') > 20) codes[3] = false;
		else codes[3] = true;
	if (tempCode.find('5') > 20) codes[4] = false;
		else codes[4] = true;
}

bool* Profile::getCodes(void) {
	return codes;
}

void Profile::setWeight(unsigned char * value) {
	char convert[100];
	int data = (value[3] << 8) | value[4];
	float gData;
	if ( pounds == false) {
		sprintf(convert,"%.1f",data/2.2046);
		data = (int) atof(convert)/10;
	} else data = data / 10;
	weight = data;
}

int Profile::getWeight(void) {
	return weight;
}

std::string Profile::getDataFormat(void) {
	int i;
	std::stringstream stream;

	stream << "Metric: ";
	if (milles == true) stream << "milles";
		else stream << "kilometres";
	stream << "\nGender: ";
	if (gender == true) stream << "man";
		else stream << "woman";
	stream << "\nWeight: ";
	if (pounds == true) {
		stream << weight << " pounds";
	} else {
		stream << weight << " kilos";
	}
	stream << "\nUser: " << user;
	stream << "\nPin: " << pin;
	stream << "\nBirth: " << birth;
	stream << "\nUser: " << logUser;
	stream << "\nCodes: ";
	for (i=0;i<5;i++)
		if (codes[i] == true) stream << "true ";
			else stream << "false ";
	stream << "\n";
	return stream.str();
}

std::string Profile::getData(void) {
	int i;
	std::stringstream stream;

	if (milles == true) stream << "milles";
		else stream << "kilometres";
	stream << ",";
	if (gender == true) stream << "man";
		else stream << "woman";
	stream << ",";
	if (pounds == true) {
		stream << weight << ",pounds";
	} else {
		stream << weight << ",kilos";
	}
	stream << "," << user;
	stream << "," << pin;
	stream << "," << birth;
	stream << "," << logUser;
	stream << ",";
	for (i=0;i<5;i++)
		if (codes[i] == true) stream << "true ";
			else stream << "false ";
	return stream.str();
}