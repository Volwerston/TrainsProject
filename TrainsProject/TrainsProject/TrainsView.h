#pragma once

#include <string>
#include <vector>

#include "View.h"
#include "Algorithms.h"
#include "Console.h"
#include "Train.h"

class TrainsView : public View
{
	TripData tripData;
	vector<string> trains;
	vector<Train> suitableTrains;
public:
	TrainsView(TripData);
	void draw();
	View* handle();
};