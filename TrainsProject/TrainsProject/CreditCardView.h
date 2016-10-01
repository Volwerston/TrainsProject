#ifndef CREDIT_CARD_VIEW
#define CREDIT_CARD_VIEW

#include <string>

#include "Printer.h"
#include "View.h"
#include "Console.h"
#include "Train.h"
#include "RailCar.h"
#include "TripData.h"

class CreditCardView : public View
{
private:
	TripData tripData;
	double price;
public:
	CreditCardView( TripData );
	void draw();
	View* handle();
	bool creditCardValid(const string&);
};


#endif
