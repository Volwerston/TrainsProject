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
	seatsNumber->QueryIntText(&numOfSeats);

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
		XMLNode* root = trainsData.FirstChild();

		XMLElement* train = root->FirstChildElement("Train");

		while (train != nullptr)
		{
			Train currTrain;

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

void saveTrainsByDate(vector<Train>& vec, const string& date)
{
	XMLDocument doc;

	XMLNode* root = doc.NewElement("Data");

	for (size_t i = 0; i < vec.size(); ++i)
	{
		XMLElement* train = doc.NewElement("Train");

		vector<RailCar> railCars = vec[i].getVectorOfRailCars();

		for (size_t j = 0; j < railCars.size(); ++j)
		{
			XMLElement* railCar = doc.NewElement("RailCar");
			XMLElement* number = doc.NewElement("Number");
			number->SetText(railCars[j].getNumber());
			XMLElement* type = doc.NewElement("Type");
			
			
			if (railCars[j].getType() == TypeOfRailCar::FirstClass)
			{
				type->SetText("L");
			}
			else if (railCars[j].getType() == TypeOfRailCar::SecondClass)
			{
				type->SetText("K");
			}
			else
			{
				type->SetText("P");
			}

			XMLElement* seats = doc.NewElement("Seats");
			seats->SetText(railCars[j].getNumberOfSeats());

			railCar->InsertEndChild(number);
			railCar->InsertEndChild(type);
			railCar->InsertEndChild(seats);
			train->InsertEndChild(railCar);
		}

		XMLElement* departure = doc.NewElement("Departure");
		XMLElement* name = doc.NewElement("Name");
		name->SetText(vec[i].getVectorOfStations()[0].getName().c_str());
		XMLElement* time = doc.NewElement("Time");

		string departureTime = vec[i].getVectorOfStations()[0].getTimeOfDeparture().substr(11);

		time->SetText(departureTime.c_str());
		
		departure->InsertEndChild(name);
		departure->InsertEndChild(time);

		train->InsertEndChild(departure);

		vector<Station> stations = vec[i].getVectorOfStations();

		for (size_t j = 1; j < stations.size() - 1; ++j)
		{
			XMLElement* transition = doc.NewElement("Transition");
			XMLElement* name = doc.NewElement("Name");
			name->SetText(stations[j].getName().c_str());

			XMLElement* arrive = doc.NewElement("Arrive");

			XMLElement* arrivalTime = doc.NewElement("Time");
			XMLElement* arrivalDate = doc.NewElement("Date");
			
			string arriveTime = stations[j].getTimeOfArrival().substr(11);
			string arriveDate = stations[j].getTimeOfArrival().substr(0, 10);

			arrivalTime->SetText(arriveTime.c_str());
			arrivalDate->SetText(arriveDate.c_str());

			arrive->InsertEndChild(arrivalTime);
			arrive->InsertEndChild(arrivalDate);

			XMLElement* leave = doc.NewElement("Leave");

			string departTime = stations[j].getTimeOfDeparture().substr(11);
			string departDate = stations[j].getTimeOfArrival().substr(0, 10);

			XMLElement* departureTime = doc.NewElement("Time");
			XMLElement* departureDate = doc.NewElement("Date");

			departureTime->SetText(departTime.c_str());
			departureDate->SetText(departDate.c_str());

			leave->InsertEndChild(departureTime);
			leave->InsertEndChild(departureDate);

			transition->InsertEndChild(name);
			transition->InsertEndChild(arrive);
			transition->InsertEndChild(leave);

			train->InsertEndChild(transition);
		}

		XMLElement* arrival = doc.NewElement("Arrival");
		XMLElement* arrivalName = doc.NewElement("Name");
		arrivalName->SetText(stations[stations.size() - 1].getName().c_str());

		string arrivalTime = stations[stations.size() - 1].getTimeOfArrival().substr(11);
		string arrivalDate = stations[stations.size() - 1].getTimeOfArrival().substr(0, 10);

		XMLElement* arriveTime = doc.NewElement("Time");
		XMLElement* arriveDate = doc.NewElement("Date");

		arriveTime->SetText(arrivalTime.c_str());
		arriveDate->SetText(arrivalDate.c_str());

		arrival->InsertEndChild(arrivalName);
		arrival->InsertEndChild(arriveTime);
		arrival->InsertEndChild(arriveDate);

		train->InsertEndChild(arrival);

		vector<Route> routes = vec[i].getVectorOfRoutes();

		for (size_t j = 0; j < routes.size(); ++j)
		{
			XMLElement* route = doc.NewElement("Route");
			XMLElement* routeFrom = doc.NewElement("From");
			XMLElement* routeTo = doc.NewElement("To");

			routeFrom->SetText(routes[j].getDepartureStation().c_str());
			routeTo->SetText(routes[j].getArrivalStation().c_str());

			route->InsertEndChild(routeFrom);
			route->InsertEndChild(routeTo);

			vector<RailCar> bookingData = routes[j].getBookingData();

			for (size_t k = 0; k < bookingData.size(); ++k)
			{
				XMLElement* railCarSnippet = doc.NewElement("RailCar");

				XMLElement* numberSnippet = doc.NewElement("Number");
				numberSnippet->SetText(bookingData[k].getNumber());
				railCarSnippet->InsertEndChild(numberSnippet);

				vector<unsigned int> seats = bookingData[k].getVectotOfBookedSeats();

				for (size_t l = 0; l < seats.size(); ++l)
				{
					XMLElement* seatSnippet = doc.NewElement("Seat");
					seatSnippet->SetText(seats[l]);
					railCarSnippet->InsertEndChild(seatSnippet);
				}

				route->InsertEndChild(railCarSnippet);
			}

			train->InsertEndChild(route);
		}

		root->InsertEndChild(train);
	}

	string fileName = "Database/" + date + ".xml";

	doc.InsertEndChild(root);

	doc.SaveFile(fileName.c_str());
}