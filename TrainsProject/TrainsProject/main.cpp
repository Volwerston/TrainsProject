#include <iostream>
#include <sstream>
#include <vector>

#include "Train.h"
#include "Algorithms.h"
#include "ChooseCarView.h"
#include "RailCarView.h"
#include "StartView.h"

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
	vector<Train> trains = getTrainsByDate("2016-10-03");

	//setConsoleSize(123, 39);

	TripData tripData("2016-10-03", "ivano-frankivsk", "brody", 0, 0, vector<unsigned int>(), trains[0]);

	/*
	View* carView = new ChooseCarView(tripData);

	carView->handle();

	delete carView;
	*/

	//saveTrainsByDate(trains, "2016-10-03");
	//TripData tripData = TripData();
	//View *view = new ChooseCarView(tripData);
	
	
	View *view = new ChooseCarView(tripData);
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
	
	

	system("pause");
	return 0;
}