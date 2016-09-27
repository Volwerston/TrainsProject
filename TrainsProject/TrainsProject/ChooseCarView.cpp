#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#include  "ChooseCarView.h"
#include "Route.h"
#include "RailCarView.h"
#include "RailCar.h"

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

		setCursorAt(0, 3+i);
		printAtCenter(toPrint, stats);
	}
}

View* ChooseCarView::handle()
{
	draw();

	bool notChosen = true;
	unsigned numOfCar;

	while (notChosen)
	{
		cout << "Choose railcar: ";
		cin >> numOfCar;

		if (numOfCar == -1)  // -1 - go back (I'll correct this A.S.A.P :)
		{
			notChosen = false;
		}
		else if (numOfCar > 0)
		{
			
			if (numOfCar <= tripData.getTrain().getVectorOfRailCars().size())
			{
				int numOfFreeSeats = tripData.getTrain().getVectorOfRailCars()[numOfCar - 1].getNumberOfSeats() - std::count(trainSnippet[numOfCar - 1].begin(), trainSnippet[numOfCar - 1].end(), true);

				if (numOfFreeSeats > 0)
				{
					notChosen = false;
				}
			}
		}
	}

	View* toReturn;

	if (numOfCar == -1)
	{
		toReturn = nullptr; // must be TrainsView!
	}
	else
	{
		tripData.setNumberOfRailcar(numOfCar);

		Train aTrain = Train();
		vector<RailCar> railCars = tripData.getTrain().getVectorOfRailCars();

		for (int i = 0; i < trainSnippet.size(); ++i)
		{
			for (int j = 0; j < trainSnippet[i].size(); ++j)
			{
				if (trainSnippet[i][j])
				{
					railCars[i].pushSeatToVectorOfBookedSeats(j);
				}
			}
		}

		tripData.setDataOfBookedSeats(railCars);

		// you can find out the type of car by calling tripData.getTrain().getVectorOfRailCars()[tripData.getNumberOfRailCar() - 1].getType();

		toReturn = new RailCarView(tripData);
	}

	return toReturn;
}