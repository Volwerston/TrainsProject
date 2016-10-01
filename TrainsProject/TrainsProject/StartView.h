#pragma once
#include "View.h"
#include "Printer.h"

#define ENTER_KEY 13
#define SPACEBAR 32
#define BACK_SPACE 8
#define ESC 27
#define ARROW_KEY 224
#define UP 72
#define DOWN 80
#define ASCII_ZERO 48

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
	int correctDate(unsigned&);
	bool backSpace(unsigned&, unsigned&, string&);
	bool dateValidation(unsigned&, unsigned&);
	int UPorDOWNorENTER(unsigned&);
	string representDate();
	void drawItem(Items, Printer& );
	int writingWord(string&, unsigned, unsigned&);
	void drawItems();
	void draw();
	void drawName();
	int writingNumberOfTrain(unsigned&);
	void drawMessage();
	bool enterWasPressed();
	View* handle();
};

