#pragma once
#include "TripData.h"
#include <Windows.h> 

class View
{
public:
	View();
	View(TripData tripData);

	virtual void draw() = 0;
	virtual View* handle() = 0;

	void clean();
	void View::drawBackground(int, int, int, int, COLORREF);

	virtual ~View(){}
};
