#pragma once

#include "Printer.h"

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

string Printer::getFont() const
{
	return indicateColor(font);
}

string Printer::getBackground() const
{
	return indicateColor(background);
}
