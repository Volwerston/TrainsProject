#pragma once
#include "Train.h"
#include "TripData.h"

vector<Train> getTrainsByDate(const string&, TripData&);

vector<Train> getSuitableTrains(const vector<Train>&);

void saveTrainsByDate(vector<Train>&, const string&);