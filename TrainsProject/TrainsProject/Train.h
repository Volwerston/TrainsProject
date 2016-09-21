#pragma once
#include "RailCar.h"
#include "Station.h"

class Train
{
	string name;
	unsigned number;
	vector<RailCar> vectorOfRailCars;
	vector<Station> vectorOfStations;

public:
	Train();
	Train(string, unsigned, vector<RailCar>, vector<Station>);

	void setName(string);
	void setNumber(unsigned);
	void pushRailCarToVectorOfRailCars(RailCar);
	void pushStationToVectorOfStations(Station);

	string getName() const;
	unsigned getNumber() const;
	vector<RailCar> getVectorOfRailCars() const;
	vector<Station> getVectorOfStations() const;
};

