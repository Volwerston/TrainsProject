#pragma once
#include "View.h"
#include "Printer.h"

enum class Items
{
	Date,
	ArrivalPoint,
	DeparturePoint,
	NumberOfTrain
};

class StartView : public View
{
	TripData tripData;

	vector<Items> vectorOfItems;
	Items *selectedItem;
	unsigned indexOfSelectedItem;
	Printer mainPrinter;
	Printer printerForSelectedItem;
	string date;
	string arrival;
	string departure;
	string trainNumber;
	string currentDate;
	string currentYear;
	string currentMonth;
	string currentDay;
public:
	StartView(TripData);

	string itemToString(Items);
	string representDate();
	void drawItem(Items, Printer& );
	void drawItems();
	void draw();
	void drawName();
	int writingNumberOfTrain(unsigned&);
	bool enterWasPressed();
	void drawMessage();
	View* handle();
};

