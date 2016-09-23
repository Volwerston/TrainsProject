#pragma once

#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

enum class Color
{
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHT_GRAY,
	DARK_GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_MAGENTA,
	YELLOW,
	WHITE
};

class Printer
{
	Color font;
	Color background;

public:
	Printer(Color = Color::WHITE, Color = Color::BLACK);

	template <class T>
	void print(T text) const
	{

		int _font = static_cast<int>(font);
		int _back = static_cast<int>(background);

		SetConsoleTextAttribute(hconsole, _font + 16 * _back);

		ostringstream out;
		out << text;
		cout << out.str() << endl;

		cursor.X += out.str().size();

		setCursorAt(cursor.X, cursor.Y);

		SetConsoleTextAttribute(hconsole, 15);  // return to normal state
	}

	string indicateColor(Color) const;

	string getFont() const;
	string getBackground() const;
};