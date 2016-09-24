#include "TripData.h"



TripData::TripData():
	date(""),
	departurePoint(""),
	arrivalPoint(""),
	numberOfTrain(0),
	numberOfRailCar(0),
	vectorOfSeats(0),
	chosenTrain(Train())
{
}

TripData::TripData(string _date, string _departurePoint, string _arrivalPoint, unsigned _numberOfTrain, unsigned _numberOfRailCar, vector<unsigned> _vectorOfSeats, Train _t) :
	date(_date),
	arrivalPoint(_arrivalPoint),
	departurePoint(_departurePoint),
	numberOfTrain(_numberOfTrain),
	numberOfRailCar(_numberOfRailCar),
	vectorOfSeats(_vectorOfSeats),
	chosenTrain(_t)
{
}

string TripData::getDate() const
{
	return date;
}

string TripData::getDeparturePoint() const
{
	return departurePoint;
}

string TripData::getArrivalPoint() const
{
	return arrivalPoint;
}

unsigned TripData::getNumberOfTrain() const
{
	return numberOfTrain;
}

unsigned TripData::getNumberOfRailCar() const
{
	return numberOfRailCar;
}

vector<unsigned> TripData::getVectorOfSeats() const
{
	return vectorOfSeats;
}

Train TripData::getTrain() const
{
	return chosenTrain;
}

void TripData::setDate(string _date)
{
	date = _date;
}

void TripData::setDeparturePoint(string _departure)
{
	departurePoint = _departure;
}

void TripData::setArrivalPoint(string _arrival)
{
	arrivalPoint = _arrival;
}

void TripData::setNumberOfTrain(unsigned _numberOfTrain)
{
	numberOfTrain = _numberOfTrain;
}

void TripData::setNumberOfRailcar(unsigned _numberOfRailCar)
{
	numberOfRailCar = _numberOfRailCar;
}

void TripData::setTrain(Train t)
{
	chosenTrain = t;
}

void TripData::pushToVectorOfSeats(unsigned seat)
{
	vectorOfSeats.push_back(seat);
}