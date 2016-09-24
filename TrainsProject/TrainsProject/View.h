#pragma once
#include "TripData.h"

class View
{
public:
	View();
	View(TripData tripData);

	virtual void draw() = 0;
	virtual View* handle() = 0;

	void clean();

	virtual ~View(){}
};
