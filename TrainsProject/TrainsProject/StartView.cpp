#include "StartView.h"
#include "Console.h"
#include <wchar.h>
#include <string>
#include <iostream>
#include <conio.h>

StartView::StartView(TripData _tripData):
	mainPrinter(Color::BLUE, Color::BLACK),
	printerForSelectedItem(Color::RED,Color::BLACK),
	tripData(_tripData),
	indexOfSelectedItem(0),
	date("")
{
	vectorOfItems.push_back(Items::Date);
	vectorOfItems.push_back(Items::DeparturePoint);
	vectorOfItems.push_back(Items::ArrivalPoint);
	vectorOfItems.push_back(Items::NumberOfTrain);

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
	}
	return toReturn;
}

bool StartView::dateValidation(unsigned& index, unsigned& key)
{
	if (index == 4 && key - ASCII_ZERO < 2)
	{
		return true;
	}
	else if (index == 5)
	{
		if (date[4] == '0')
		{
			if (key != ASCII_ZERO)
			{
				return true;
			}
			else
			{
				--index;
				return false;
			}
		}
		else if (key - ASCII_ZERO < 3)
		{
			return true;
		}
		else
		{
			--index;
			return false;
		}
	}
	else if (index == 6 && key-ASCII_ZERO < 4)
	{
		return true;
	}
	else if (index == 7)
	{
		if (date[6] == '3' && key - ASCII_ZERO < 2)
		{
			return true;
		}
		else if (date[6] == '0')
		{
			if (key != ASCII_ZERO)
			{
				return true;
			}
			else
			{
				--index;
				return false;
			}
		}
		else if(date[6] == '1' || date[6] == 2)
		{
			return true;
		}
		else
		{
			--index;
			return false;
		}
	}
	else if (index >= 0 && index < 4 && key- ASCII_ZERO < 10)
	{
		return true;
	}
	else
	{
		--index;
		return false;
	}
}

bool StartView::backSpace(unsigned& index, unsigned& key , string& str)
{
	bool toReturn = false;
	while (key == BACK_SPACE && index >= 0)
	{
		toReturn = true;
		if (index != 0)
		{
			--index;
		}
		if (str.size() != 0)
		{
			str.pop_back();
		}
		draw();
		key = _getch();
		
	}
	return toReturn;
}

int StartView::UPorDOWNorENTER(unsigned& key)
{
	if(key == UP)
	{
		return UP;
	}
	else if (key == DOWN)
	{
		return DOWN;
	}
	else if (key == ENTER_KEY)
	{
		return ENTER_KEY;
	}
	else
	{
		return false;
	}
}

int StartView::writingWord(string& word, unsigned size, unsigned& key)
{
	if (UPorDOWNorENTER(key))
	{
		return UPorDOWNorENTER(key);
	}
	unsigned start = word.size();
	backSpace(start,key,word);
	for (unsigned i = start; i < size; ++i)
	{
		if ((char)key >= 'a' && (char)key <= 'z' || (char)key == '-')
		{
			word.push_back(key);
			draw();
		}
		key = _getch(); 
		backSpace(i, key, word);
		if (UPorDOWNorENTER(key))
		{
			return UPorDOWNorENTER(key);
		}
	}
	while (key)
	{
		unsigned i = size - 1;
		if (backSpace(i, key, word))
		{
			backSpace(i, key, word);
			writingWord(word, size,key);
		}
		key = _getch();
		backSpace(i, key, word);
		if (UPorDOWNorENTER(key))
		{
			return UPorDOWNorENTER(key);
		}
	}

}
int  StartView::writingNumberOfTrain(unsigned& key)
{
	if (UPorDOWNorENTER(key))
	{
		return UPorDOWNorENTER(key);
	}
	unsigned start = trainNumber.size();
	backSpace(start, key, trainNumber);
	for (unsigned i = start; i < 3; ++i)
	{
		if ((char)key >= '1' && (char)key <= '9')
		{
			trainNumber.push_back(key);
			draw();
		}
		key = _getch();
		backSpace(i, key, trainNumber);
		if (UPorDOWNorENTER(key))
		{
			return UPorDOWNorENTER(key);
		}
	}
	while (key)
	{
		unsigned i = 3 - 1;
		if (backSpace(i, key, trainNumber))
		{
			backSpace(i, key, trainNumber);
			writingWord(trainNumber, 3, key);
		}
		key = _getch();
		backSpace(i, key, trainNumber);
		if (UPorDOWNorENTER(key))
		{
			return UPorDOWNorENTER(key);
		}
	}

}

int StartView::correctDate(unsigned& key)
{
	if (UPorDOWNorENTER(key))
	{
		return UPorDOWNorENTER(key);
	}
	unsigned start = date.size();
	backSpace(start, key, date);
	if (key - ASCII_ZERO < 10)
	{
		for (unsigned i = start; i < 8 - i; ++i)
		{
			if (key > currentDate[i])
			{
				if (dateValidation(i, key))
				{
					for (unsigned j = i; j < 8; ++j)
					{
						if (dateValidation(j, key))
						{
							date.push_back(key);
							draw();
						}
						key = _getch();
						if (UPorDOWNorENTER(key))
						{
							return UPorDOWNorENTER(key);
						}
						backSpace(j, key, date);
					}
					break;
				}
				key = _getch();
				if (UPorDOWNorENTER(key))
				{
					return UPorDOWNorENTER(key);
				}
				backSpace(i, key,date);
			}
			else if (key == currentDate[i])
			{
				if (dateValidation(i, key))
				{
					date.push_back(key);
					draw();
				}
					key = _getch();
					if (UPorDOWNorENTER(key))
					{
						return UPorDOWNorENTER(key);
					}
					backSpace(i, key, date);
			}
			else
			{
				--i;
				key = _getch();
				if (UPorDOWNorENTER(key))
				{
					return UPorDOWNorENTER(key);
				}
				backSpace(i, key, date);
			}
		}
	}

	while (key)
	{
		unsigned i = 7;
		if (backSpace(i, key, date))
		{
			backSpace(i, key, date);
			correctDate(key);
		}
		key = _getch();
		if (UPorDOWNorENTER(key))
		{
			return UPorDOWNorENTER(key);
		}
	}
}

string StartView::representDate()
{
	string toReturn = date;;
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
				clean();
				return this;
			}
			else
			{
				selectedItem = &vectorOfItems[indexOfSelectedItem - 1];
				indexOfSelectedItem -= 1;
				clean();
				return this;
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
				clean();
				return this;
			}
			else
			{
				selectedItem = &vectorOfItems[indexOfSelectedItem + 1];
				indexOfSelectedItem += 1;
				clean();
				return this;
			}
			key = _getch();
		}
		break;
		case(ENTER_KEY):
		{
			if (enterWasPressed())
			{
				//return SOMEVIEW(TripData);
			}
			else
			{
				key = _getch();
			}
		}
		break;
		}s
		if (selectedItem == &vectorOfItems[0])
		{
			key = correctDate(key);
		}
		else if (selectedItem == &vectorOfItems[1])
		{
			key = writingWord(departure, 20,key);
		}
		else if (selectedItem == &vectorOfItems[2])
		{
			key = writingWord(arrival, 20,key);
		}
		else 
		{
			key = writingNumberOfTrain(key);
		}
	}
	return nullptr;
}