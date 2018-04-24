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

#include "BufferControl.h"
#include "DeviceCom.h"
#include "Profile.h"
#include "Controller.h"
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

int Controller::ifPlugged(void) {
    std::cout << "Controller::ifPlugged INI" << std::endl;
	DeviceCom control;
	if (control.init() == true) {
		control.close();
		return 1;
	}
	return 0;
}

void Controller::readAllData(void) {
    std::cout << "Controller::readAllData INI" << std::endl;
	DeviceCom control;
	BufferControl buffer;
	if (control.init() == true) {
    	std::cout << "Controller::readAllData setting Milles/Kilometres" << std::endl;
		// Milles/Kilometres
		buffer.init(8);
		buffer.insertArrayString("9,2,132,50",0);
		control.write(0x21,0x9,0x209,buffer.getBuffer(),0x8);
		control.read(0xa1,0x1,0x101,buffer.getBuffer(),0x8);
		profile.setMilles(buffer.getBuffer()[3]);
		buffer.freeBuffer();

		//Pounds/Kilogrames - Gender - Pin-Email
    		std::cout << "Controller::readAllData setting Pounds/Kilograms" << std::endl;
		buffer.init(8);
		buffer.insertArrayString("9,4,82,52",0);
		control.write(0x21,0x9,0x209,buffer.getBuffer(),0x8);
		buffer.freeBuffer();
		buffer.init(64);
		control.read(0xa1,0x1,0x104,buffer.getBuffer(),0x40);
    		std::cout << "Controller::readAllData setting Pounds-> " << buffer.getBuffer()[6] << std::endl;
		profile.setPounds(buffer.getBuffer()[6]);
    		std::cout << "Controller::readAllData setting Gender-> " << buffer.getBuffer()[7] << std::endl;
		profile.setGender(buffer.getBuffer()[7]);
    		std::cout << "Controller::readAllData setting Pin-> " << buffer.getBuffer() << std::endl;
		profile.setPin(buffer.getBuffer());
    		std::cout << "Controller::readAllData setting User-> " << buffer.getBuffer() << std::endl;
		profile.setUser(buffer.getBuffer());
		buffer.freeBuffer();

		//Birth - User
		buffer.init(8);
		buffer.insertArrayString("9,4,73,52,00,58",0);
		control.write(0x21,0x9,0x209,buffer.getBuffer(),0x8);
		buffer.freeBuffer();
		buffer.init(64);
		control.read(0xa1,0x1,0x104,buffer.getBuffer(),0x40);
    		std::cout << "Controller::readAllData setting birth-> " << buffer.getBuffer() << std::endl;
		profile.setBirth(buffer.getBuffer());
    		std::cout << "Controller::readAllData setting log user-> " << buffer.getBuffer() << std::endl;
		profile.setLogUser(buffer.getBuffer());
		buffer.freeBuffer();
		
		//Codes-state
		buffer.init(8);
		buffer.insertArrayString("9,2,225,58",0);
		control.write(0x21,0x9,0x209,buffer.getBuffer(),0x8);
		buffer.freeBuffer();
		buffer.init(16);
		control.read(0xa1,0x1,0x102,buffer.getBuffer(),0x10);
    		std::cout << "Controller::readAllData setting codes-> " << buffer.getBuffer() << std::endl;
		profile.setCodes(buffer.getBuffer());
		buffer.freeBuffer();

		//Weight
		buffer.init(8);
		buffer.insertArrayString("9,2,174,51",0);
		control.write(0x21,0x9,0x209,buffer.getBuffer(),0x8);
		buffer.freeBuffer();
		buffer.init(8);
		control.read(0xa1,0x1,0x101,buffer.getBuffer(),0x8);
    		std::cout << "Controller::readAllData setting weight-> " << buffer.getBuffer() << std::endl;
		profile.setWeight(buffer.getBuffer());
		buffer.freeBuffer();
		
		control.close();
	}
    std::cout << "Controller::readAllData END" << std::endl;
 }

Profile Controller::getProfile(void) {
    std::cout << "Controller::getProfile INI" << std::endl;
	return profile;
}

void Controller::setTime(int hour,int minutes,int seconds,int day,int month, int year) {
    std::cout << "Controller::setTime INI" << std::endl;
	time_t rawtime;
	struct tm * timeinfo;
	DeviceCom control;
	BufferControl buffer;
	long timeLong;
	if (control.init() == true) {
		time ( &rawtime );
	  	timeinfo = localtime ( &rawtime );
	  	timeinfo->tm_year = year- 1900;
	  	timeinfo->tm_mon = month - 1;
	  	timeinfo->tm_mday = day;
		timeinfo->tm_sec = seconds;
		timeinfo->tm_min = minutes;
		timeinfo->tm_hour = hour;

		buffer.init(16);
		buffer.insertArrayString("10,11,48,33,0,0,0,0,0,1,67,112,1,0,0,0,0",0);
		timeLong = (long) mktime(timeinfo);
		buffer.valDump(&timeLong, sizeof timeLong, 1,4);
		control.write(0x21,0x09,0x20a,buffer.getBuffer(),0x10);
		buffer.freeBuffer();
		control.close();
	}	
    std::cout << "Controller::setTime END" << std::endl;
}

void Controller::setFormatHour(bool h24) {
    std::cout << "Controller::setFormatHour INI";
	DeviceCom control;
	BufferControl buffer;
	if (control.init() ==true) {
		buffer.init(8);
		buffer.insertArrayString("9,3,151,49",0);
		if (h24 == true) buffer.setBuffer(4, 1);
			else buffer.setBuffer(4,0);
		control.write(0x21,0x09,0x209,buffer.getBuffer(),0x8);
		buffer.freeBuffer();
		control.close();
	}
    std::cout << "Controller::setFormatHour END" << std::endl;
}

void Controller::setMilles(bool value) {
    std::cout << "Controller::setMilles INI" << std::endl;
	DeviceCom control;
	BufferControl buffer;
	if (control.init() ==true) {
		buffer.init(8);
		buffer.insertArrayString("9,3,212,50",0);
		if (value == true) buffer.setBuffer(4, 0);
			else buffer.setBuffer(4,1);
		control.write(0x21,0x09,0x209,buffer.getBuffer(),0x8);
		buffer.freeBuffer();
		control.close();
	}
    std::cout << "Controller::setMilles END" << std::endl;
}

void Controller::setWeight(int value) {
    std::cout << "Controller::setWeight INI" << std::endl;
	DeviceCom control;
	BufferControl buffer;
	float gData;
	char convert[100];
	if (control.init() ==true) {
		buffer.init(8);
		buffer.insertArrayString("9,4,234,51",0);
		if (profile.getPounds()) {
			value = value * 10;
			buffer.valDump(&value, 2, 1,4);
		} else {
			sprintf(convert,"%.1f",value*2.2046);
			value = (int) atof(convert)*10;
			buffer.valDump(&value,2, 1,4);
		}
		control.write(0x21,0x09,0x209,buffer.getBuffer(),0x8);
		buffer.freeBuffer();
		control.close();
	}
    std::cout << "Controller::setWeight END" << std::endl;
}

void Controller::setTypeWeight(bool value) {
    std::cout << "Controller::setTypeWeight INI" << std::endl;
	DeviceCom control;
	BufferControl buffer;
	if (control.init() ==true) {
		buffer.init(64);
		buffer.insertArrayString("12,61,220,52,00,00,02,00,00,24",0);
		if (profile.getGender() == true) buffer.setBuffer(8,0);
			else buffer.setBuffer(8,1);
		if (value == true) buffer.setBuffer(7,0);
			else buffer.setBuffer(7,1);

		buffer.setAppendIndex(10);
		buffer.insertAppendIndexString(profile.getPin());
		buffer.insertAppendIndexValue(16);
		buffer.insertAppendIndexString(profile.getUser());
		control.write(0x21,0x09,0x20c,buffer.getBuffer(),0x40);
		buffer.freeBuffer();
		control.close();
	}
    std::cout << "Controller::setTypeWeight END" << std::endl;
}

void Controller::setGender(bool value) {
    std::cout << "Controller::setGender INI" << std::endl;
	DeviceCom control;
	BufferControl buffer;
	if (control.init() ==true) {
		buffer.init(64);
		buffer.insertArrayString("12,61,220,52,00,00,02,00,00,24",0);
		if (value == true) buffer.setBuffer(8,0);
			else buffer.setBuffer(8,1);
		if (profile.getPounds() == true) buffer.setBuffer(7,0);
			else buffer.setBuffer(7,1);
		buffer.setAppendIndex(10);
		buffer.insertAppendIndexString(profile.getPin());
		buffer.insertAppendIndexValue(16);
		buffer.insertAppendIndexString(profile.getUser());
		control.write(0x21,0x09,0x20c,buffer.getBuffer(),0x40);
		buffer.freeBuffer();
		control.close();
	}
    std::cout << "Controller::setGender END" << std::endl;
}

void Controller::setPin(std::string value) {
    std::cout << "Controller::setPin INI" << std::endl;
	DeviceCom control;
	BufferControl buffer;
	if (control.init() ==true) {
		buffer.init(64);
		buffer.insertArrayString("12,61,220,52,00,00,02,00,00,24",0);
		if (profile.getGender() == true) buffer.setBuffer(7,0);
			else buffer.setBuffer(7,1);
		if (profile.getPounds() == true) buffer.setBuffer(8,0);
			else buffer.setBuffer(8,1);
		buffer.setAppendIndex(10);
		buffer.insertAppendIndexString(value);
		buffer.insertAppendIndexValue(16);
		buffer.insertAppendIndexString(profile.getUser());
		control.write(0x21,0x09,0x20c,buffer.getBuffer(),0x40);
		buffer.freeBuffer();
		control.close();
	}
    std::cout << "Controller::setPin END" << std::endl;
}

void Controller::setUser(std::string value) {
    std::cout << "Controller::setUser INI" << std::endl;
	DeviceCom control;
	BufferControl buffer;
	if (control.init() ==true) {
		buffer.init(64);
		buffer.insertArrayString("12,61,220,52,00,00,02,00,00,24",0);
		if (profile.getGender() == true) buffer.setBuffer(7,0);
			else buffer.setBuffer(7,1);
		if (profile.getPounds() == true) buffer.setBuffer(8,0);
			else buffer.setBuffer(8,1);
		buffer.setAppendIndex(10);
		buffer.insertAppendIndexString(profile.getPin());
		buffer.insertAppendIndexValue(16);
		buffer.insertAppendIndexString(value);
		control.write(0x21,0x09,0x20c,buffer.getBuffer(),0x40);
		buffer.freeBuffer();
		control.close();
	}
    std::cout << "Controller::setUser END" << std::endl;
}

void Controller::setCodes(int value) {
    std::cout << "Controller::setCodes INI" << std::endl;
	DeviceCom control;
	BufferControl buffer;
	int pos = 4;
	int index = 0;
	int posByte = 16;
	if (control.init() ==true) {
		buffer.init(16);
		while(posByte != 0) {
			if ( (value & posByte) == posByte) {
				buffer.setBuffer(pos,index);
				pos++;
			}
			index++;
			posByte /= 2;
			if (posByte == 2) {
				buffer.setBuffer(pos,3);
				index++;
				pos++;
			}
		}
		if ( (pos-4) > 3) {
			buffer.insertArrayString("10,7,50,58",0);
			control.write(0x21,0x09,0x20a,buffer.getBuffer(),0x10);
		} else {
			buffer.insertArrayString("9,7,50,58",0);
			control.write(0x21,0x09,0x209,buffer.getBuffer(),0x8);
		}
		buffer.freeBuffer();
		control.close();
	}
    std::cout << "Controller::setCodes END" << std::endl;
}

void Controller::setBirth(std::string birth) {
    std::cout << "Controller::setBirth INI" << std::endl;
	DeviceCom control;
	BufferControl buffer;
	if (control.init() ==true) {
		buffer.init(32);
		buffer.insertArrayStringHex("0B,1A,10,34,00,39,00,00,00,00,09",0);
		buffer.setAppendIndex(11);
		buffer.insertAppendIndexString(birth);
		buffer.insertAppendIndexValue(6);
		buffer.insertAppendIndexString(profile.getLogUser());
		control.write(0x21,0x9,0x20b,buffer.getBuffer(),0x20);
		buffer.freeBuffer();
		control.close();
	}
    std::cout << "Controller::setBirth INI" << std::endl;
}

void Controller::setLogUser(std::string logUser) {
    std::cout << "Controller::setLogUser INI" << std::endl;
	DeviceCom control;
	BufferControl buffer;
	int i;
	if (control.init() ==true) {
		buffer.init(32);
		buffer.insertArrayStringHex("0B,1A,10,34,00,39,00,00,00,00,09",0);
		buffer.setAppendIndex(11);
		buffer.insertAppendIndexString(profile.getBirth());
		buffer.insertAppendIndexValue(6);
		buffer.insertAppendIndexString(logUser);
		control.write(0x21,0x9,0x20b,buffer.getBuffer(),0x20);
		buffer.freeBuffer();
		control.close();
	}
    std::cout << "Controller::setLogUser END" << std::endl;
}

bool Controller::getReadTracks(std::string filename) {
    std::cout << "Controller::getReadTracks INI" << std::endl;
	DeviceCom control;
	BufferControl buffer;
	int offset;
	int result;
	unsigned char *data;
	std::ofstream outfile;
	if (control.init() ==true) {
		buffer.init(8);
		buffer.insertArrayStringHex("09,02,bb,12,00,00,00,00",0);
		control.write(0x21,0x9,0x209,buffer.getBuffer(),0x8);
		buffer.freeBuffer();
		buffer.init(16);
		control.read(0xa1,0x1,0x102,buffer.getBuffer(),0x10);
		if ( (buffer.getBuffer()[7]>0) || (buffer.getBuffer()[8]>0)) {
			//get runs
			outfile.open(filename.data(),std::ofstream::binary);
			offset = 0;
			do {
				buffer.freeBuffer();
				buffer.init(8);
				buffer.insertArrayStringHex("09,05,96,10,00,00,00,00",0);
				buffer.valDump(&offset, 2, 1,5);
				control.write(0x21,0x9,0x209,buffer.getBuffer(),0x8);
				buffer.freeBuffer();
				buffer.init(64);
				result = control.readInt(0xa1,0x1,0x104,buffer.getBuffer(),0x40);
				data = buffer.getBuffer();
				outfile.write ((char *)&data[7],result-7);
				offset = offset + (result-7);
			} while (data[3] == 1);
			buffer.freeBuffer();
			outfile.close();
		} else {
			buffer.freeBuffer();
		}
		return true;
	}
	return false;	
}

void Controller::free(void) {
    std::cout << "Controller::free INI" << std::endl;
	DeviceCom control;
	BufferControl buffer;
	int i=0;
	if (control.init() ==true) {
		buffer.init(8);
		buffer.insertArrayStringHex("09,04,45,11,EE,86,00,00",0);
		control.write(0x21,0x9,0x209,buffer.getBuffer(),0x8);
		buffer.freeBuffer();
		buffer.init(8);
		buffer.insertArrayStringHex("09,02,3B,11,00,00,00,00",0);
		control.write(0x21,0x9,0x209,buffer.getBuffer(),0x8);
		buffer.freeBuffer();
		buffer.init(7);
		control.read(0xa1,0x1,0x101,buffer.getBuffer(),0x7);
		buffer.freeBuffer();
		control.close();
	}
    std::cout << "Controller::free END" << std::endl;
}
