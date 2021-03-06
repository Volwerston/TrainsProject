#pragma once
#include "RailCar.h"
#include "Station.h"
#include "Route.h"

class Train
{
	string name;
	unsigned number;
	vector<RailCar> vectorOfRailCars; 
	vector<Station> vectorOfStations;
	vector<Route> vectorOfRoutes;

public:
	Train();
	Train(string, unsigned, vector<RailCar>, vector<Station>, vector<Route>);

	void setName(string);
	void setNumber(unsigned);
	void pushRailCarToVectorOfRailCars(RailCar);
	void pushStationToVectorOfStations(Station);
	void pushRouteToVectorOfRoutes(Route);

	string getName() const;
	unsigned getNumber() const;
	vector<RailCar> getVectorOfRailCars() const;
	vector<Station> getVectorOfStations() const;
	vector<Route> getVectorOfRoutes() const;
};