#include <wchar.h>
#include <string>
#include <iostream>
#include <conio.h>

#include "StartView.h"
#include "Console.h"
#include "TrainsView.h"

StartView::StartView(TripData _tripData):
	mainPrinter(Color::WHITE, Color::CYAN),
	printerForSelectedItem(Color::RED,Color::CYAN),
	tripData(_tripData),
	indexOfSelectedItem(0),
	date("")
{
	vectorOfItems.push_back(Items::Date);
	vectorOfItems.push_back(Items::DeparturePoint);
	vectorOfItems.push_back(Items::ArrivalPoint);
	vectorOfItems.push_back(Items::NumberOfTrain);
	vectorOfItems.push_back(Items::Submit);
	vectorOfItems.push_back(Items::Exit);

	selectedItem = &vectorOfItems[0];
	SYSTEMTIME time;
	GetLocalTime(&time);

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

string StartView::itemToString(Items item)
{
	string toReturn = "";
	switch (item)
	{
	case(Items::Date):
	{
		toReturn = "Date: ";
	}
	break;
	case(Items::ArrivalPoint):
	{
		toReturn = "Arrival station: ";
	}
	break;
	case(Items::DeparturePoint):
	{
		toReturn = "Departure station: ";
	}
	break;
	case(Items::NumberOfTrain):
	{
		toReturn = "Number of train: ";
	}
	break;
	case(Items::Submit):
	{
		toReturn = "Submit";
	}
	break;
	case(Items::Exit):
	{
		toReturn = "Exit";
	}
    break;
	}
	return toReturn;
}

string StartView::representDate()
{
	string toReturn = date;
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

int  StartView::writingNumberOfTrain(unsigned& key)
{
	if (UPorDOWNorENTER(key))
	{
		return UPorDOWNorENTER(key);
	}
	unsigned start = trainNumber.size();
	backSpace(start, key, trainNumber, this);
	for (unsigned i = start; i < 3; ++i)
	{
		if ((char)key >= '1' && (char)key <= '9')
		{
			trainNumber.push_back(key);
			draw();
		}
		key = _getch();
		backSpace(i, key, trainNumber, this);
		if (UPorDOWNorENTER(key))
		{
			return UPorDOWNorENTER(key);
		}
	}
	while (key)
	{
		unsigned i = 3 - 1;
		if (backSpace(i, key, trainNumber, this))
		{
			backSpace(i, key, trainNumber, this);
			writingWord(trainNumber, 3, key, this);
		}
		key = _getch();
		backSpace(i, key, trainNumber, this);
		if (UPorDOWNorENTER(key))
		{
			return UPorDOWNorENTER(key);
		}
	}

}

void StartView::drawItem(Items item, Printer& printer)
{
	cursor.X = 10;
	cursor.Y = 10;
	unsigned sizeBetweenLines = 2;
	switch (item) 
	{
	case(Items::Date):
	{
		setCursorAt(cursor.X, cursor.Y);
		printer.print("      YYYY-MM-DD");
		cursor.X = 10;
		setCursorAt(cursor.X, ++cursor.Y);
		printer.print(itemToString(item) + representDate());
	}
	break;
	case(Items::DeparturePoint):
	{
		cursor.Y += 1 + sizeBetweenLines;
		setCursorAt(cursor.X, cursor.Y);
		printer.print(itemToString(item) + departure);
	}
	break;
	case(Items::ArrivalPoint):
	{
		cursor.Y += 1 + 2 * sizeBetweenLines;
		setCursorAt(cursor.X, cursor.Y);
		printer.print(itemToString(item) + arrival);
	}
	break;
	case(Items::NumberOfTrain):
	{
		cursor.Y += 1 + 3 * sizeBetweenLines;
		setCursorAt(cursor.X, cursor.Y);
		printer.print(itemToString(item) + trainNumber);
	}
	break;
	case(Items::Submit) :
	{
		cursor.Y += 1 + 5 * sizeBetweenLines;
		setCursorAt(cursor.X, cursor.Y);
		printAtCenter(itemToString(item), printer);
	}
	break;
	case(Items::Exit):
	{
		cursor.Y += 1 + 7 * sizeBetweenLines;
		setCursorAt(cursor.X, cursor.Y);
		printAtCenter(itemToString(item), printer);
	}
	break;
	}
}

void StartView::drawItems()
{
	
	for (size_t i = 0; i < vectorOfItems.size(); ++i)
	{
		if (selectedItem == &vectorOfItems[i])
		{
			drawItem(vectorOfItems[i], printerForSelectedItem);
		}
		else
		{
			drawItem(vectorOfItems[i], mainPrinter);
		}
	}
}

void StartView::draw()
{
	clean();
	drawName();
	drawItems();
	drawMessage();
}

void StartView::drawName()
{
	setCursorAt(8, 8);
	printAtCenter("Please fill in these fields using arrow keys to move", mainPrinter);
}

void StartView::drawMessage()
{
	if (date.size() == currentDate.size() && arrival.size() >= 3 && departure.size() >= 3)
	{
		setCursorAt(8, 30);
		printAtCenter("Now you can press ENTER to continue", mainPrinter);
	}
}

bool StartView::enterWasPressed()
{
	if (date.size() == 8 && arrival.size() >= 3 && departure.size() >= 3)
	{
		date.insert(6, "-").insert(4, "-");
		tripData.setDate(date);
		tripData.setDeparturePoint(departure);
		tripData.setArrivalPoint(arrival);
		return true;
	}
	return false;
}

View* StartView::handle()
{
	unsigned key = _getch();
	while (key)
	{
		if (key == ARROW_KEY)
		{
			key = _getch();
		}
		switch (key)
		{
		case(UP):
		{
			if (selectedItem == &vectorOfItems[0])
			{
				selectedItem = &vectorOfItems[vectorOfItems.size() - 1];
				indexOfSelectedItem = vectorOfItems.size() - 1;
				draw();
			}
			else
			{
				selectedItem = &vectorOfItems[indexOfSelectedItem - 1];
				indexOfSelectedItem -= 1;
				draw();
			}
			key = _getch();
		}
		break;
		case(DOWN):
		{
			if (selectedItem == &vectorOfItems[vectorOfItems.size() - 1])
			{
				selectedItem = &vectorOfItems[0];
				indexOfSelectedItem = 0;
				draw();
			}
			else
			{
				selectedItem = &vectorOfItems[indexOfSelectedItem + 1];
				indexOfSelectedItem += 1;
				draw();
			}
			key = _getch();
		}
		break;
		case(ENTER_KEY):
		{
			if (enterWasPressed())
			{
				if (selectedItem == &vectorOfItems[vectorOfItems.size() - 2])
				{
					return new TrainsView(tripData);
				}
			}

			if (selectedItem == &vectorOfItems[vectorOfItems.size() - 1])
			{
				return nullptr;
			}
			else
			{
				key = _getch();
			}
		}
		break;
		}
		if (selectedItem == &vectorOfItems[0])
		{
			key = correctDate(key, date, currentDate, this);
		}
		else if (selectedItem == &vectorOfItems[1])
		{
			key = writingWord(departure, 20,key, this);
		}
		else if (selectedItem == &vectorOfItems[2])
		{
			key = writingWord(arrival, 20,key, this);
		}
		else 
		{
			key = writingNumberOfTrain(key);
		}
	}
	return nullptr;
}