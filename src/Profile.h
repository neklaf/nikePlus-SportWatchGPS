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
#ifndef PROFILE_H
#define PROFILE_H
#include <string>
class Profile {
	private:
	bool milles;
	bool gender;
	bool pounds;
	std::string user;
	std::string pin;
	std::string birth;
	std::string logUser;
	bool codes[5];
	int weight;
	std::string convertString(char *);
	int find(unsigned char *, int,char);
	int findFrom(unsigned char *, int,int,char);
	public:
	void setMilles(char);
	bool getMilles(void);
	void setPounds(char);
	bool getPounds(void);
	void setGender(char);
	bool getGender(void);
	void setPin(unsigned char *);
	std::string getPin(void);
	void setUser(unsigned char *);
	std::string getUser(void);
	void setBirth(unsigned char *);
	std::string getBirth(void);
	void setLogUser(unsigned char *);
	std::string getLogUser(void);
	void setCode(int,bool);
	void setCodes(unsigned char *);
	bool* getCodes(void);
	void setWeight(unsigned char *);
	int getWeight(void);
	std::string getDataFormat(void);
	std::string getData(void);	
};
#endif
 