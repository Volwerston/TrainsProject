#pragma once

#include <string>
#include "View.h"
#include "TripData.h"

class ChooseCarView : public View
{
	TripData tripData;
	vector<vector<bool> > trainSnippet;
	vector<string> chooseOptions;

	void printOptions(int);
public:
	ChooseCarView(const TripData& t = TripData());

	void draw();

	View* handle();
}; 