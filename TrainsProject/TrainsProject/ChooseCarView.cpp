#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#include  "ChooseCarView.h"
#include "Route.h"
#include "RailCarView.h"
#include "RailCar.h"
#include "TrainsView.h"

template<typename T>
string toString(const T& t)
{
	ostringstream oStream;
	oStream << t;

	return oStream.str();
}


// checks whether two routes, that contain stations from vector<Station>, intersect
bool intersect(Route r1, Route r2, vector<Station>& st)
{
	bool toReturn = false;

	if (r1.getArrivalStation() != r2.getDepartureStation() && r1.getDepartureStation() != r1.getArrivalStation())
	{
		bool secondRouteStarted = false;

		for (size_t i = 0; i < st.size(); ++i)
		{
			if (r2.getArrivalStation() == st[i].getName())
			{
				if (secondRouteStarted)
				{
					toReturn = true;
				}
				break;
			}

			if (r1.getDepartureStation() == st[i].getName())
			{
				secondRouteStarted = true;
			}
		}
	}

	return toReturn;
}
 
ChooseCarView::ChooseCarView(const TripData& t)
	: tripData(t)
{
}

void ChooseCarView::draw()
{
	View::clean();

	setCursorAt(0, 1);
	string mask = "#    Type         Price     Places    Free places    ";
	printAtCenter(mask, headline);

	Train aTrain = tripData.getTrain();
	vector<RailCar> railCars = aTrain.getVectorOfRailCars();
	vector<Route> routes = aTrain.getVectorOfRoutes();
	vector<Station> stations = aTrain.getVectorOfStations();

	int numOfCars = railCars.size();

	// vector of vector<bool>, where true = seat is booked; false = seat is free
	trainSnippet.resize(railCars.size());

	for (size_t i = 0; i < trainSnippet.size(); ++i)
	{
		trainSnippet[i] = vector<bool>(railCars[i].getNumberOfSeats(), false);
	}

	Route chosenRoute(tripData.getDeparturePoint(), tripData.getArrivalPoint());

	for (size_t i = 0; i < routes.size(); ++i)
	{
		if (intersect(chosenRoute, routes[i], stations))
		{

			vector<RailCar> bookingData = routes[i].getBookingData();

			// takes a "snippet" of booked tickets in this train
			for (size_t j = 0; j < bookingData.size(); ++j)
			{
				for (size_t k = 0; k < bookingData[j].getVectotOfBookedSeats().size(); ++k)
				{
					trainSnippet[bookingData[j].getNumber() - 1][bookingData[j].getVectotOfBookedSeats()[k] - 1] = true;
				}
			}
		}
	}


	// output all railcars one-by-one
	for (size_t i = 0; i < tripData.getTrain().getVectorOfRailCars().size(); ++i)
	{
		int numOfFreeSeats = railCars[i].getNumberOfSeats() - std::count(trainSnippet[i].begin(), trainSnippet[i].end(), true);
		string toPrint;

		// number of railcar
		toPrint += toString(railCars[i].getNumber()) + string(3 - toString(railCars[i].getNumber()).size(), ' ');

		string railCarType;
		string price;

		
		if (railCars[i].getType() == TypeOfRailCar::FirstClass)
		{
			railCarType = "Deluxe";
			price = "40";
		}
		else if (railCars[i].getType() == TypeOfRailCar::SecondClass)
		{
			railCarType = "Compartment";
			price = "20";
		}
		else
		{
			railCarType = "Reserved Seat";
			price = "10";
		}

		// type of railcar && number of seats
		toPrint += " " + railCarType + string(14 - railCarType.size(), ' ');
		toPrint += " " + price + string(9 - price.size(), ' ');
		toPrint += " " + toString(railCars[i].getNumberOfSeats()) + string(9 - toString(railCars[i].getNumberOfSeats()).size(), ' ');
		toPrint += " " + toString(numOfFreeSeats) + string(14 - toString(numOfFreeSeats).size(), ' ');

		chooseOptions.push_back(toPrint);
	}


	// nexessary "Go back" option
	chooseOptions.push_back("Go back");
}

void ChooseCarView::printOptions(int currItem)
{
	for (int i = 0; i < chooseOptions.size(); ++i)
	{
		setCursorAt(0, 3 + 2 * i);

		if (i == currItem)
		{
			printAtCenter(chooseOptions[i], menuActive);
		}
		else
		{
			printAtCenter(chooseOptions[i], menuPassive);
		}
	}
}

View* ChooseCarView::handle()
{
	bool chosen = false;
	unsigned numOfCar;

	View* toReturn = nullptr;
	int currItem = 0;

	printOptions(currItem);

	int prevItem = 0;

	while (!chosen)
	{
		switch (_getch())
		{
		case ARROW_KEY: // one of the arrows
			switch (_getch())
			{
			case UP: // menu up
				prevItem = currItem;

				if (currItem == 0)
				{
					currItem = chooseOptions.size() - 1;
				}
				else
				{
					--currItem;
				}

				// redraws previously and currently chosen options
				setCursorAt(0, 3 + 2*prevItem);
				printAtCenter(chooseOptions[prevItem], menuPassive);
				setCursorAt(0, 3 + 2*currItem);
				printAtCenter(chooseOptions[currItem], menuActive);
				break;
			case DOWN:  // menu down
				prevItem = currItem;

				if (currItem == chooseOptions.size() - 1)
				{
					currItem = 0;
				}
				else
				{
					++currItem;
				}

				// redraws previously and currently chosen options
				setCursorAt(0, 3 + 2*prevItem);
				printAtCenter(chooseOptions[prevItem], menuPassive);
				setCursorAt(0, 3 + 2*currItem);
				printAtCenter(chooseOptions[currItem], menuActive);
				break;
			}
			break;
		case VK_RETURN: // Enter

			if (currItem == chooseOptions.size() - 1) // Go back
			{
				toReturn = new TrainsView(tripData); 
				chosen = true;
			}
			else // Railcar was chosen
			{

				int numOfBookedPlaces = std::count(trainSnippet[currItem].begin(), trainSnippet[currItem].end(), true);
				RailCar buf = tripData.getTrain().getVectorOfRailCars()[currItem];

				// if not all seats are booked
				if (buf.getNumberOfSeats() != numOfBookedPlaces)
				{
					// sets tripData configuration and redirects to the RailCarView
					numOfCar = currItem + 1;

					tripData.setNumberOfRailcar(numOfCar);

					Train aTrain = Train();
					vector<RailCar> railCars = tripData.getTrain().getVectorOfRailCars();

					for (int i = 0; i < trainSnippet.size(); ++i)
					{
						for (int j = 0; j < trainSnippet[i].size(); ++j)
						{
							if (trainSnippet[i][j]) // seat is booked
							{
								railCars[i].pushSeatToVectorOfBookedSeats(j);
							}
						}
					}

					// sets data of booked seats in all railcars
					tripData.setDataOfBookedSeats(railCars);

					toReturn = new RailCarView(tripData);
					chosen = true;
				}
			}
			break;
		}
	}

	return toReturn;
}