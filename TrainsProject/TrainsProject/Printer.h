#pragma once

#include <iostream>
#include <Windows.h>
#include <string>
//#include "Console.h"

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

	void print(string text) const;
	string indicateColor(Color) const;

	string getFont() const;
	string getBackground() const;
};