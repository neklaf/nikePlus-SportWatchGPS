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
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdio.h>
#include "Profile.h"

class Controller {
	private:
	Profile profile;
	public:
	int ifPlugged(void);
	void readAllData(void);
	Profile getProfile(void);
	void setTime(int,int,int,int,int, int);
	void setFormatHour(bool);
	void setMilles(bool);
	void setWeight(int);
	void	setTypeWeight(bool);
	void setGender(bool);
	void setPin(std::string);
	void setUser(std::string value);
	void setCodes(int);
	void setBirth(std::string);
	void setLogUser(std::string);
	bool getReadTracks(std::string);
	void free(void);
};
#endif
 