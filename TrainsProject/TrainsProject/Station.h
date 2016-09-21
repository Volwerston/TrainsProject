#pragma once
#include <string>

using namespace std;

class Station
{
	string name;
	string timeOfDeparture;
	string timeOfArrival;

public:
	Station();
	Station(string, string, string);

	void setName(string);
	void setTimeOfDeparture(string);
	void setTimeOfArrival(string);

	string getName() const;
	string getTimeOfArrival() const;
	string getTimeOfDeparture() const;
};

