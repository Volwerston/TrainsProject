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
	int writingNumberOfTrain(unsigned& key, unsigned& size, string& str)
	{
		/*if (UPorDOWNorENTER(key))
		{
		return UPorDOWNorENTER(key);
		}*/
		unsigned start = str.size();
		backSpace(start, key, str);
		for (unsigned i = start; i < 3; ++i)
		{
			if ((char)key >= '1' && (char)key <= '9')
			{
				str.push_back(key);
				draw();
			}
			key = _getch();
			backSpace(i, key, str);
			if (UPorDOWNorENTER(key))
			{
				return UPorDOWNorENTER(key);
			}
		}
		while (key)
		{
			unsigned i = 3 - 1;
			if (backSpace(i, key, str))
			{
				backSpace(i, key, str);
				writingNumberOfTrain(key, size, str);
			}
			key = _getch();
			backSpace(i, key, str);
			if (UPorDOWNorENTER(key))
			{
				return UPorDOWNorENTER(key);
			}
		}
	}

	//bool backSpace(unsigned&, unsigned&, string&);
	void drawVectorOfOptions();
	void draw();
	View* handle();
	bool creditCardValid(const string&);
};


#endif
