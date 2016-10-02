#include <string>
#include <algorithm>
#include <sstream>

#include "CreditCardView.h"
#include "Route.h"
#include "Console.h"
#include "Station.h"
#include "Algorithms.h"
#include "StartView.h"

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

CreditCardView::CreditCardView( TripData data ) 
	: tripData(data)
{
}

void CreditCardView::draw()
{
	clean();

	string toPrint = "Total sum: ";

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

	unsigned price = koef*numOfStations*(tripData.getVectorOfSeats().size());
	toPrint += "   " + toString(price);

	setCursorAt(0, 1);
	printAtCenter(toPrint, stats);
}

View* CreditCardView::handle()
{
	View* nextView = nullptr;

	setCursorAt(5, 5);
	cout << "Enter card number: ";
	string cardNum = "";
	cin >> cardNum; //valid example: "4149500017188320"

	while (!creditCardValid(cardNum))
	{
		clean();
		draw();

		setCursorAt(5, 5);
		cout << "Enter card number: ";
		cin >> cardNum;
	}

	string cvv, expireDate;

	setCursorAt(5, 7);
	cout << "Enter date of expire: ";
	cin >> expireDate; // use your function for date validation

	setCursorAt(5, 9);
	cout << "Enter CVV: ";
	cin >> cvv; // just some string

	vector<Route> routes = tripData.getTrain().getVectorOfRoutes();
	
	Route toAdd;
	toAdd.setDepartureStation(tripData.getDeparturePoint());
	toAdd.setArrivalStation(tripData.getArrivalPoint());

	bool routeFound = false;
	vector<unsigned> seats = tripData.getVectorOfSeats();

	vector<RailCar> railCars; 

	for (int i = 0; i < routes.size(); ++i)
	{
		if (routes[i].getArrivalStation() == toAdd.getArrivalStation()
			&& routes[i].getDepartureStation() == routes[i].getDepartureStation())
		{
			routeFound = true;

			railCars = routes[i].getBookingData();

			bool railCarFound = false;

			for (int j = 0; j < railCars.size(); ++j)
			{
				if (railCars[j].getNumber() == tripData.getNumberOfRailCar())
				{
					railCarFound = true;
					for (int k = 0; k < seats.size(); ++k)
					{
						railCars[j].pushSeatToVectorOfBookedSeats(seats[k]);
					}

					break;
				}
			}

			if (!railCarFound)
			{
				RailCar newRailCar;
				newRailCar.setNumber(tripData.getNumberOfRailCar()+1);
				for (int j = 0; j < seats.size(); ++j)
				{
					newRailCar.pushSeatToVectorOfBookedSeats(seats[j]+1);
				}
				railCars.push_back(newRailCar);
			}

			routes[i].setBookingData(railCars);
			break;
		}
	}

	if (!routeFound)
	{
		vector<RailCar> cars;

		RailCar aRailCar;
		aRailCar.setNumber(tripData.getNumberOfRailCar() + 1);
		for (int i = 0; i < seats.size(); ++i)
		{
			aRailCar.pushSeatToVectorOfBookedSeats(seats[i]+1);
		}

		cars.push_back(aRailCar);

		toAdd.setBookingData(cars);
		routes.push_back(toAdd);
	}
	
	Train aTrain = tripData.getTrain();

	Train modifyTrain(aTrain.getName(), aTrain.getNumber(), aTrain.getVectorOfRailCars(), aTrain.getVectorOfStations(), routes);

	vector<Train> trainsToSave = tripData.getTrains();

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
	
	saveTrainsByDate(trainsToSave, tripData.getDate());

	return new StartView(TripData());
}
