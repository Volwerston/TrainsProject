#include "Train.h"



Train::Train() :
	name(""),
	number(0),
	vectorOfRailCars(0),
	vectorOfStations(0)
{
}

Train::Train(string _name, unsigned _number, vector<RailCar> _vectorOfRailCars, vector<Station> _vectorOfStations):
	name(_name), 
	number(_number), 
	vectorOfRailCars(_vectorOfRailCars),
	vectorOfStations(_vectorOfStations)
{
}

void Train::setName(string _name)
{
	name = _name;
}

void Train::setNumber(unsigned _number)
{
	number = _number;
}

void Train::pushRailCarToVectorOfRailCars(RailCar _railCar)
{
	vectorOfRailCars.push_back(_railCar);
}

void Train::pushStationToVectorOfStations(Station _station)
{
	vectorOfStations.push_back(_station);
}

string Train::getName() const
{
	return name;
}

unsigned Train::getNumber() const
{
	return number;
}

vector<RailCar> Train::getVectorOfRailCars() const
{
	return vectorOfRailCars;
}

vector<Station> Train::getVectorOfStations() const
{
	return vectorOfStations;
}
