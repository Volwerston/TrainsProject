#include "RailCarView.h"

HPEN penForRailCarSeats1, penForRailCarSeats2 = CreatePen(PS_SOLID, 4, RGB(44, 62, 80));
HPEN penForRailCarSeatsBold1, penForRailCarSeatsBold2 = CreatePen(PS_SOLID, 8, RGB(44, 62, 80));
HPEN penForRailCarSelectedSold1, penForRailCarSelectedSold2 = CreatePen(PS_SOLID, 8, RGB(127, 140, 141));

HBRUSH brushForRailCarSeat1, brushForRailCarSeat2 = CreateSolidBrush(RGB(189, 195, 199));
HBRUSH brushForRailCarSeatSelected1, brushForRailCarSeatSelected2 = CreateSolidBrush(RGB(127, 140, 141));
HBRUSH brushForRailCarSeatSold1, brushForRailCarSeatSold2 = CreateSolidBrush(RGB(44, 62, 80));

RailCarView::RailCarView(const TripData _tripData) :tripData(_tripData) {}

void RailCarView::draw()
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
}

void RailCarView::drawSeat(int num)
{
	if (num <= 1)
	{
		RoundRect(hdc, 150 + (num)* 150, 150, 230 + (num)* 150, 230, 20, 20);
	}
	else if (num > 1 && num <= 3)
	{
		RoundRect(hdc, 420 + (num - 2) * 150, 150, 500 + (num - 2) * 150, 230, 20, 20);
	}
	else if (num > 3 && num <= 5)
	{
		RoundRect(hdc, 690 + (num - 4) * 150, 150, 770 + (num - 4) * 150, 230, 20, 20);
	}
	else if (num > 5 && num <= 7)
	{
		RoundRect(hdc, 960 + (num - 6) * 150, 150, 1040 + (num - 6) * 150, 230, 20, 20);
	}
	else if (num > 7 && num <= 9)
	{
		RoundRect(hdc, 150 + (num - 8) * 150, 280, 230 + (num - 8) * 150, 360, 20, 20);
	}
	else if (num > 9 && num <= 11)
	{
		RoundRect(hdc, 420 + (num - 10) * 150, 280, 500 + (num - 10) * 150, 360, 20, 20);
	}
	else if (num > 11 && num <= 13)
	{
		RoundRect(hdc, 690 + (num - 12) * 150, 280, 770 + (num - 12) * 150, 360, 20, 20);
	}
	else if (num > 13 && num <= 15)
	{
		RoundRect(hdc, 960 + (num - 14) * 150, 280, 1040 + (num - 14) * 150, 360, 20, 20);
	}
	else if (num > 15 && num <= 17)
	{
		RoundRect(hdc, 150 + (num - 16) * 150, 470, 230 + (num - 16) * 150, 550, 20, 20);
	}
	else if (num > 17 && num <= 19)
	{
		RoundRect(hdc, 420 + (num - 18) * 150, 470, 500 + (num - 18) * 150, 550, 20, 20);
	}
	else if (num > 19 && num <= 21)
	{
		RoundRect(hdc, 690 + (num - 20) * 150, 470, 770 + (num - 20) * 150, 550, 20, 20);
	}
	else if (num > 21 && num <= 23)
	{
		RoundRect(hdc, 960 + (num - 22) * 150, 470, 1040 + (num - 22) * 150, 550, 20, 20);
	}
}

void RailCarView::drawSelected(int selected)
{
	penForRailCarSeats1 = (HPEN)SelectObject(hdc, penForRailCarSeats2);
	brushForRailCarSeatSelected1 = (HBRUSH)SelectObject(hdc, brushForRailCarSeatSelected2);
	drawSeat(selected);
	brushForRailCarSeat1 = (HBRUSH)SelectObject(hdc, brushForRailCarSeat2);
}

void RailCarView::drawSold(vector<unsigned> vec, int selected)
{
	brushForRailCarSeatSold1 = (HBRUSH)SelectObject(hdc, brushForRailCarSeatSold2);
	for (size_t i = 0; i < vec.size(); i++)
	{
		drawSeat(vec[i]);
		if (vec[i] == selected)
		{
			penForRailCarSelectedSold1 = (HPEN)SelectObject(hdc, penForRailCarSelectedSold2);
			drawSeat(selected);
			penForRailCarSeats1 = (HPEN)SelectObject(hdc, penForRailCarSeats2);
		}
	}
	brushForRailCarSeatSelected1 = (HBRUSH)SelectObject(hdc, brushForRailCarSeatSelected2);
}


View* RailCarView::handle()
{
	View::clean();
	draw();
	int selected = 0;
	bool chosen = false;

	Train currentTrain = tripData.getTrain();
	vector < RailCar> railCars = currentTrain.getVectorOfRailCars();
	RailCar currentRailCar = railCars[tripData.getNumberOfRailCar()];
	vector<unsigned> vectorOfBookedSeats = currentRailCar.getVectotOfBookedSeats();
	drawSelected(selected);

	while (!chosen)
	{
		switch (_getch())
		{
		case 77:
			selected++;
			if (selected > 23 || selected == 8 || selected == 16)
			{
				selected--;
			}
			else
			{
				drawSelected(selected);
				drawSeat(selected - 1);
				drawSold(vectorOfBookedSeats, selected);
			}
			break;
		case 75:
			selected--;
			if (selected < 0 || selected == 7 || selected == 15)
			{
				selected++;
			}
			else
			{
				drawSelected(selected);
				drawSeat(selected + 1);
				drawSold(vectorOfBookedSeats, selected);
			}
			break;
		case 72:
			selected -= 8;
			if (selected < 0)
			{
				selected += 8;
			}
			else
			{
				drawSelected(selected);
				drawSeat(selected + 8);
				drawSold(vectorOfBookedSeats, selected);

			}
			break;
		case 80:
			selected += 8;
			if (selected > 23)
			{
				selected -= 8;
			}
			else
			{
				drawSelected(selected);
				drawSeat(selected - 8);
				drawSold(vectorOfBookedSeats, selected);
			}
			break;
		case 13:
			brushForRailCarSeatSold1 = (HBRUSH)SelectObject(hdc, brushForRailCarSeatSold2);
			drawSeat(selected);
			vectorOfBookedSeats.push_back(selected);
			tripData.pushToVectorOfSeats(selected);
			drawSold(vectorOfBookedSeats, selected);
			for (size_t i = 0; i < vectorOfBookedSeats.size(); i++)
			{
				cout << vectorOfBookedSeats[i] << " ";
			}
			break;
		case 27:
			return 0;
		case 32:
			chosen = true;
			break;
		}
	}

	SelectObject(hdc, penForRailCarSeats1);
	SelectObject(hdc, penForRailCarSeatsBold1);
	SelectObject(hdc, brushForRailCarSeat1);
	SelectObject(hdc, brushForRailCarSeatSelected1);
	SelectObject(hdc, brushForRailCarSeatSold1);
	ReleaseDC(hwnd, hdc);
	DeleteObject(penForRailCarSeats2);
	DeleteObject(penForRailCarSeatsBold2);
	DeleteObject(brushForRailCarSeat2);
	DeleteObject(brushForRailCarSeatSelected2);
	DeleteObject(brushForRailCarSeatSold2);

	
	View *nextView = new RailCarView(tripData);
	return nextView;
}