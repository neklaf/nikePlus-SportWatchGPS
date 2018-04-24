/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.cc
 * Copyright (C) rajibe 2010 <rajibe@gmail.com>
 * 
 * comsport is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * comsport is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <fstream>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include "Controller.h"
#include "Profile.h"
#include "ConvertControl.h"

using namespace std;

struct globalArgs_t {
	string fileName;
	bool outputFile;
	bool read;
	bool formated;
} globalArgs;

void displayUsage( void ) {
	cout << "\nComsport v0.1, driver for sportband+\n";
	cout << "usage: \n";
	cout << "-h Dispay this help.\n";
	cout << "-? Display this help.\n";
	cout << "-r Read data from sportband.\n";
	cout << "-f Display format data.\n";
	cout << "-o filename	Output read data to file.\n";
	cout << "-t yyyy-mm-dd,hh:mm:ss   Change date and time.\n";
	cout << "-H [24|12]		Change time format.\n";
	cout << "-m [milles|kilometres]   Change metric format. \n";
	cout << "-w [pounds|kilos]   Change weight format. \n";
	cout << "-W value   Change weight value. \n";
	cout << "-g [man|woman]  Change gender.\n";
	cout << "-p value   Change pin value.\n";
	cout << "-U value  Change user value.\n";
	cout << "-u value  Change user value.\n";
	cout << "-b yyyy/mm/dd  Change birth value.\n";
	cout << "-c value  Change value codes.\n";
	cout << "-d filename		Dump tracks data to file.\n";
	cout << "-e  Delete all runs.\n";
	exit( EXIT_FAILURE );
}

int main(int argc, char *argv[] )
{
    cout  << "main INI\n";
	Controller controller;
	Profile profile;
	ConvertControl convertControl;
	int option;

	if (!controller.ifPlugged()) {
		cout << "\nComsport v0.1, driver for sportband+\n";
		cout << "no sportband found. \n";
		exit( EXIT_FAILURE );
	} else {
        cout << "main controller.readAllData()\n";
		controller.readAllData();
	}
	
	globalArgs.outputFile = false;
	globalArgs.read = false;
	globalArgs.formated = false;
	convertControl.setController(controller);
	
	option = getopt( argc, argv, "fro:h?t:H:m:w:W:g:p:u:U:b:c:d:e" );
	while( option != -1 ) {
		switch( option ) {
			case 'f':
					globalArgs.formated = true;
					break;
			case 'r':
					globalArgs.read = true;
					break;
			case 'o':
					globalArgs.fileName = optarg;
					globalArgs.outputFile = true;
					break;
			case 't':
					if (convertControl.setTime(optarg)) cout << "Date and hour changed ok.\n";
						else {
							cerr << "Error changing date and hour.\n";
							displayUsage();
						}
					break;
			case 'H':
					if (convertControl.changeHour(optarg)) cout << "Hour format changed ok.\n";
						else {
							cerr << "Error changing hour format.\n";
							displayUsage();
						}
					break;
			case 'm':
					if (convertControl.changeMetric(optarg)) cout << "Metric changed ok.\n";
						else {
							cerr << "Error changing metric.\n";
							displayUsage();
						}
					break;
			case 'w':
					if (convertControl.changeWeight(optarg)) cout << "Weight format changed ok.\n";
						else {
							cerr << "Error changing weight format.\n";
							displayUsage();
						}
					break;
			case 'W':
					if (convertControl.changeWeightValue(optarg)) cout << "Weight changed ok.\n";
						else {
							cerr << "Error changing weight.\n";
							displayUsage();
						}
					break;
			case 'g':
					if (convertControl.changeGender(optarg)) cout << "Gender changed ok.\n";
						else {
							cerr << "Error changing gender.\n";
							displayUsage();
						}
					break;
			case 'p':
					if (convertControl.changePin(optarg)) cout << "Pin changed ok.\n";
						else {
							cerr << "Error changing pin.\n";
							displayUsage();
						}
					break;
			case 'u':
					if (convertControl.changeUser(optarg)) cout << "User changed ok.\n";
						else {
							cerr << "Error changing user.\n";
							displayUsage();
						}
					break;
			case 'U':
					if (convertControl.changeUserLog(optarg)) cout << "User changed ok.\n";
						else {
							cerr << "Error changing user.\n";
							displayUsage();
						}
					break;
			case 'b':
					if (convertControl.changeBirth(optarg)) cout << "Birth changed ok.\n";
						else {
							cerr << "Error changing birth.\n";
							displayUsage();
						}
					break;
			case 'c':
					if (convertControl.changeCodes(optarg)) cout << "Codes changed ok.\n";
						else {
							cerr << "Error changing codes.\n";
							displayUsage();
						}
					break;
			case 'd':
					if (convertControl.readTraks(optarg)) cout << "Data dump ok.\n";						
						else displayUsage();
					break;
			case 'e':
					convertControl.free();
			case 'h':
					displayUsage();
					break;
			case '?':
					displayUsage();
					break;
			default:
				displayUsage();
				break;
		}
		option = getopt( argc, argv, "fro:h?t:H:m:w:W:g:p:u:U:b:c:d:e" );
	}

	if (globalArgs.read == true) {
        cout << "main globalArgs.read == true\n";
		string data;
		controller.readAllData();
		profile = controller.getProfile();
		if (globalArgs.formated) {
			data = profile.getDataFormat();
		} else data = profile.getData();
		if (globalArgs.outputFile ==true) {
			ofstream outFile;
			outFile.open(globalArgs.fileName.data());
			outFile << data;
			outFile.close();
		} else cout << data;
	}
	return EXIT_SUCCESS;
}
