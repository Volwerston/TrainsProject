#pragma once

#include <string>
#include "RailCar.h"
#include <vector>

using namespace std;

class Route
{
	string departureStation;
	string arrivalStation;
	vector<RailCar> bookingData;
public:
	Route(const string& = " ", const string& = " ");

	string getDepartureStation() const;

	string getArrivalStation() const;

	vector<RailCar> getBookingData() const;

	void setDepartureStation(const string);

	void setArrivalStation(const string&);

	void setBookingData(vector<RailCar>& vec);
};