#include <iostream>
#include <sstream>
#include <vector>

#include "Train.h"
#include "Algorithms.h"
#include "ChooseCarView.h"
#include "RailCarView.h"
#include "StartView.h"
#include "TrainsView.h"

template<typename T>
string toString(T dat)
{
	ostringstream oStream;
	oStream << dat;
	return oStream.str();
}

using namespace std;

int main()
{
	setConsoleProperties();	
	
	View *view = new StartView(TripData());
	while (view != nullptr)
	{
		view->draw();
		View* newView = view->handle();
		if (newView != view)
		{
			delete view;
			view = newView;
		}
	}

	return 0;
}