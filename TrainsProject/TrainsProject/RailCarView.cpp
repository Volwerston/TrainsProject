#include "RailCarView.h"
#include <iterator>
#include <algorithm>

HPEN penForRailCarSeats1, penForRailCarSeats2 = CreatePen(PS_SOLID, 4, RGB(44, 62, 80));
HPEN penForRailCarSeatsBold1, penForRailCarSeatsBold2 = CreatePen(PS_SOLID, 8, RGB(44, 62, 80));
HPEN penForRailCarSelectedSold1, penForRailCarSelectedSold2 = CreatePen(PS_SOLID, 8, RGB(127, 140, 141));

HBRUSH brushForRailCarSeat1, brushForRailCarSeat2 = CreateSolidBrush(RGB(189, 195, 199));
HBRUSH brushForRailCarSeatSelected1, brushForRailCarSeatSelected2 = CreateSolidBrush(RGB(127, 140, 141));
HBRUSH brushForRailCarSeatSold1, brushForRailCarSeatSold2 = CreateSolidBrush(RGB(44, 62, 80));
HBRUSH brushForRailCarFirstClassSeat1, brushForRailCarFirstClassSeat2 = CreateSolidBrush(RGB(52, 152, 219));
HBRUSH brushForRailCarFirstClassSeatSelected1, brushForRailCarFirstClassSeatSelected2 = CreateSolidBrush(RGB(142, 68, 173));

Printer printer(Color::WHITE, Color::CYAN);

RailCarView::RailCarView(const TripData _tripData) :tripData(_tripData) {}

void RailCarView::draw()
{
	clean();
	penForRailCarSeats1 = (HPEN)SelectObject(hdc, penForRailCarSeats2);
	brushForRailCarSeat1 = (HBRUSH)SelectObject(hdc, brushForRailCarSeat2);

	RoundRect(hdc, 120, 100, 1220, 600, 100, 100);
	
	setCursorAt(55, 36);
	printAtCenter("Press Enter to continue", printer);

	brushForRailCarSeat1 = (HBRUSH)SelectObject(hdc, brushForRailCarSeat2);
	
	Train currentTrain = tripData.getTrain();
	vector < RailCar> railCars = currentTrain.getVectorOfRailCars();
	RailCar currentRailCar = railCars[tripData.getNumberOfRailCar()-1];
	if (currentRailCar.getType() == TypeOfRailCar::FirstClass)
	{
		brushForRailCarFirstClassSeat1 = (HBRUSH)SelectObject(hdc, brushForRailCarFirstClassSeat2);
		for (int i = 0; i < 4; i++)
		{
			RoundRect(hdc, 150 + i * 270, 150, 380 + i * 270, 360, 20, 20);
		}

		penForRailCarSeatsBold1 = (HPEN)SelectObject(hdc, penForRailCarSeatsBold2);
		DrawLine(hdc, 122, 380, 210, 380);
		DrawLine(hdc, 1130, 380, 1217, 380);

		for (int i = 0; i < 3; i++)
		{
			DrawLine(hdc, 400 + i * 270, 102, 400 + i * 270, 380);
			DrawLine(hdc, 320 + i * 270, 380, 480 + i * 270, 380);
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			RoundRect(hdc, 150 + i * 270, 150, 230 + i * 270, 230, 20, 20);
			RoundRect(hdc, 150 + i * 270, 280, 230 + i * 270, 360, 20, 20);

			RoundRect(hdc, 300 + i * 270, 150, 380 + i * 270, 230, 20, 20);
			RoundRect(hdc, 300 + i * 270, 280, 380 + i * 270, 360, 20, 20);
		}
		penForRailCarSeatsBold1 = (HPEN)SelectObject(hdc, penForRailCarSeatsBold2);
		DrawLine(hdc, 122, 380, 210, 380);
		DrawLine(hdc, 1130, 380, 1217, 380);
		for (int i = 0; i < 3; i++)
		{
			DrawLine(hdc, 400 + i * 270, 102, 400 + i * 270, 380);
			DrawLine(hdc, 320 + i * 270, 380, 480 + i * 270, 380);
		}
		if (currentRailCar.getType() == TypeOfRailCar::ThirdClass)
		{
			penForRailCarSeats1 = (HPEN)SelectObject(hdc, penForRailCarSeats2);
			for (int i = 0; i < 4; i++)
			{
				RoundRect(hdc, 150 + i * 270, 470, 230 + i * 270, 550, 20, 20);
				RoundRect(hdc, 300 + i * 270, 470, 380 + i * 270, 550, 20, 20);
			}
			penForRailCarSeatsBold1 = (HPEN)SelectObject(hdc, penForRailCarSeatsBold2);
			for (int i = 0; i < 3; i++)
			{
				DrawLine(hdc, 400 + i * 270, 490, 400 + i * 270, 597);
			}
		}
	}
}

void RailCarView::drawSeat(int num)
{
	Train currentTrain = tripData.getTrain();
	vector < RailCar> railCars = currentTrain.getVectorOfRailCars();
	RailCar currentRailCar = railCars[tripData.getNumberOfRailCar()-1];
	if (currentRailCar.getType() == TypeOfRailCar::ThirdClass)
	{
		if (num <= 1 || (num > 3 && num <= 5) || (num > 7 && num <= 9) || (num > 11 && num <= 13))
		{
			RoundRect(hdc, 150 + (num)* 150 - 30 * (num / 2) - 1080 * (num / 8), 150 + 130 * (num / 8), 
				230 + (num)* 150 - 30 * (num / 2) - 1080 * (num / 8), 230 + 130 * (num / 8), 20, 20);
		}
		else if ((num > 1 && num <= 3) || (num > 5 && num <= 7) || (num > 9 && num <= 11) || (num > 13 && num <= 15))
		{
			RoundRect(hdc, 420 + (num - 2) * 150 - 30 * ((num - 2) / 2) - 1080 * (num / 10), 150 + 130 * (num / 10),
				500 + (num - 2) * 150 - 30 * ((num - 2) / 2) - 1080 * (num / 10), 230 + 130 * (num / 10), 20, 20);
		}
		else if ((num > 15 && num <= 17) || (num > 19 && num <= 21))
		{
			RoundRect(hdc, 150 + (num - 16) * 150 - 30 * ((num - 16) / 2), 470, 230 + (num - 16) * 150 - 30 * ((num - 16) / 2), 550, 20, 20);
		}
		else if ((num > 17 && num <= 19) || (num > 21 && num <= 23))
		{
			RoundRect(hdc, 420 + (num - 18) * 150 - 30 * ((num - 18) / 2), 470, 500 + (num - 18) * 150 - 30 * ((num - 18) / 2), 550, 20, 20);
		}
	}
	else if (currentRailCar.getType() == TypeOfRailCar::SecondClass)
	{
		if (num <= 1 || (num > 3 && num <= 5) || (num > 7 && num <= 9) || (num > 11 && num <= 13))
		{
			RoundRect(hdc, 150 + (num)* 150 - 30 * (num / 2) - 1080 * (num / 8), 150 + 130 * (num / 8),
				230 + (num)* 150 - 30 * (num / 2) - 1080 * (num / 8), 230 + 130 * (num / 8), 20, 20);
		}
		else if ((num > 1 && num <= 3) || (num > 5 && num <= 7) || (num > 9 && num <= 11) || (num > 13 && num <= 15))
		{
			RoundRect(hdc, 420 + (num - 2) * 150 - 30 * ((num - 2) / 2) - 1080 * (num / 10), 150 + 130 * (num / 10),
				500 + (num - 2) * 150 - 30 * ((num - 2) / 2) - 1080 * (num / 10), 230 + 130 * (num / 10), 20, 20);
		}
	}
	else
	{
		if (num <= 1)
		{
			RoundRect(hdc, 150 + (num)* 270, 150, 380 + (num)* 270, 360, 20, 20);
		}
		else if (num > 1 && num <= 3)
		{
			RoundRect(hdc, 690 + (num - 2) * 270, 150, 920 + (num - 2) * 270, 360, 20, 20);
		}
	}
}

void RailCarView::drawSelected(int selected)
{
	Train currentTrain = tripData.getTrain();
	vector < RailCar> railCars = currentTrain.getVectorOfRailCars();
	RailCar currentRailCar = railCars[tripData.getNumberOfRailCar()-1];
	penForRailCarSeats1 = (HPEN)SelectObject(hdc, penForRailCarSeats2);
	if (currentRailCar.getType() == TypeOfRailCar::FirstClass)
	{
		brushForRailCarFirstClassSeatSelected1 = (HBRUSH)SelectObject(hdc, brushForRailCarFirstClassSeatSelected2);
	}
	else
	{
		brushForRailCarSeatSelected1 = (HBRUSH)SelectObject(hdc, brushForRailCarSeatSelected2);
	}
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

	View *nextView = nullptr;

	Train currentTrain = tripData.getTrain();
	vector < RailCar> railCars = currentTrain.getVectorOfRailCars();
	RailCar currentRailCar = railCars[tripData.getNumberOfRailCar()-1];
	vector<unsigned> vectorOfBookedSeats = currentRailCar.getVectotOfBookedSeats();
	vector<unsigned> vectorOfOrderedSeats = tripData.getVectorOfSeats();
	drawSelected(selected);
	drawSold(vectorOfBookedSeats, selected);
	drawSold(vectorOfOrderedSeats, selected);
	bool isBooked = false;
	while (!chosen)
	{
		switch (_getch())
		{
		case RIGHT:
			selected++;
			if (currentRailCar.getType() == TypeOfRailCar::ThirdClass)
			{
				if (selected > 23 || selected == 8 || selected == 16)
				{
					selected--;
				}
				else
				{
					drawSelected(selected);
					drawSeat(selected - 1);
					drawSold(vectorOfBookedSeats, selected);
					drawSold(vectorOfOrderedSeats, selected);
				}
			}
			else if (currentRailCar.getType() == TypeOfRailCar::SecondClass)
			{
				if (selected > 15 || selected == 8 )
				{
					selected--;
				}
				else
				{
					drawSelected(selected);
					drawSeat(selected - 1);
					drawSold(vectorOfBookedSeats, selected);
					drawSold(vectorOfOrderedSeats, selected);
				}
			}
			else
			{
				if (selected > 3)
				{
					selected--;
				}
				else
				{
					brushForRailCarFirstClassSeatSelected1 = (HBRUSH)SelectObject(hdc, brushForRailCarFirstClassSeatSelected2);
					drawSelected(selected);
					brushForRailCarFirstClassSeat1 = (HBRUSH)SelectObject(hdc, brushForRailCarFirstClassSeat2);
					drawSeat(selected - 1);
					drawSold(vectorOfBookedSeats, selected);
					drawSold(vectorOfOrderedSeats, selected);
				}
			}
			break;
		case LEFT:
			selected--;
			if (currentRailCar.getType() == TypeOfRailCar::ThirdClass)
			{
				if (selected < 0 || selected == 7 || selected == 15)
				{
					selected++;
				}
				else
				{
					drawSelected(selected);
					drawSeat(selected + 1);
					drawSold(vectorOfBookedSeats, selected);
					drawSold(vectorOfOrderedSeats, selected);
				}
			}
			else if (currentRailCar.getType() == TypeOfRailCar::SecondClass)
			{
				if (selected < 0 || selected == 7)
				{
					selected++;
				}
				else
				{
					drawSelected(selected);
					drawSeat(selected + 1);
					drawSold(vectorOfBookedSeats, selected);
					drawSold(vectorOfOrderedSeats, selected);
				}
			}
			else
			{
				if (selected < 0)
				{
					selected++;
				}
				else
				{
					brushForRailCarFirstClassSeatSelected1 = (HBRUSH)SelectObject(hdc, brushForRailCarFirstClassSeatSelected2);
					drawSelected(selected);
					brushForRailCarFirstClassSeat1 = (HBRUSH)SelectObject(hdc, brushForRailCarFirstClassSeat2);
					drawSeat(selected + 1);
					drawSold(vectorOfBookedSeats, selected);
					drawSold(vectorOfOrderedSeats, selected);
				}
			}
			break;
		case UP:
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
				drawSold(vectorOfOrderedSeats, selected);
			}
			break;
		case DOWN:
			selected += 8;
			if (currentRailCar.getType() == TypeOfRailCar::ThirdClass)
			{
				if (selected > 23)
				{
					selected -= 8;
				}
				else
				{
					drawSelected(selected);
					drawSeat(selected - 8);
					drawSold(vectorOfBookedSeats, selected);
					drawSold(vectorOfOrderedSeats, selected);
				}
			}
			else if (currentRailCar.getType() == TypeOfRailCar::SecondClass)
			{
				if (selected > 15)
				{
					selected -= 8;
				}
				else
				{
					drawSelected(selected);
					drawSeat(selected - 8);
					drawSold(vectorOfBookedSeats, selected);
					drawSold(vectorOfOrderedSeats, selected);
				}
			}
			else
			{
				if (selected > 3)
				{
					selected -= 8;
				}
				else
				{
					drawSelected(selected);
					drawSeat(selected - 8);
					drawSold(vectorOfBookedSeats, selected);
					drawSold(vectorOfOrderedSeats, selected);
				}
			}
			break;
		case SPACEBAR:
			isBooked = false;

				for (size_t i = 0; i < vectorOfBookedSeats.size(); i++)
				{
					if (selected == vectorOfBookedSeats[i])
					{
						isBooked = true;
						break;
					}
				}

			if (!isBooked)
			{
				
				auto it = vectorOfOrderedSeats.begin();
				bool contained = false;

				while (it != vectorOfOrderedSeats.end())
				{
					if ((*it) == selected)
					{
						contained = true;
						it = vectorOfOrderedSeats.erase(it);
						break;
					}
					else
					{
						++it;
					}
				}

				if (!contained)
				{
					vectorOfOrderedSeats.push_back(selected);
				}

				drawSelected(selected);
			}

			drawSold(vectorOfBookedSeats, selected);
			drawSold(vectorOfOrderedSeats, selected);
			break;
		case ESC:
			nextView = new ChooseCarView(tripData);
			chosen = true;
			break;
		case ENTER_KEY:
			tripData.setDataOfChosenSeats(vectorOfOrderedSeats);
			nextView = new ChooseCarView(tripData);
			chosen = true;
			break;
		}
	}
	
	/*
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
	*/

	return nextView;
}