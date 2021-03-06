#include <string>
#include <algorithm>
#include <sstream>
#include <conio.h>

#include "CreditCardView.h"
#include "Route.h"
#include "Console.h"
#include "Station.h"
#include "Algorithms.h"
#include "StartView.h"
#include "RailCarView.h"

template <typename T>
string toString(T& dat)
{
	ostringstream oStream;
	oStream << dat;

	return oStream.str();
}

bool CreditCardView::creditCardValid(const string& number)	// return true if valid card and false otherwise	
{
	int digit = number.size() - 1;
	unsigned mult = 0, sumOdd = 0, sumEven = 0;

	while (digit >= 0)
	{
		if (digit % 2 == 1)
			sumOdd += number[digit] - '0';
		else
		{
			mult = (number[digit] - '0') * 2;

			if (mult > 9)
				mult = mult % 10 + mult / 10;	// add digits in the number

			sumEven += mult;
		}

		--digit;
	}

	return !((sumOdd + sumEven) % 10);	// if mod 10 == zero card is valid
}


class FindByStationName
{
	string stationName;
public:
	FindByStationName(const string& s = " ")
		: stationName(s)
	{
	}

	bool operator()(const Station& s)
	{
		return (s.getName() == stationName);
	}
};

string CreditCardView::representDate()
{
	string toReturn = dateOfExpiration;
	if (toReturn.size() == 5 || toReturn.size() == 6)
	{
		toReturn = toReturn.insert(4, "-");
	}
	else if (toReturn.size() == 7 || toReturn.size() == 8)
	{
		toReturn = toReturn.insert(4, "-");
		toReturn = toReturn.insert(7, "-");
	}
	return toReturn;
}

CreditCardView::CreditCardView(TripData data) :
	tripData(data),
	indexOfSelectedOption(0),
	dateOfExpiration(""),
	CVV(""),
	cardNumber("")
{
	countPrice();
	vectorOfOptions.push_back(Item::CardNumber);
	vectorOfOptions.push_back(Item::DateOfExpire);
	vectorOfOptions.push_back(Item::CVV);
	vectorOfOptions.push_back(Item::Pay);
	vectorOfOptions.push_back(Item::GoBack);
	selectedOption = &vectorOfOptions[0];

	// get local time
	SYSTEMTIME time;
	GetLocalTime(&time);

	string currentYear;
	string currentMonth;
	string currentDay;

	currentYear = to_string(time.wYear);

	if (time.wMonth < 10)
	{
		currentMonth = "0" + to_string(time.wMonth);
	}
	else
	{
		currentMonth = to_string(time.wMonth);
	}

	if (time.wDay < 10)
	{
		currentDay = "0" + to_string(time.wDay);
	}
	else
	{
		currentDay = to_string(time.wDay);
	}

	currentDate = currentYear + currentMonth + currentDay;
}

void CreditCardView::countPrice() // find the price of purchase
{
	int koef = 0;

	vector<RailCar> railCars = tripData.getTrain().getVectorOfRailCars();

	TypeOfRailCar carType = railCars[tripData.getNumberOfRailCar() - 1].getType();

	if (carType == TypeOfRailCar::FirstClass)
	{
		koef = 40;
	}
	else if (carType == TypeOfRailCar::SecondClass)
	{
		koef = 30;
	}
	else
	{
		koef = 20;
	}

	vector<Station> stations = tripData.getTrain().getVectorOfStations();

	auto it1 = std::find_if(stations.begin(), stations.end(), FindByStationName(tripData.getDeparturePoint()));
	auto it2 = std::find_if(stations.begin(), stations.end(), FindByStationName(tripData.getArrivalPoint()));

	int numOfStations = std::distance(it1, it2 + 1);

	price =  koef*numOfStations*(tripData.getVectorOfSeats().size());
}

void CreditCardView::drawPrice()
{
	cursor.Y = 8;
	printAtCenter("Price: " + to_string(price), headline);
}

void CreditCardView::drawOption(Item option, Printer& printer)
{
	cursor.X = 10;
	cursor.Y = 10;
	unsigned sizeBetweenLines = 2;
	if (option == Item::CardNumber)
	{
		setCursorAt(cursor.X, cursor.Y);
		printer.print("Number of credit card: " + cardNumber);
	}
	else if (option == Item::DateOfExpire)
	{
		cursor.Y += sizeBetweenLines;
		setCursorAt(cursor.X, cursor.Y);
		printer.print("                YYYY/MM");
		cursor.X = 10;
		setCursorAt(cursor.X, ++cursor.Y);
		printer.print("Date of expire: " + representDate());
	}
	else if (option == Item::CVV)
	{
		cursor.Y += 1 + 2 * sizeBetweenLines;
		setCursorAt(cursor.X, cursor.Y);
		printer.print("CVV: " + CVV);
	}
	else if (option == Item::Pay)
	{
		cursor.Y += 1 + 5 * sizeBetweenLines;
		setCursorAt(cursor.X, cursor.Y);
		printAtCenter("Pay", printer);
	}
	else
	{
		cursor.Y += 1 + 7 * sizeBetweenLines;
		printAtCenter("Go back", printer);
	}
}

void CreditCardView::drawVectorOfOptions()
{
	for (size_t i = 0; i < vectorOfOptions.size(); ++i)
	{
		if (selectedOption == &vectorOfOptions[i])
		{
			drawOption(vectorOfOptions[i], printerForSelectedItem);
		}
		else
		{
			drawOption(vectorOfOptions[i], mainPrinter);
		}
	}
}

void CreditCardView::draw()
{
	countPrice();
	clean();
	drawPrice();
	drawVectorOfOptions();
}

bool CreditCardView::enterWasPressed() // checks whether all fields have proper data before submitting
{
	bool toReturn = false;
	if (creditCardValid(cardNumber) && dateOfExpiration.size() == 8 && CVV.size() == 3)
	{
		toReturn = true;
	}

	return toReturn;
}

void CreditCardView::payForTickets()
{
	vector<Route> routes = tripData.getTrain().getVectorOfRoutes();

	// makes new route
	Route toAdd;
	toAdd.setDepartureStation(tripData.getDeparturePoint());
	toAdd.setArrivalStation(tripData.getArrivalPoint());

	bool routeFound = false;
	vector<unsigned> seats = tripData.getVectorOfSeats();

	vector<RailCar> railCars;

	for (int i = 0; i < routes.size(); ++i)
	{
		// there is such route in the list of routes
		if (routes[i].getArrivalStation() == toAdd.getArrivalStation()
			&& routes[i].getDepartureStation() == toAdd.getDepartureStation())
		{
			routeFound = true;

			railCars = routes[i].getBookingData();

			bool railCarFound = false;

			for (int j = 0; j < railCars.size(); ++j)
			{
				// some tickets in this car for this route have already been booked
				if (railCars[j].getNumber() == tripData.getNumberOfRailCar())
				{
					railCarFound = true;

					// just add new seats to the vector of booked seats
					for (int k = 0; k < seats.size(); ++k)
					{
						railCars[j].pushSeatToVectorOfBookedSeats(seats[k] + 1);
					}

					break;
				}
			}

			// if no tickets have been booked for this railcar in the existing route
			if (!railCarFound)
			{
				// make new railcar, fill booked seats and add this railcar to the existing route
				RailCar newRailCar;
				newRailCar.setNumber(tripData.getNumberOfRailCar());
				for (int j = 0; j < seats.size(); ++j)
				{
					newRailCar.pushSeatToVectorOfBookedSeats(seats[j] + 1);
				}
				railCars.push_back(newRailCar);
			}

			routes[i].setBookingData(railCars);
			break;
		}
	}

	// if route doesn't exist
	if (!routeFound)
	{
		vector<RailCar> cars;

		RailCar aRailCar;
		aRailCar.setNumber(tripData.getNumberOfRailCar());
		for (int i = 0; i < seats.size(); ++i)
		{
			aRailCar.pushSeatToVectorOfBookedSeats(seats[i] + 1);
		}

		cars.push_back(aRailCar);

		// push already created "toAdd" route to the vector of routes
		toAdd.setBookingData(cars);
		routes.push_back(toAdd);
	}

	Train aTrain = tripData.getTrain();

	// creates a modified train to replace the existing one
	Train modifyTrain(aTrain.getName(), aTrain.getNumber(), aTrain.getVectorOfRailCars(), aTrain.getVectorOfStations(), routes);

	vector<Train> trainsToSave = tripData.getTrains();


	// delete existing train and replace with the new one
	auto it = trainsToSave.begin();

	while (it != trainsToSave.end())
	{
		if ((*it).getNumber() == aTrain.getNumber())
		{
			it = trainsToSave.erase(it);
			break;
		}
		else
		{
			++it;
		}
	}

	trainsToSave.push_back(modifyTrain);


	// save trains to file
	saveTrainsByDate(trainsToSave, tripData.getDate());
}

View* CreditCardView::handle()
{
	View* toReturn = nullptr;

	bool finish = false;

	unsigned key = _getch();
	while (key && !finish)
	{
		if (key == ARROW_KEY)
		{
			key = _getch();
		}
		switch (key)
		{
		case(UP) :
		{
			if (selectedOption == &vectorOfOptions[0]) // go to the last option
			{
				selectedOption = &vectorOfOptions[vectorOfOptions.size() - 1];
				indexOfSelectedOption = vectorOfOptions.size() - 1;
				draw();
			}
			else
			{
				selectedOption = &vectorOfOptions[indexOfSelectedOption - 1];
				indexOfSelectedOption -= 1;
				draw();
			}
			key = _getch();
		}
				 break;
		case(DOWN) :
		{
			if (selectedOption == &vectorOfOptions[vectorOfOptions.size() - 1]) // go to the first option
			{
				selectedOption = &vectorOfOptions[0];
				indexOfSelectedOption = 0;
				draw();
			}
			else 
			{
				selectedOption = &vectorOfOptions[indexOfSelectedOption + 1];
				indexOfSelectedOption += 1;
				draw();
			}
			key = _getch();
		}
				   break;
		case ESC:
			toReturn = new RailCarView(tripData); // go to the previous view
			finish = true;
			break;
		case(ENTER_KEY) :
		{
			if (enterWasPressed()) // can be paid
			{
				if (selectedOption == &vectorOfOptions[vectorOfOptions.size() - 2]) // "Pay"
				{
					// commit payment operation and go to start
					payForTickets();

					toReturn = new StartView(TripData());
					finish = true;
				}
			}


			if (selectedOption == &vectorOfOptions[vectorOfOptions.size() - 1]) // "Go back"
				{
					toReturn = new RailCarView(tripData);
					finish = true;
				}
			else
				{
					if (!enterWasPressed()) // if "Pay" but not all fields have proper data
					{
						key = _getch();
					}
				}
		}
			break;
		}
		if (selectedOption == &vectorOfOptions[0])
		{
			key = writingNumber(cardNumber, 16, key, this); // write card number
		}
		else if (selectedOption == &vectorOfOptions[1])
		{
			key = correctDate(key, dateOfExpiration, currentDate,  this); // write day of expire
		}
		else if (selectedOption == &vectorOfOptions[2])
		{
			key = writingNumber(CVV, 3, key, this); // write CVV
		}
	}

	return toReturn;
}
