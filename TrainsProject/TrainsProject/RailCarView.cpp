#include "RailCarView.h"

HPEN penForRailCarSeats1, penForRailCarSeats2 = CreatePen(PS_SOLID, 4, RGB(44, 62, 80));
HPEN penForRailCarSeatsBold1, penForRailCarSeatsBold2 = CreatePen(PS_SOLID, 8, RGB(44, 62, 80));
HBRUSH brushForRailCarSeat1, brushForRailCarSeat2 = CreateSolidBrush(RGB(189, 195, 199));
HBRUSH brushForRailCarSeatSelected1, brushForRailCarSeatSelected2 = CreateSolidBrush(RGB(127, 140, 141));
HBRUSH brushForRailCarSeatSold1, brushForRailCarSeatSold2 = CreateSolidBrush(RGB(44, 62, 80));

RailCarView::RailCarView(TripData tripData) :
	date(tripData.getDate()),
	departurePoint(tripData.getDeparturePoint()),
	arrivalPoint(tripData.getArrivalPoint()),
	numberOfTrain(tripData.getNumberOfTrain()),
	numberOfRailcar(tripData.getNumberOfRailCar()),
	vectorOfSeats(tripData.getVectorOfSeats())
{
}

void RailCarView::drawRailCar()
{
	penForRailCarSeats1 = (HPEN)SelectObject(hdc, penForRailCarSeats2);
	brushForRailCarSeat1 = (HBRUSH)SelectObject(hdc, brushForRailCarSeat2);

	RoundRect(hdc, 120, 100, 1220, 600, 100, 100);

	for (int i = 0; i < 4; i++)
	{
		RoundRect(hdc, 150 + i * 270, 150, 230 + i * 270, 230, 20, 20);
		RoundRect(hdc, 150 + i * 270, 280, 230 + i * 270, 360, 20, 20);
		RoundRect(hdc, 150 + i * 270, 470, 230 + i * 270, 550, 20, 20);

		RoundRect(hdc, 300 + i * 270, 150, 380 + i * 270, 230, 20, 20);
		RoundRect(hdc, 300 + i * 270, 280, 380 + i * 270, 360, 20, 20);
		RoundRect(hdc, 300 + i * 270, 470, 380 + i * 270, 550, 20, 20);
	}

	penForRailCarSeatsBold1 = (HPEN)SelectObject(hdc, penForRailCarSeatsBold2);
	DrawLine(hdc, 122, 380, 210, 380);
	DrawLine(hdc, 1130, 380, 1217, 380);

	for (int i = 0; i < 3; i++)
	{
		DrawLine(hdc, 400 + i * 270, 102, 400 + i * 270, 380);
		DrawLine(hdc, 400 + i * 270, 490, 400 + i * 270, 597);
		DrawLine(hdc, 320 + i * 270, 380, 480 + i * 270, 380);
	}

	SelectObject(hdc, penForRailCarSeats1);
	SelectObject(hdc, penForRailCarSeatsBold1);
	SelectObject(hdc, brushForRailCarSeat1);
	ReleaseDC(hwnd, hdc);
	DeleteObject(penForRailCarSeats2);
	DeleteObject(penForRailCarSeatsBold2);
	DeleteObject(brushForRailCarSeat2);
}

void RailCarView::draw()
{}

View* RailCarView::handle()
{
	View* nextView = new RailCarView(TripData());
	return nextView;
}