#include <stdio.h>
#include "stdafx.h"
#include <cstdio>
#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class plane {
	string planeID;
	int rows, columns, aisles;
public:
	plane(string, int rows, int columns, int aisles);

	int getRows() {
		return rows;
	}

	int getColumns() {
		return columns;
	}

	int getAisles() {
		return aisles;
	}
};

class flight {
	plane planeDetails;
	string departureTime, arrivalTime;
public:
	flight(string flightID, plane planeDetails, string departureTime, string arrivalTime);
	string flightID;
	int rows, columns, aisles;

	//Generate a new seating chart file
	void generateSeatingChart() {
		ofstream flightFile;
		flightFile.open(flightID + ".txt");
		for (int i = 0; i < (rows * columns) + 1; i++) {
			flightFile << "O" << endl;
		}
		flightFile.close();
	}

	//Print an existing seating chart
	void printSeatingChart() {
		string emptyCheck;
		string tempString;
		string seatingChart;

		ifstream flightFile;
		flightFile.open(flightID + ".txt");

		getline(flightFile, emptyCheck);

		if (emptyCheck == "") {
			generateSeatingChart();
		}

		while (flightFile.is_open()) {
			for (int i = 0; i < columns; i++) {
				for (int j = 0; j < rows; j++) {
					getline(flightFile, tempString);
					seatingChart += tempString;
				}
				seatingChart += "\n";
				if (i == aisles - 1 || i == columns - aisles - 1) {
					seatingChart += "\n";
				}
			}
			flightFile.close();
		}
		cout << seatingChart << endl;
	}

	//Checks to see if a seat is already booked
	bool checkSeat(int row, int column) {
		string seatValue;
		int seatID = ((((column - 1) * rows) + row));

		ifstream flightFile;
		flightFile.open(flightID + ".txt");
		for (int i = 0; i < seatID + 1; i++) {
			getline(flightFile, seatValue);
			if (i == seatID && seatValue == "X") {
				return false;
			}
		}
		return true;
	}

	//Adds a booked seat to the booking chart of a flight
	void addBooking(int row, int column) {
		int seatID = ((((column - 1) * rows) + row));
		string seatValue;
		ifstream inputFlightFile;
		ofstream outputFlightFile;
		inputFlightFile.open(flightID + ".txt");
		outputFlightFile.open(flightID + "-temp.txt");

		while (inputFlightFile.is_open()) {
			for (int i = 0; i < (rows * columns) + 1; i++) {
				getline(inputFlightFile, seatValue);
				if (i != seatID) {
					if (seatValue == "O") {
						outputFlightFile << "O\n";
					}
					else if (seatValue == "X") {
						outputFlightFile << "X\n";
					}
				}
				else {
					outputFlightFile << "X\n";
				}
			}
			inputFlightFile.close();
			outputFlightFile.close();

			ifstream  newFile(flightID + "-temp.txt", ios::binary);
			ofstream  oldFile(flightID + ".txt", ios::binary);

			oldFile << newFile.rdbuf();

			oldFile.close();
			newFile.close();
			remove((flightID + "-temp.txt").c_str());
		}
	}

};