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
    std::cout << "Profile::convertString INI" << std::endl;
	int i;
	std::string convert(str);
	std::string out;
	for (i=0; i < convert.length(); i++)
		if ((convert.at(i) > 31) && (convert.at(i) < 127)) out.push_back(convert.at(i));

    std::cout << "Profile::convertString END: " + out << std::endl;
	
    return out;
}

int Profile::find(unsigned char *data, int size,char value) {
    std::cout << "Profile::find INI" << std::endl;
	int i;
	for (i=0;i<size;i++)
		if (data[i] == value) return i;
    std::cout << "Profile::find END" << std::endl;
	return -1;
}

int Profile::findFrom(unsigned char *data, int from,int size,char value) {
    std::cout << "Profile::findFrom INI" << std::endl;
	int i;
	for (i=from;i<size;i++)
		if (data[i] == value) return i;
    std::cout << "Profile::findFrom END" << std::endl;
	return -1;
}

void Profile::setMilles(char value) {
    std::cout << "Profile::setMilles INI" << std::endl;
	if (value == 0) milles=true;
		else milles=false;
    std::cout << "Profile::setMilles END" << std::endl;
}

bool Profile::getMilles(void) {
    std::cout << "Profile::getMilles INI" << std::endl;
	return milles;
}

void Profile::setPounds(char value) {
    std::cout << "Profile::setPounds INI" << std::endl;
	if (value == 0) pounds=true;
		else pounds=false;
    std::cout << "Profile::setPounds END" << std::endl;
}

bool Profile::getPounds(void) {
    std::cout << "Profile::getPounds INI" << std::endl;
	return pounds;
}

void Profile::setGender(char value) {
    std::cout << "Profile::setGender INI" << std::endl;
	if (value == 0) gender=true;
		else gender=false;
    
    std::cout << "Profile::setGender END" << std::endl;
}

bool Profile::getGender(void) {
    std::cout << "Profile::getGender INI" << std::endl;
    return gender;
}

void Profile::setPin(unsigned char * value) {
    std::cout << "Profile::setPin INI" << std::endl;
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
    std::cout << "Profile::setPin END" << std::endl;
}

std::string Profile::getPin(void) {
    std::cout << "Profile::getPin INI" << std::endl;
	return pin;
}

void Profile::setUser(unsigned char *value) {
    std::cout << "Profile::setUser INI" << std::endl;
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
    std::cout << "Profile::getUser INI" << std::endl;
	return user;
}

void Profile::setBirth(unsigned char * value) {
    std::cout << "Profile::setBirth INI" << std::endl;
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
    std::cout << "Profile::getBirth INI" << std::endl;
	return birth;
}

void Profile::setLogUser(unsigned char *value) {
    std::cout << "Profile::setLogUser INI" << std::endl;
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
    std::cout << "Profile::setLogUser END" << std::endl;
}

std::string Profile::getLogUser(void) {
    std::cout << "Profile::getLogUser INI" << std::endl;
	return logUser;
}

void Profile::setCode(int pos,bool value) {
    std::cout << "Profile::setCode INI" << std::endl;
	codes[pos] = value;	
    std::cout << "Profile::setCode END" << std::endl;
}

void Profile::setCodes(unsigned char *value) {
    std::cout << "Profile::setCodes INI" << std::endl;
    std::cout << "Profile::setCodes params: value-> " << std::endl;
	char temp[255];
	int index = 3;
	bool end = false;
	std::string tempCode;
	while ((end == false) || (value[index] != 0)) {
		//std::cout << "Profile::setCodes value[index]-> " + value[index] << std::endl;
		if (value[index] == 3) end=true;
		temp[index-3] = value[index]+48;
		index++;
	}
	temp[index-3] = '\0';
	std::cout << "Profile::setCodes temp-> " << temp << std::endl;
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
    std::cout << "Profile::setCodes END" << std::endl;
}

bool* Profile::getCodes(void) {
    std::cout << "Profile::getCodes INI" << std::endl;
	return codes;
}

void Profile::setWeight(unsigned char * value) {
    std::cout << "Profile::setWeight INI" << std::endl;
	char convert[100];
	int data = (value[3] << 8) | value[4];
	float gData;
	if ( pounds == false) {
		sprintf(convert,"%.1f",data/2.2046);
		data = (int) atof(convert)/10;
	} else data = data / 10;
	weight = data;
    std::cout << "Profile::setWeight END" << std::endl;
}

int Profile::getWeight(void) {
    std::cout << "Profile::getWeight INI" << std::endl;
	return weight;
}

std::string Profile::getDataFormat(void) {
    std::cout << "Profile::getDataFormat INI" << std::endl;
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

    std::cout << "Profile::getDataFormat END" << std::endl;
	return stream.str();
}

std::string Profile::getData(void) {
    std::cout << "Profile::getData INI" << std::endl;
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

    std::cout << "Profile::getData END" << std::endl;
	return stream.str();
}
