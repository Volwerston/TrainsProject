#include "View.h"
#include "Printer.h"
#include "Console.h"

View::View()
{
}

View::View(TripData tripData)
{ 
}

void View::drawBackground(int left, int top, int width, int height, COLORREF background) // draws background of the game
{
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SelectObject(hdc, GetStockObject(DC_PEN));

	SetDCBrushColor(hdc, background);
	SetDCPenColor(hdc, background);

	GetClientRect(hwnd, &rect);
	RoundRect(hdc, left, top, left + width, top + height, 0, 0);
}

void View::clean()
{
	system("cls");
	drawBackground(0, 0, consoleWidth*fontWidth, consoleHeight*fontHeight, RGB(0, 128, 128));
}