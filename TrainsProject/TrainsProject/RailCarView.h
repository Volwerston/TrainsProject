#pragma once
#include <conio.h>

#include "Printer.h"
#include "View.h"
#include "TripData.h"
#include "Console.h"
#include "Train.h"
#include "RailCar.h"
#include "TripData.h"
#include "ChooseCarView.h"

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