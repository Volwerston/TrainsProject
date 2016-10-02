#include "TrainsView.h"
#include "StartView.h"
#include "ChooseCarView.h"

#include <conio.h>
TrainsView::TrainsView(TripData t)
{
	tripData = t;
}

void TrainsView::draw()
{
	clean();
	vector<Train> tr = getTrainsByDate(tripData.getDate(), tripData);
	suitableTrains = getSuitableTrains(tr, tripData);

	string mainLine = "#" + string(4, ' ') + "Name" + string(12, ' ') + string(16, ' ') + 
		"From/Departure Time" + string(4, ' ') + "To/Arrival Time" + string(8, ' ');
	

	setCursorAt(0, 1);
	printAtCenter(mainLine, headline); // print header of the window
	setCursorAt(0, 3);
	if (suitableTrains.empty()) // algorithm of suitable trains for the route and date
	{
		string sorry = "Sorry, there are no trains";
		printAtCenter(sorry, menuPassive);
	}
	else
	{

		int counter = 3;
		for (size_t i = 0; i < suitableTrains.size(); ++i) // print all "good" trains for day and route selected
		{
			string toPrint;

			setCursorAt(0, counter);
			counter += 2;
			stringstream ss;
			ss << suitableTrains[i].getNumber(); // number of the train
			toPrint += ss.str() + string(5 - ss.str().length(), ' '); // print it

			vector<Station> stations = suitableTrains[i].getVectorOfStations();

			string nameString = stations[0].getName() + "-" + stations[stations.size() - 1].getName(); // name of the train

			toPrint += nameString + string(32 - nameString.length(), ' '); // print it

			string fromStation = tripData.getDeparturePoint() + "/";

			for (int i = 0; i < stations.size(); ++i) // departure point and time
			{
				if (stations[i].getName() == tripData.getDeparturePoint())
				{
					fromStation += stations[i].getTimeOfDeparture();
					break;
				}
			}

			toPrint += fromStation + string(23 - fromStation.size(), ' '); // print it

			string toStation = tripData.getArrivalPoint() + "/"; 

			for (int i = 0; i < stations.size(); ++i) // arrival point and time
			{
				if (stations[i].getName() == tripData.getArrivalPoint())
				{
					toStation += stations[i].getTimeOfArrival();
					break;
				}
			}

			toPrint += toStation + string(23 - toStation.size(), ' '); // print it

			trains.push_back(toPrint); // push text to vector of trains (just its text)
		}

	}

	trains.push_back("Go back");
}

View* TrainsView::handle()
{
	bool chosen = false;
	unsigned numOfCar;

	View* nextView = nullptr;
	int currItem = 0;

	for (int i = 0; i < trains.size(); ++i) // print all the trains
	{
		setCursorAt(0, 5 + 2 * i);

		if (i == currItem) // print selected train
		{
			printAtCenter(trains[i], menuActive);
		}
		else // print non-selected train
		{
			printAtCenter(trains[i], menuPassive);
		}
	}

	int prevItem = 0;

	while (!chosen)
	{
		switch (_getch())
		{
		case 224: // one of the arrows
			switch (_getch())
			{
			case UP: // menu up
				prevItem = currItem;

				if (currItem == 0)
				{
					currItem = trains.size() - 1; // go to button "Go back" if scrolled over first train
				}
				else
				{
					--currItem;
				}

				setCursorAt(0, 5 + 2 * prevItem);
				printAtCenter(trains[prevItem], menuPassive); // print previous train as passive
				setCursorAt(0, 5 + 2 * currItem);
				printAtCenter(trains[currItem], menuActive); // print current train as active ( selected )
				break;
			case DOWN: // menu down
				prevItem = currItem;

				if (currItem == trains.size() - 1) // go to first if scrolled over "Go back" button
				{
					currItem = 0;
				}
				else
				{
					++currItem;
				}

				setCursorAt(0, 5 + 2 * prevItem);
				printAtCenter(trains[prevItem], menuPassive);
				setCursorAt(0, 5 + 2 * currItem);
				printAtCenter(trains[currItem], menuActive);
				break;
			}
			break;
		case VK_RETURN: // Enter

			if (currItem == trains.size() - 1) // if button "Go back" pressed, then return to previous view
			{
				nextView = new StartView(TripData());
			}
			else // if train chosen, then go to next view with this train selected
			{
				tripData.setTrain(suitableTrains[currItem]);
				nextView = new ChooseCarView(tripData);
			}
			
			chosen = true;

			break;
		}
	}

	return nextView;
}