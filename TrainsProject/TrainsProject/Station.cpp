#include "Station.h"



Station::Station():
	name(""),
	timeOfDeparture(""),
	timeOfArrival("")
{
}

Station::Station(string _name, string _timeOfDeparture, string _timeOfArrival):
	name(_name),
	timeOfDeparture(_timeOfDeparture),
	timeOfArrival(_timeOfArrival)
{
}

void Station::setName(string _name)
{
	name = _name;
}

void Station::setTimeOfDeparture(string _timeOfDeparture)
{
	timeOfDeparture = _timeOfDeparture;

}

void Station::setTimeOfArrival(string _timeOfArrival)
{
	timeOfArrival = _timeOfArrival;
}

string Station::getName() const
{
	return name;
}

string Station::getTimeOfArrival() const
{
	return timeOfArrival;
}

string Station::getTimeOfDeparture() const
{
	return timeOfDeparture;
}