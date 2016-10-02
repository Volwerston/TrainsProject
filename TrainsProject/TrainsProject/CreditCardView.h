#ifndef CREDIT_CARD_VIEW
#define CREDIT_CARD_VIEW

#include <string>

#include "Printer.h"
#include "View.h"
#include "Console.h"
#include "Train.h"
#include "RailCar.h"
#include "TripData.h"

enum class Item
{
	CardNumber,
	DateOfExpire,
	CVV,
	GoBack,
	Pay
};

class CreditCardView : public View
{

private:
	TripData tripData;
	double price;
	vector<Item> vectorOfOptions; 
	Item* selectedOption;
	unsigned indexOfSelectedOption;
	Printer mainPrinter;
	Printer printerForSelectedItem;
	string dateOfExpiration;
	string currentDate;
	string cardNumber;
	string CVV;
public:
	CreditCardView( TripData );
	void countPrice();
	void drawPrice();
	bool enterWasPressed();
	string representDate();
	void drawOption(Item, Printer&);
	bool backSpace(unsigned&, unsigned&, string&);
	
	void drawVectorOfOptions();
	void draw();
	View* handle();
	bool creditCardValid(const string&);
};


#endif
