#include "Train.h"

Train::Train() :
	name(""),
	number(0),
	vectorOfRailCars(0),
	vectorOfStations(0),
	vectorOfRoutes(0)
{
}

Train::Train(string _name, unsigned _number, vector<RailCar> _vectorOfRailCars, vector<Station> _vectorOfStations, vector<Route> _vectorOfRoutes):
	name(_name), 
	number(_number), 
	vectorOfRailCars(_vectorOfRailCars),
	vectorOfStations(_vectorOfStations),
	vectorOfRoutes(_vectorOfRoutes)
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

void Train::pushRouteToVectorOfRoutes(Route _r)
{
	vectorOfRoutes.push_back(_r);
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

vector<Route> Train::getVectorOfRoutes() const
{
	return vectorOfRoutes;
}