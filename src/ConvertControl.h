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
 #ifndef CONVERT_CONTROL_H
#define CONVERT_CONTROL_H

#include <string>
#include <vector>
#include "Controller.h"
class ConvertControl {
	private:
	Controller controller;	
	std::vector<std::string> explodeChar(char, std::string);
	std::vector<int> explodeInt(char sep, std::string src);
	public:
	void setController(Controller);
	bool setTime(std::string);
	bool changeHour(std::string);
	bool changeMetric(std::string);
	bool changeWeight(std::string);
	bool changeWeightValue(std::string);
	bool changeGender(std::string);
	bool changePin(std::string);
	bool changeUser(std::string);
	bool changeUserLog(std::string);
	bool changeBirth(std::string);
	bool changeCodes(std::string);
	bool readTraks(std::string);
	void free(void);
};
#endif