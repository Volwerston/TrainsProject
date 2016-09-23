#include <iostream>
#include <vector>
#include <string>

#include "tinyxml2\tinyxml2.h"
#include "Algorithms.h"
#include "RailCar.h"
#include "Station.h"

using namespace tinyxml2;
using namespace std;



RailCar readRailCar(XMLElement* railCar)
{

	RailCar toReturn;
	int number;
	int numOfSeats;
	string typeOfCar;

	// gets railcar's number/type/number of seats
	XMLElement* railCarNumber = railCar->FirstChildElement("Number");
	railCarNumber->QueryIntText(&number);
	XMLElement* railCarType = railCar->FirstChildElement("Type");
	typeOfCar = railCarType->GetText();
	XMLElement* seatsNumber = railCar->FirstChildElement("Seats");
	railCarNumber->QueryIntText(&numOfSeats);

	toReturn.setNumber(number);
	toReturn.setNumberOfSeats(numOfSeats);

	if (typeOfCar == "L")
	{
		toReturn.setType(TypeOfRailCar::FirstClass);
	}
	else if (typeOfCar == "K")
	{
		toReturn.setType(TypeOfRailCar::SecondClass);
	}
	else if (typeOfCar == "P")
	{
		toReturn.setType(TypeOfRailCar::ThirdClass);
	}
	else
	{
		toReturn.setType(TypeOfRailCar::DiningCar);
	}

	return toReturn;
}

Station readStation(XMLElement* transition)
{
	Station toReturn;

	string transitionName;
	string arrivalTime;
	string arrivalDate;
	string departureTime;
	string departureDate;

	// gets stations' name/ time of arrival / time of departure /
	XMLElement* nameOfStation = transition->FirstChildElement("Name");
	transitionName = nameOfStation->GetText();

	XMLElement* arriveData = transition->FirstChildElement("Arrive");
	XMLElement* arriveTime = arriveData->FirstChildElement("Time");
	arrivalTime = arriveTime->GetText();
	XMLElement* arriveDate = arriveData->FirstChildElement("Date");
	arrivalDate = arriveDate->GetText();

	XMLElement* departData = transition->FirstChildElement("Leave");
	XMLElement* departTime = departData->FirstChildElement("Time");
	departureTime = departTime->GetText();
	XMLElement* departDate = departData->FirstChildElement("Date");
	departureDate = departDate->GetText();

	toReturn.setName(transitionName);
	toReturn.setTimeOfArrival(arrivalDate + " " + arrivalTime);
	toReturn.setTimeOfDeparture(departureDate + " " + departureTime);

	return toReturn;
}

RailCar readBookedSeats(XMLElement* railCar)
{
	RailCar toReturn;

	// gets the number of railcar
	XMLElement* railCarNum = railCar->FirstChildElement("Number");

	int numOfRailCar;

	railCarNum->QueryIntText(&numOfRailCar);

	toReturn.setNumber(numOfRailCar);

	XMLElement* bookedSeats = railCar->FirstChildElement("Seat");
	 
	// gets numbers of booked seats in the railcar
	while (bookedSeats != nullptr)
	{
		int seatNum;
		bookedSeats->QueryIntText(&seatNum);
		toReturn.pushSeatToVectorOfBookedSeats(seatNum);
		bookedSeats = bookedSeats->NextSiblingElement("Seat");
	}

	return toReturn;
}


Route readRoute(XMLElement* route)
{
	Route toReturn;

	string firstStation;
	string lastStation;

	// gets route's first / last station
	XMLElement* from = route->FirstChildElement("From");
	firstStation = from->GetText();
	XMLElement* to = route->FirstChildElement("To");
	lastStation = to->GetText();

	toReturn.setDepartureStation(firstStation);
	toReturn.setArrivalStation(lastStation);

	vector<RailCar> routeBookingData;

	XMLElement* railCar = route->FirstChildElement("RailCar");

	while (railCar != nullptr)
	{
		RailCar railCarBuf = readBookedSeats(railCar);
		routeBookingData.push_back(railCarBuf);
		railCar = railCar->NextSiblingElement("RailCar");
	}

	toReturn.setBookingData(routeBookingData);

	return toReturn;
}

vector<Train> getTrainsByDate(const string& date)
{
	vector<Train> toReturn;


	// loads data
	string filePath = "Database/" + date + ".xml";

	XMLDocument trainsData;
	XMLError err = trainsData.LoadFile(filePath.c_str());

	if (err == XML_SUCCESS)
	{
		Train currTrain;

		XMLElement* train = trainsData.FirstChildElement("Train");

		while (train != nullptr)
		{

			// gets the number of train
			XMLElement* trainNumber = train->FirstChildElement("Number");
			int numberOfTrain;
			trainNumber->QueryIntText(&numberOfTrain);
			currTrain.setNumber(numberOfTrain);

			XMLElement* railCar = train->FirstChildElement("RailCar");

			// gets the data about all railcars in the train
			while (railCar != nullptr)
			{
				RailCar railCarBuf = readRailCar(railCar);
				currTrain.pushRailCarToVectorOfRailCars(railCarBuf);
				railCar = railCar->NextSiblingElement("RailCar");
			}

			XMLElement* departurePlace = train->FirstChildElement("Departure");

			Station depart;

			string departName;
			string departTime;

			// read the departure station
			XMLElement* departureName = departurePlace->FirstChildElement("Name");
			departName = departureName->GetText();
			XMLElement* departureTime = departurePlace->FirstChildElement("Time");
			departTime = departureTime->GetText();

			depart.setName(departName);
			depart.setTimeOfDeparture(date + " " + departTime);

			currTrain.pushStationToVectorOfStations(depart);

			XMLElement* transition = train->FirstChildElement("Transition");

			// gets transitional station
			while (transition != nullptr)
			{
				Station transitionalStation = readStation(transition);
				currTrain.pushStationToVectorOfStations(transitionalStation);
				transition = transition->NextSiblingElement("Transition");
			}

			// gets the arrival station
			XMLElement* arrivalPoint = train->FirstChildElement("Arrival");
			Station arrivalStation;
			string arrivalName;
			string arrivalTime;
			string arrivalDate;

			XMLElement* arriveName = arrivalPoint->FirstChildElement("Name");
			arrivalName = arriveName->GetText();
			XMLElement* arriveTime = arrivalPoint->FirstChildElement("Time");
			arrivalTime = arriveTime->GetText();
			XMLElement* arriveDate = arrivalPoint->FirstChildElement("Date");
			arrivalDate = arriveDate->GetText();

			arrivalStation.setName(arrivalName);
			arrivalStation.setTimeOfArrival(arrivalDate + " " + arrivalTime);

			currTrain.pushStationToVectorOfStations(arrivalStation);

			XMLElement* route = train->FirstChildElement("Route");

			// gets all booked routes 
			while (route != nullptr)
			{
				Route currRoute = readRoute(route);
				currTrain.pushRouteToVectorOfRoutes(currRoute);
				route = route->NextSiblingElement("Route");
			}

			toReturn.push_back(currTrain);

			// go to next train
			train = train->NextSiblingElement("Train");
		}
	}

	return toReturn;
}