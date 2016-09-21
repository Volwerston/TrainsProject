#include "RailCar.h"



RailCar::RailCar():
	number(0),
	numberOfSeats(0),
	vectorOfBookedSeats(0)
{
}

RailCar::RailCar(unsigned _number, unsigned _numberOfSeats, TypeOfRailCar _type, vector<unsigned> _vectorOfBookedSeats):
	number(_number),
	numberOfSeats(_numberOfSeats),
	type(_type),
	vectorOfBookedSeats(_vectorOfBookedSeats)
{
}

void RailCar::setNumber(unsigned _number)
{
	number = _number;
}

void RailCar::setNumberOfSeats(unsigned _numberOfSeats)
{
	numberOfSeats = _numberOfSeats;
}

void RailCar::pushSeatToVectorOfBookedSeats(unsigned _bookedSeat)
{
	vectorOfBookedSeats.push_back(_bookedSeat);
}

void RailCar::setType(TypeOfRailCar _type)
{
	type = _type;
}

unsigned RailCar::getNumber() const
{
	return number;
}

unsigned RailCar::getNumberOfSeats() const
{
	return numberOfSeats;
}

TypeOfRailCar RailCar::getType() const
{
	return type;
}

vector<unsigned> RailCar::getVectotOfBookedSeats() const
{
	return vectorOfBookedSeats;
}

void RailCar::draw()
{
}
