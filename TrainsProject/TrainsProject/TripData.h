#pragma once
#include <string>
#include <vector>

using namespace std;

class TripData
{
	string date;
	string departurePoint;
	string arrivalPoint;
	unsigned numberOfTrain;
	unsigned numberOfRailCar;
	vector<unsigned> vectorOfSeats;

public:
	TripData();
	TripData(string, string, string, unsigned, unsigned, vector<unsigned>);

	string getDate() const;
	string getDeparturePoint() const;
	string getArrivalPoint() const;
	unsigned getNumberOfTrain() const;
	unsigned getNumberOfRailCar() const;
	vector<unsigned> getVectorOfSeats() const;

	void setDate(string);
	void setDeparturePoint(string);
	void setArrivalPoint(string);
	void setNumberOfTrain(unsigned);
	void setNumberOfRailcar(unsigned);
	void pushToVectorOfSeats(unsigned);
};

