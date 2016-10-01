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
	unsigned num;

	railCar->QueryUnsignedAttribute("number", &num);
	toReturn.setNumber(num);

	string type = railCar->Attribute("type");

	if (type == "L")
	{
		toReturn.setType(TypeOfRailCar::FirstClass);
		toReturn.setNumberOfSeats(4);
	}
	else if (type == "K")
	{
		toReturn.setType(TypeOfRailCar::SecondClass);
		toReturn.setNumberOfSeats(16);
	}
	else
	{
		toReturn.setType(TypeOfRailCar::ThirdClass);
		toReturn.setNumberOfSeats(24);
	}

	return toReturn;
}

Station readStation(XMLElement* station)
{
	Station toReturn;

	string stationName;
	string arrivalTime;
	string departureTime;

	stationName = station->Attribute("name");
	departureTime = station->Attribute("leaveTime");
	arrivalTime = station->Attribute("arriveTime");

	toReturn.setName(stationName);
	toReturn.setTimeOfArrival(arrivalTime);
	toReturn.setTimeOfDeparture(departureTime);

	return toReturn;
}

Route readRoute(XMLElement* route)
{
	Route toReturn;

	string startPoint = route->Attribute("startPoint");
	string endPoint = route->Attribute("endPoint");

	toReturn.setDepartureStation(startPoint);
	toReturn.setArrivalStation(endPoint);

	vector<RailCar> bookingData;

	XMLElement* bookedCar = route->FirstChildElement("RailCar");

	while (bookedCar != nullptr)
	{
		RailCar aCar;
		unsigned num;

		bookedCar->QueryUnsignedAttribute("number", &num);

		aCar.setNumber(num);

		XMLElement* bookedSeat = bookedCar->FirstChildElement("BookedSeat");

		while (bookedSeat != nullptr)
		{
			unsigned seatNum;

			bookedSeat->QueryUnsignedText(&seatNum);
			aCar.pushSeatToVectorOfBookedSeats(seatNum);

			bookedSeat = bookedSeat->NextSiblingElement("BookedSeat");
		}

		bookingData.push_back(aCar);

		bookedCar = bookedCar->NextSiblingElement("RailCar");
	}

	toReturn.setBookingData(bookingData);

	return toReturn;
}

vector<Train> getTrainsByDate(const string& date, TripData& tr)
{
	vector<Train> toReturn;

	tr.setDate(date);

	// loads data
	string filePath = "Database/" + date + ".xml";

	XMLDocument trainsData;
	XMLError err = trainsData.LoadFile(filePath.c_str());

	if (err == XML_SUCCESS)
	{
		XMLNode* root = trainsData.FirstChild();

		XMLElement* train = root->FirstChildElement("Train");

		while (train != nullptr)
		{
			Train aTrain;

			unsigned num;
			train->QueryUnsignedAttribute("number", &num);

			aTrain.setNumber(num);

			XMLElement* railCar = train->FirstChildElement("RailCar");

			while (railCar != nullptr)
			{
				RailCar toPush = readRailCar(railCar);
				aTrain.pushRailCarToVectorOfRailCars(toPush);
				railCar = railCar->NextSiblingElement("RailCar");
			}


			XMLElement* departure = train->FirstChildElement("Departure");

			Station toPush;


			// read departure station
			string stationName = departure->Attribute("name");
			string departureTime = departure->Attribute("leaveTime");
			string arrivalTime;

			toPush.setName(stationName);
			toPush.setTimeOfDeparture(departureTime);

			aTrain.pushStationToVectorOfStations(toPush);

			XMLElement* station = train->FirstChildElement("Station");


			// read all transitional stations
			while (station != nullptr)
			{
				toPush = readStation(station);
				aTrain.pushStationToVectorOfStations(toPush);
				station = station->NextSiblingElement("Station");
			}


			// read arrival station
			XMLElement* arrival = train->FirstChildElement("Arrival");
			stationName = arrival->Attribute("name");
			arrivalTime = arrival->Attribute("arriveTime");

			toPush.setName(stationName);
			toPush.setTimeOfArrival(arrivalTime);

			aTrain.pushStationToVectorOfStations(toPush);

			XMLElement* route = train->FirstChildElement("Route");

			// read routes 

			while (route != nullptr)
			{
				Route toPush = readRoute(route);
				aTrain.pushRouteToVectorOfRoutes(toPush);
				route = route->NextSiblingElement("Route");
			}

			toReturn.push_back(aTrain);

			// go to next train
			train = train->NextSiblingElement("Train");
		}
	}

	tr.setTrains(toReturn);

	return toReturn;
}

void saveTrainsByDate(vector<Train>& vec, const string& date)
{
	XMLDocument doc;

	XMLNode* root = doc.NewElement("Data");

	for (size_t i = 0; i < vec.size(); ++i)
	{
		XMLElement* train = doc.NewElement("Train");

		train->SetAttribute("number", vec[i].getNumber());

		vector<RailCar> railCars = vec[i].getVectorOfRailCars();

		for (size_t j = 0; j < railCars.size(); ++j)
		{
			XMLElement* railCar = doc.NewElement("RailCar");
			railCar->SetAttribute("number", railCars[j].getNumber());

			
			if (railCars[j].getType() == TypeOfRailCar::FirstClass)
			{
				railCar->SetAttribute("type", "L");
			}
			else if (railCars[j].getType() == TypeOfRailCar::SecondClass)
			{
				railCar->SetAttribute("type", "K");
			}
			else
			{
				railCar->SetAttribute("type", "P");
			}

			train->InsertEndChild(railCar);
		}

		vector<Station> stations = vec[i].getVectorOfStations();

		XMLElement* departure = doc.NewElement("Departure");
		departure->SetAttribute("name", stations[0].getName().c_str());
		departure->SetAttribute("leaveTime", stations[0].getTimeOfDeparture().c_str());

		train->InsertEndChild(departure);

		for (size_t j = 1; j < stations.size() - 1; ++j)
		{
			XMLElement* station = doc.NewElement("Station");
			station->SetAttribute("name", stations[j].getName().c_str());
			station->SetAttribute("arriveTime", stations[j].getTimeOfArrival().c_str());
			station->SetAttribute("leaveTime", stations[j].getTimeOfDeparture().c_str());

			train->InsertEndChild(station);
		}

		XMLElement* arrival = doc.NewElement("Arrival");
		arrival->SetAttribute("name", stations[stations.size() - 1].getName().c_str());
		arrival->SetAttribute("arriveTime", stations[stations.size() - 1].getTimeOfArrival().c_str());

		train->InsertEndChild(arrival);

		vector<Route> routes = vec[i].getVectorOfRoutes();

		for (size_t j = 0; j < routes.size(); ++j)
		{
			XMLElement* route = doc.NewElement("Route");
			//

			route->SetAttribute("startPoint", routes[j].getDepartureStation().c_str());
			route->SetAttribute("endPoint", routes[j].getArrivalStation().c_str());

			vector<RailCar> bookingData = routes[j].getBookingData();

			for (int k = 0; k < bookingData.size(); ++k)
			{
				XMLElement* railCar = doc.NewElement("RailCar");

				railCar->SetAttribute("number", bookingData[k].getNumber());

				vector<unsigned> seats = bookingData[k].getVectotOfBookedSeats();

				for (int l = 0; l < seats.size(); ++l)
				{
					XMLElement* bookedSeat = doc.NewElement("BookedSeat");
					bookedSeat->SetText(seats[l]);

					railCar->InsertEndChild(bookedSeat);
				}

				route->InsertEndChild(railCar);
			}

			train->InsertEndChild(route);
		}

		root->InsertEndChild(train);
	}

	string fileName = "Database/" + date + ".xml";

	doc.InsertEndChild(root);

	doc.SaveFile(fileName.c_str());
}

vector<Train> getSuitableTrains(const vector<Train> &tr)
{
	vector<Train> vectorOfSuitableTrains;
	vector<Station> vectorOfStations;
	TripData tripData;
	tripData.setDeparturePoint("ivano-frankivsk");
	tripData.setArrivalPoint("kyiv");
	for (size_t i = 0; i < tr.size(); i++)
	{
		bool departureStationFound = false;
		bool arrivalStationFound = false;
		unsigned numberOfDepartureStation = 0;
		unsigned numberOfArrivalStation = 0;
		vectorOfStations = tr[i].getVectorOfStations();
		for (size_t j = 0; j < vectorOfStations.size(); j++)
		{
			if (tripData.getDeparturePoint() == vectorOfStations[j].getName())
			{
				departureStationFound = true;
				numberOfDepartureStation = j;
			}
			if (tripData.getArrivalPoint() == vectorOfStations[j].getName())
			{
				arrivalStationFound == true;
				numberOfArrivalStation = j;
			}
		}
		if (departureStationFound == true && arrivalStationFound == true)
		{
			if (numberOfDepartureStation < numberOfArrivalStation)
			{
				vectorOfSuitableTrains.push_back(tr[i]);
			}
		}
	}
	return vectorOfSuitableTrains;

	//We can find out what the price is by using the difference between numberOfDepartureStation and numberOfArrivalStatin
}