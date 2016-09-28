#include <iostream>
#include <vector>

#include "Train.h"
#include "Algorithms.h"
#include "TripData.h"
#include "ChooseCarView.h"
#include "RailCarView.h"
#include "Console.h"

using namespace std;

int main()
{
	setConsoleProperties();
	vector<Train> trains = getTrainsByDate("2016-10-01");

	//setConsoleSize(123, 39);

	TripData tripData("2016-10-01", "ivano-frankivsk", "brody", 0, 0, vector<unsigned int>(), trains[0]);

	/*
	View* carView = new ChooseCarView(tripData);

	carView->handle();

	delete carView;
	*/

	//saveTrainsByDate(trains, "2016-10-03");

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