
#include "CreditCardView.h"
#include "CreditCard.h"

static float sPrice = 0;
static CreditCard sCard( 100 );

CreditCardView::CreditCardView( TripData data ) : tripData( data )
{
	const unsigned trainNum = tripData.getNumberOfTrain(); 	// get train
	const unsigned carNum = tripData.getNumberOfRailCar(); 	// get car
	const string deptDate = tripData.getDate(); 			// get departure date
    const string deptPoint = tripData.getDeparturePoint(); 	// get departure station
    const string arrvPoint = tripData.getDeparturePoint(); 	// get arrival station

	vector<Station>	stations = tripData.getTrain().getVectorOfStations();		// get all stations that user travels

	TypeOfRailCar type = tripData.getTrain().getVectroOfRailCars()[carNum].getType();

	if( 		type == TypeOfRailCar::FirstClass )
		price = 40;
	else if(	type == TypeOfRailCar::SecondClass )
		price = 30;
	else if(	type == TypeOfRailCar::ThirdClass )
		price = 20;
		
	price *= stations.size();	// calculate full price for the trip
}

void CreditCardView::draw()
{
	clean();

	/*
		...
	here go different Windows settigs parameters 
	that I do no know how to use
		...
	*/

	cout<< "Order information:" <<endl;
	cout<< tripData.getNumberOfTrain() <<endl; 	// get train
	cout<< tripData.getNumberOfRailCar() <<endl; 	// get car
	cout<< tripData.getDate() <<endl; 			// get departure date
    cout<< tripData.getDeparturePoint() <<endl; 	// get departure station
    cout<< tripData.getDeparturePoint() <<endl; 	// get arrival station
	cout<< sPrice <<endl;				// get price

	cout<< "Input credit card:" <<endl;		
	cout<< sCard.number() <<endl;
	cout<< sCard.expires() <<endl;
	cout<< sCard.code() <<endl;

}

View* CreaditCard::handle()
{
	clean();
	View* nextView = this;

	cout<< "Input card:" << endl;
	do
	{
		valid = sCard.inputNumber();
		valid = sCard.inputExpirationDate();
		valid = sCard.inputCvvCode();

		if( !valid )
			cout<< "Incorrect Input." <<endl;
	} while( !valid );

	return nextView;
}
