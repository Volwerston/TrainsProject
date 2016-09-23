#include "Console.h"

HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
HWND hwnd = GetConsoleWindow();
HDC hdc = GetDC(hwnd);
COORD cursor;
const int consoleWidth = 123;
const int consoleHeight = 39;

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
	SMALL_RECT r;
	r.Left = 0;
	r.Top = 0;
	r.Right = consoleWidth - 1;
	r.Bottom = consoleHeight - 1;
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &r);

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

BOOL DrawLine(HDC hdc, int x1, int y1, int x2, int y2)
{
	POINT pt;
	MoveToEx(hdc, x1, y1, &pt);
	return LineTo(hdc, x2, y2);
}