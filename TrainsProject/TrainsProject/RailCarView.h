#pragma once
#include "Printer.h"
#include "View.h"
#include "TripData.h"
#include "Console.h"
#include <conio.h>
#include "Train.h"
#include "RailCar.h"
#include "TripData.h"

class RailCarView :public View
{
private:
	TripData tripData;
public:
	RailCarView(TripData);
	void drawSeat(int);
	void drawSold(vector<unsigned>, int);
	void drawSelected(int);
	void draw();
	View* handle();
};