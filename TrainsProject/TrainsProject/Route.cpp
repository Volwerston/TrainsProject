#include "Route.h"

Route::Route(const string& _f, const string& _l)
	: departureStation(_f),
	arrivalStation(_l)
{
}

string Route::getDepartureStation() const
{
	return departureStation;
}

string Route::getArrivalStation() const
{
	return arrivalStation;
}

vector<RailCar> Route::getBookingData() const
{
	return bookingData;
}

void Route::setDepartureStation(const string _dep)
{
	departureStation = _dep;
}

void Route::setArrivalStation(const string& _arr)
{
	arrivalStation = _arr;
}

void Route::setBookingData(vector<RailCar>& vec)
{
	bookingData = vec;
}