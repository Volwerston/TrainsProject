#include "RailCarView.h"

RailCarView::RailCarView(TripData tripData) :
	date(tripData.getDate()),
	departurePoint(tripData.getDeparturePoint()),
	arrivalPoint(tripData.getArrivalPoint()),
	numberOfTrain(tripData.getNumberOfTrain()),
	numberOfRailcar(tripData.getNumberOfRailCar()),
	vectorOfSeats(tripData.getVectorOfSeats())
{
}

void RailCarView::draw()
{}

View* RailCarView::handle(){}