#include "Console.h"

#include <conio.h>

HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
HWND hwnd = GetConsoleWindow();
HDC hdc = GetDC(hwnd);
COORD cursor;
RECT rect;

const int consoleWidth = 123;
const int consoleHeight = 39;
const int fontWidth = 11;
const int fontHeight = 18;

Printer headline(Color::YELLOW, Color::BLUE);
Printer menuPassive(Color::YELLOW, Color::CYAN);
Printer menuActive(Color::YELLOW, Color::GREEN);
Printer techData(Color::BLACK, Color::WHITE);
Printer stats(Color::WHITE, Color::LIGHT_BLUE);
Printer printerForRailCarViewEnterButton(Color::WHITE, Color::CYAN);
Printer mainPrinter(Color::WHITE, Color::CYAN);
Printer printerForSelectedItem(Color::RED, Color::CYAN);

vector<Train> trains;

void scrollOff(int width, int height)
{
	string cols = to_string(width);
	string lines = to_string(height);
	string str = "mode con cols=" + cols + " lines=" + lines;
	const char* sch = str.c_str();
	system(sch);
}

void setConsoleProperties()
{
	scrollOff(consoleWidth, consoleHeight);

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// setting text font
	CONSOLE_FONT_INFOEX info = { 0 };
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = 18;
	info.FontWeight = FW_NORMAL;
	wcscpy_s(info.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(hconsole, NULL, &info);

	// making cursor invisible
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(hconsole, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hconsole, &cursorInfo);

	// making edges immutable
	HMENU hm = GetSystemMenu(GetConsoleWindow(), FALSE);
	RemoveMenu(hm, SC_SIZE, MF_BYCOMMAND | MF_REMOVE);
	RemoveMenu(hm, SC_MAXIMIZE, MF_BYCOMMAND | MF_REMOVE);
	DrawMenuBar(GetConsoleWindow());

	// configuring buffer and window

	setConsoleSize(consoleWidth, consoleHeight);

	COORD c;
	c.X = consoleWidth;
	c.Y = consoleHeight;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void setCursor(short x, short y)
{
	COORD c = { x , y };
	SetConsoleCursorPosition(hconsole, c);
}

void setCursorAt(int x, int y)
{
	cursor.X = x;
	cursor.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
}

void printAtCenter(string st, const Printer& p)
{
	int size = st.size();
	int x_pos = (consoleWidth - size) / 2 + (consoleWidth - size) % 2;
	setCursorAt(x_pos, cursor.Y);
	p.print(st);
}

void setConsoleSize(int width, int height)
{
	HANDLE consol;
	consol = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c;
	c.X = width;
	c.Y = height;
	SetConsoleScreenBufferSize(consol, c);
	SMALL_RECT r;
	r.Left = 0;
	r.Top = 0;
	r.Right = width - 1;
	r.Bottom = height - 1;
	SetConsoleWindowInfo(consol, TRUE, &r);
}

BOOL DrawLine(HDC hdc, int x1, int y1, int x2, int y2)
{ 
	POINT pt;
	MoveToEx(hdc, x1, y1, &pt);
	return LineTo(hdc, x2, y2);
}

int correctDate(unsigned& key, string& date,const string& currentDate, View* v)
{
	if (UPorDOWNorENTER(key))
	{
		return UPorDOWNorENTER(key);
	}
	unsigned start = date.size();
	backSpace(start, key, date, v);
	if (key - ASCII_ZERO < 10)
	{
		for (unsigned i = start; i < 8; ++i)
		{
			if (key > currentDate[i])
			{
				if (dateValidation(i, key, date))
				{
					for (unsigned j = i; j < 8; ++j)
					{
						if (dateValidation(j, key, date))
						{
							date.push_back(key);
							v->draw();
						}
						key = _getch();
						if (UPorDOWNorENTER(key))
						{
							return UPorDOWNorENTER(key);
						}
						backSpace(j, key, date, v);
					}
					break;
				}
				key = _getch();
				if (UPorDOWNorENTER(key))
				{
					return UPorDOWNorENTER(key);
				}
				backSpace(i, key, date, v);
			}
			else if (key == currentDate[i])
			{
				if (dateValidation(i, key, date))
				{
					date.push_back(key);
					v->draw();
				}
				key = _getch();
				if (UPorDOWNorENTER(key))
				{
					return UPorDOWNorENTER(key);
				}
				backSpace(i, key, date, v);
			}
			else
			{
				--i;
				key = _getch();
				if (UPorDOWNorENTER(key))
				{
					return UPorDOWNorENTER(key);
				}
				backSpace(i, key, date, v);
			}
		}
	}

	while (key)
	{
		unsigned i = 7;
		if (backSpace(i, key, date, v))
		{
			backSpace(i, key, date, v);
			correctDate(key, date, currentDate, v);
		}
		key = _getch();
		if (UPorDOWNorENTER(key))
		{
			return UPorDOWNorENTER(key);
		}
	}
}

bool dateValidation(unsigned& index, unsigned& key, string& date)
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
	else if (index == 6 && key - ASCII_ZERO < 4)
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
		else if (date[6] == '1' || date[6] == 2)
		{
			return true;
		}
		else
		{
			--index;
			return false;
		}
	}
	else if (index >= 0 && index < 4 && key - ASCII_ZERO < 10)
	{
		return true;
	}
	else
	{
		--index;
		return false;
	}
}

bool backSpace(unsigned& index, unsigned& key, string& str, View* v)
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
		v->draw();
		key = _getch();

	}
	return toReturn;
}

int UPorDOWNorENTER(unsigned& key)
{
	if (key == UP)
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

string getCurrentDate() 
{
	SYSTEMTIME time;
	GetLocalTime(&time);

	string currDay, currYear, currMonth;

	currYear = to_string(time.wYear);

	if (time.wMonth < 10)
	{
		currMonth = "0" + to_string(time.wMonth);
	}
	else
	{
		currMonth = to_string(time.wMonth);
	}

	if (time.wDay < 10)
	{
		currDay = "0" + to_string(time.wDay);
	}
	else
	{
		currDay = to_string(time.wDay);
	}

	return currYear + currMonth + currDay;
}

int writingWord(string& word, unsigned size, unsigned& key, View* v)
{
	unsigned start = word.size();
	backSpace(start, key, word, v);
	for (unsigned i = start; i < size; ++i)
	{
		if ((char)key >= 'a' && (char)key <= 'z' || (char)key == '-')
		{
			word.push_back(key);
			v->draw();
		}
		key = _getch();
		backSpace(i, key, word, v);
		if (UPorDOWNorENTER(key))
		{
			return UPorDOWNorENTER(key);
		}
	}
	while (key)
	{
		unsigned i = size - 1;
		if (backSpace(i, key, word, v))
		{
			backSpace(i, key, word, v);
			writingWord(word, size, key, v);
		}
		key = _getch();
		backSpace(i, key, word, v);
		if (UPorDOWNorENTER(key))
		{
			return UPorDOWNorENTER(key);
		}
	}
}

int writingNumber(string& word, unsigned size, unsigned& key, View* v)
{
	unsigned start = word.size();
	backSpace(start, key, word, v);
	for (unsigned i = start; i < size; ++i)
	{
		if ((char)key >= '0' && (char)key <= '9')
		{
			word.push_back(key);
			v->draw();
		}
		key = _getch();
		backSpace(i, key, word, v);
		if (UPorDOWNorENTER(key))
		{
			return UPorDOWNorENTER(key);
		}
	}
	while (key)
	{
		unsigned i = size - 1;
		if (backSpace(i, key, word, v))
		{
			backSpace(i, key, word, v);
			writingWord(word, size, key, v);
		}
		key = _getch();
		backSpace(i, key, word, v);
		if (UPorDOWNorENTER(key))
		{
			return UPorDOWNorENTER(key);
		}
	}
}