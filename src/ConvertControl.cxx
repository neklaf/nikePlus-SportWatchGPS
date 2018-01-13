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
	return output;
}

std::vector<int> ConvertControl::explodeInt(char sep, std::string src) {
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

void ConvertControl::setController(Controller control) {
	controller = control;
}

bool ConvertControl::setTime(std::string date) {
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
	return true;
}

bool ConvertControl::changeHour(std::string hour) {
	if (hour.compare("12") == 0) controller.setFormatHour(false);
		else if (hour.compare("24") == 0) controller.setFormatHour(true);
			else return false;
	return true;
}

bool ConvertControl::changeMetric(std::string metric) {
	if (metric.compare("milles") == 0) controller.setMilles(true);
		else if (metric.compare("kilometres") == 0) controller.setMilles(false);
			else return false;
	return true;
}

bool ConvertControl::changeWeight(std::string weight) {
	if (weight.compare("pounds") == 0) controller.setTypeWeight(true);
		else if (weight.compare("kilos") == 0) controller.setTypeWeight(false);
			else return false;
	return true;
}

bool ConvertControl::changeWeightValue(std::string value) {
	int convertValue;
	convertValue = atoi(value.data());
	if ((convertValue==0) || (convertValue > 500)) return false;
	controller.setWeight(convertValue);
	return true;
}

bool ConvertControl::changeGender(std::string gender) {
	if (gender.compare("man") == 0) controller.setGender(true);
		else if (gender.compare("woman") == 0) controller.setGender(false);
			else return false;
	return true;
}

bool ConvertControl::changePin(std::string pin) {
	if (pin.size()!=36) return false;
	controller.setPin(pin);
	return true;
}

bool ConvertControl::changeUser(std::string user) {
	if (user.size()==0) return false;
	controller.setUser(user);
	return true;
}

bool ConvertControl::changeUserLog(std::string userLog) {
	if (userLog.size()==0) return false;
	controller.setLogUser(userLog);
	return true;
}

bool ConvertControl::changeBirth(std::string date) {
	// yyyy-mm-dd,hh:mm:ss
	std::vector<int> step1; 
	
	step1 = explodeInt('/',date);
	if (step1.size()<3) return false;
	controller.setBirth(date);
	return true;
}

bool ConvertControl::changeCodes(std::string data) {
	int convertValue;
	convertValue = atoi(data.data());
	if ((convertValue==0) || (convertValue > 1000)) return false;
	controller.setCodes(convertValue);
	return true;
}

bool ConvertControl::readTraks(std::string file) {
	if (!controller.getReadTracks(file)) {
		std::cerr << "Error reading tracks data.\n";
		return false;
	}
	return true;
}

void ConvertControl::free(void) {
	controller.free();
}