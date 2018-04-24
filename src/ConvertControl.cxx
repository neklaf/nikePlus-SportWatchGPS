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
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "Controller.h"
#include "ConvertControl.h"

std::vector<std::string> ConvertControl::explodeChar(char sep, std::string src) {
    std::cout << "ConvertControl::explodeChar INI" << std::endl;
	std::vector<std::string> output;
	char temp[10];
	int count;
	int i = 0;
	for (count = 0; count < src.size(); count++) {
		if (src[count] != sep) {
			temp[i] = src[count];
			i++;
		} else {
			temp[i] = '\0';
			output.push_back(temp);
			i = 0;
		}
	}
	if (i > 0) {
			temp[i] = '\0';
			output.push_back(temp);
	}
    std::cout << "ConvertControl::explodeChar END" << std::endl;
	return output;
}

std::vector<int> ConvertControl::explodeInt(char sep, std::string src) {
    std::cout << "ConvertControl::explodeInt INI" << std::endl;
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
    std::cout << "ConvertControl::explodeInt END" << std::endl;
	return output;
}

void ConvertControl::setController(Controller control) {
    std::cout << "ConvertControl::setController INI" << std::endl;
	controller = control;
    std::cout << "ConvertControl::setController INI" << std::endl;
}

bool ConvertControl::setTime(std::string date) {
    std::cout << "ConvertControl::setTime INI" << std::endl;
    std::cout << "ConvertControl::setTime params: date-> " + date << std::endl;
	// yyyy-mm-dd,hh:mm:ss
	std::vector<std::string> step1;
	std::vector<int> step2; 
	std::vector<int> step3; 

	step1 = explodeChar(',',date);
	if (step1.size()<2) return false;
	step2 = explodeInt('-',step1[0]);
	if (step2.size()<3) return false;
	step3 = explodeInt(':',step1[1]);
	if (step3.size()<3) return false;
	controller.setTime(step3[0],step3[1],step3[2],step2[2],step2[1],step2[0]);
    std::cout << "ConvertControl::setTime END" << std::endl;
	return true;
}

bool ConvertControl::changeHour(std::string hour) {
    std::cout << "ConvertControl::changeHour INI" << std::endl;
	if (hour.compare("12") == 0) controller.setFormatHour(false);
		else if (hour.compare("24") == 0) controller.setFormatHour(true);
			else return false;
	return true;
}

bool ConvertControl::changeMetric(std::string metric) {
    std::cout << "ConvertControl::changeMetric INI" << std::endl;
	if (metric.compare("milles") == 0) controller.setMilles(true);
		else if (metric.compare("kilometres") == 0) controller.setMilles(false);
			else return false;
	return true;
}

bool ConvertControl::changeWeight(std::string weight) {
    std::cout << "ConvertControl::changeWeight INI" << std::endl;
	if (weight.compare("pounds") == 0) controller.setTypeWeight(true);
		else if (weight.compare("kilos") == 0) controller.setTypeWeight(false);
			else return false;
	return true;
}

bool ConvertControl::changeWeightValue(std::string value) {
    std::cout << "ConvertControl::changeWeightValue INI" << std::endl;
	int convertValue;
	convertValue = atoi(value.data());
	if ((convertValue==0) || (convertValue > 500)) return false;
	controller.setWeight(convertValue);
    std::cout << "ConvertControl::changeWeightValue END" << std::endl;
	return true;
}

bool ConvertControl::changeGender(std::string gender) {
    std::cout << "ConvertControl::changeGender INI" << std::endl;
	if (gender.compare("man") == 0) controller.setGender(true);
	else if (gender.compare("woman") == 0) controller.setGender(false);
	else return false;
    std::cout << "ConvertControl::changeGender END" << std::endl;
	return true;
}

bool ConvertControl::changePin(std::string pin) {
    std::cout << "ConvertControl::changePin INI" << std::endl;
	if (pin.size()!=36) return false;
	controller.setPin(pin);
    std::cout << "ConvertControl::changePin INI" << std::endl;
	return true;
}

bool ConvertControl::changeUser(std::string user) {
    std::cout << "ConvertControl::changeUser INI" << std::endl;
	if (user.size()==0) return false;
	controller.setUser(user);
    std::cout << "ConvertControl::changeUser END" << std::endl;
	return true;
}

bool ConvertControl::changeUserLog(std::string userLog) {
    std::cout << "ConvertControl::changeUserLog INI" << std::endl;
	if (userLog.size()==0) return false;
	controller.setLogUser(userLog);
    std::cout << "ConvertControl::changeUserLog END" << std::endl;
	return true;
}

bool ConvertControl::changeBirth(std::string date) {
    std::cout << "ConvertControl::changeBirth INI" << std::endl;
	// yyyy-mm-dd,hh:mm:ss
	std::vector<int> step1; 
	
	step1 = explodeInt('/',date);
	if (step1.size()<3) return false;
	controller.setBirth(date);
    std::cout << "ConvertControl::changeBirth END" << std::endl;
	return true;
}

bool ConvertControl::changeCodes(std::string data) {
    std::cout << "ConvertControl::changeCodes INI" << std::endl;
	int convertValue;
	convertValue = atoi(data.data());
	if ((convertValue==0) || (convertValue > 1000)) return false;
	controller.setCodes(convertValue);
    std::cout << "ConvertControl::changeCodes END" << std::endl;
	return true;
}

bool ConvertControl::readTraks(std::string file) {
    std::cout << "ConvertControl::readTraks INI" << std::endl;
	if (!controller.getReadTracks(file)) {
		std::cerr << "Error reading tracks data.\n";
		return false;
	}
    std::cout << "ConvertControl::readTraks END" << std::endl;
	return true;
}

void ConvertControl::free(void) {
    std::cout << "ConvertControl::free INI" << std::endl;
	controller.free();
    std::cout << "ConvertControl::free END" << std::endl;
}
