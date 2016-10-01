#ifndef CREDIT_CARD_VIEW
#define CREDIT_CARD_VIEW

#include "Printer.h"
#include "View.h"
#include "TripData.h"
#include "Console.h"
#include "Train.h"
#include "RailCar.h"
#include "TripData.h"

class CreditCardView : public View
{
private:
	TripData tripData;
public:
	CreditCardView( TripData );
	void draw();
	static float price;
	static CreditCard;
	View* handle();
};


#endif
