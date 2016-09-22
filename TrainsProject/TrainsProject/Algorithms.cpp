#include <iostream>
#include <vector>
#include <string>

#include "tinyxml2\tinyxml2.h"
#include "Algorithms.h"
#include "RailCar.h"
#include "Station.h"

using namespace tinyxml2;
using namespace std;

vector<Train> getTrainsByDate(const string& date)
{
	vector<Train> toReturn;

	string filePath = "Database/" + date + ".xml";

	XMLDocument trainsData;
	XMLError err = trainsData.LoadFile(filePath.c_str());

	if (err == XML_SUCCESS)
	{
		Train currTrain;

		XMLElement* train = trainsData.FirstChildElement("Train");

		while (train != nullptr)
		{
			XMLElement* trainNumber = train->FirstChildElement("Number");
			int numberOfTrain;
			trainNumber->QueryIntText(&numberOfTrain);
			currTrain.setNumber(numberOfTrain);

			XMLElement* railCar = train->FirstChildElement("RailCar");

			while (railCar != nullptr)
			{
				RailCar railCarBuf;
				int number;
				int numOfSeats;
				string typeOfCar;


				XMLElement* railCarNumber = railCar->FirstChildElement("Number");
				railCarNumber->QueryIntText(&number);
				XMLElement* railCarType = railCar->FirstChildElement("Type");
				typeOfCar = railCarType->GetText();
				XMLElement* seatsNumber = railCar->FirstChildElement("Seats");
				railCarNumber->QueryIntText(&numOfSeats);
				
				railCarBuf.setNumber(number);
				railCarBuf.setNumberOfSeats(numOfSeats);

				if (typeOfCar == "L")
				{
					railCarBuf.setType(TypeOfRailCar::FirstClass);
				}
				else if (typeOfCar == "K")
				{
					railCarBuf.setType(TypeOfRailCar::SecondClass);
				}
				else if (typeOfCar == "P")
				{
					railCarBuf.setType(TypeOfRailCar::ThirdClass);
				}
				else
				{
					railCarBuf.setType(TypeOfRailCar::DiningCar);
				}

				currTrain.pushRailCarToVectorOfRailCars(railCarBuf);

				railCar = railCar->NextSiblingElement("RailCar");
			}

			XMLElement* departurePlace = train->FirstChildElement("Departure");

			Station depart;

			string departName;
			string departTime;

			// read departure station

			XMLElement* departureName = departurePlace->FirstChildElement("Name");
			departName = departureName->GetText();
			XMLElement* departureTime = departurePlace->FirstChildElement("Time");
			departTime = departureTime->GetText();

			depart.setName(departName);
			depart.setTimeOfDeparture(date + " " + departTime);

			currTrain.pushStationToVectorOfStations(depart);

			// read transitional stations

			XMLElement* transition = train->FirstChildElement("Transition");

			while (transition != nullptr)
			{
				Station transitionalStation;

				string transitionName;
				string arrivalTime;
				string arrivalDate;
				string departureTime;
				string departureDate;

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

				transitionalStation.setName(transitionName);
				transitionalStation.setTimeOfArrival(arrivalDate + " " + arrivalTime);
				transitionalStation.setTimeOfDeparture(departureDate + " " + departureTime);

				currTrain.pushStationToVectorOfStations(transitionalStation);

				transition = transition->NextSiblingElement("Transition");
			}

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

			while (route != nullptr)
			{
				Route currRoute;

				string firstStation;
				string lastStation;

				XMLElement* from = route->FirstChildElement("From");
				firstStation = from->GetText();
				XMLElement* to = route->FirstChildElement("To");
				lastStation = to->GetText();

				currRoute.setDepartureStation(firstStation);
				currRoute.setArrivalStation(lastStation);

				vector<RailCar> routeBookingData;

				XMLElement* railCar = route->FirstChildElement("RailCar");

				while (railCar != nullptr)
				{
					RailCar railCarBuf;

					XMLElement* railCarNum = railCar->FirstChildElement("Number");

					int numOfRailCar;

					railCarNum->QueryIntText(&numOfRailCar);

					railCarBuf.setNumber(numOfRailCar);

					XMLElement* bookedSeats = railCar->FirstChildElement("Seat");

					while (bookedSeats != nullptr)
					{
						int seatNum;
						bookedSeats->QueryIntText(&seatNum);
						railCarBuf.pushSeatToVectorOfBookedSeats(seatNum);
						bookedSeats = bookedSeats->NextSiblingElement("Seat");
					}

					routeBookingData.push_back(railCarBuf);

					railCar = railCar->NextSiblingElement("RailCar");
				}

				currRoute.setBookingData(routeBookingData);
				
				currTrain.pushRouteToVectorOfRoutes(currRoute);

				route = route->NextSiblingElement("Route");
			}

			toReturn.push_back(currTrain);

			train = train->NextSiblingElement("Train");
		}
	}

	return toReturn;
}