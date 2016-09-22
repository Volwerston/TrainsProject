#pragma once
#include "Printer.h"
#include "View.h"
#include "TripData.h"

class RailCarView :public View
{
private:
	string date;
	string departurePoint;
	string arrivalPoint;
	unsigned numberOfTrain;
	unsigned numberOfRailcar;
	vector<unsigned> vectorOfSeats;
public:
	RailCarView(TripData);
	void draw();
	View* handle();
};