#pragma once
#include <string>
#include <vector>

#include "Train.h"

using namespace std;

class TripData
{
	string date;
	string departurePoint;
	string arrivalPoint;
	unsigned numberOfTrain;
	unsigned numberOfRailCar;
	vector<unsigned> vectorOfSeats;
	vector<Train> trainsToSave;
	Train chosenTrain;

public:
	TripData();
	TripData(string, string, string, unsigned, unsigned, vector<unsigned>, Train);

	string getDate() const;
	string getDeparturePoint() const;
	string getArrivalPoint() const;
	unsigned getNumberOfTrain() const;
	unsigned getNumberOfRailCar() const;
	vector<unsigned> getVectorOfSeats() const;
	Train getTrain() const;
	vector<Train> getTrains() const;

	void setDate(string);
	void setDataOfBookedSeats(vector<RailCar>&);
	void setDataOfChosenSeats(vector<unsigned>&);
	void setDeparturePoint(string);
	void setArrivalPoint(string);
	void setTrain(Train);
	void setNumberOfTrain(unsigned);
	void setNumberOfRailcar(unsigned);
	void pushToVectorOfSeats(unsigned);
	void setTrains(vector<Train>&);
};