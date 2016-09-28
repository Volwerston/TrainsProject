#pragma once

#include "Printer.h"
#include "Console.h"
using namespace std;

Printer::Printer(Color f, Color back)
	: font(f), background(back)
{
}

string Printer::indicateColor(Color _color) const
{
	string col;

	switch (_color)
	{
	case Color::BLACK: col = "BLACK";
		break;
	case Color::BLUE: col = "BLUE";
		break;
	case Color::GREEN: col = "GREEN";
		break;
	case Color::CYAN: col = "CYAN";
		break;
	case Color::RED: col = "RED";
		break;
	case Color::MAGENTA: col = "MAGENTA";
		break;
	case Color::BROWN: col = "BROWN";
		break;
	case Color::LIGHT_GRAY: col = "LIGHT_GRAY";
		break;
	case Color::DARK_GRAY: col = "DARK_GRAY";
		break;
	case Color::LIGHT_BLUE: col = "LIGHT_BLUE";
		break;
	case Color::LIGHT_GREEN: col = "LIGHT_GREEN";
		break;
	case Color::LIGHT_CYAN: col = "LIGHT_CYAN";
		break;
	case Color::LIGHT_RED: col = "LIGHT_RED";
		break;
	case Color::LIGHT_MAGENTA: col = "LIGHT_MAGENTA";
		break;
	case Color::YELLOW: col = "YELLOW";
		break;
	case Color::WHITE: col = "WHITE";
		break;
	default: col = "No such color";
	}
	return col;
}
void Printer::print(string text) const
{

	int _font = static_cast<int>(font);
	int _back = static_cast<int>(background);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _font + 16 * _back);


	cout << text;

	cursor.X += text.size();

	setCursorAt(cursor.X, cursor.Y);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);  // return to normal state
}

string Printer::getFont() const
{
	return indicateColor(font);
}

string Printer::getBackground() const
{
	return indicateColor(background);
}