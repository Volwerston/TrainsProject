#pragma once

#include "View.h"
#include "TripData.h"

class ChooseCarView : public View
{
	TripData tripData;
	vector<vector<bool> > trainSnippet;
public:
	ChooseCarView(const TripData& t = TripData());

	void draw();

	View* handle();
};