#pragma once
#include <vector>
using namespace std;
enum class TypeOfRailCar
{
	FirstClass,// люкс
	SecondClass, // купе
	ThirdClass // плацкарт
};

class RailCar
{
	unsigned number;
	unsigned numberOfSeats;
	TypeOfRailCar type;
	vector<unsigned> vectorOfBookedSeats; // push to this vector numberOfseat, that are ordered
public:
	RailCar();
	RailCar(unsigned, unsigned, TypeOfRailCar, vector<unsigned>);
	void setNumber(unsigned);
	void setNumberOfSeats(unsigned);
	void pushSeatToVectorOfBookedSeats(unsigned);
	void setType(TypeOfRailCar);
	unsigned getNumber() const;
	unsigned getNumberOfSeats() const;
	TypeOfRailCar getType() const;
	vector<unsigned> getVectotOfBookedSeats() const;
	void draw();
};

