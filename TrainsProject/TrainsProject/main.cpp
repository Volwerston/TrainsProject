#include <iostream>
#include <vector>

#include "Train.h"
#include "Algorithms.h"
#include "TripData.h"
#include "ChooseCarView.h"

using namespace std;

int main()
{
	vector<Train> trains = getTrainsByDate("2016-10-01");

	TripData tripData("2016-10-02", "ivano-frankivsk", "brody", 0, 0, vector<unsigned int>(), trains[0]);

	/*
	View* carView = new ChooseCarView(tripData);

	carView->handle();

	delete carView;
	*/

	saveTrainsByDate(trains, "2016-10-03");

	system("pause");
	return 0;
}