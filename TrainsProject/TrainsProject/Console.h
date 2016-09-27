#pragma once
#include <sstream>
#include <string>
#include "Printer.h"

using namespace std;

void setConsoleProperties();

void setCursorAt(int, int);

void printAtCenter(string st, const Printer& p);

void scrollOff(int width, int height);

BOOL DrawLine(HDC, int, int, int, int);

extern HWND hwnd;
extern HANDLE hconsole;
extern HDC hdc;
extern COORD cursor;
extern RECT rect;

extern Printer headline;
extern Printer menuActive;
extern Printer menuPassive; 
extern Printer techData;
extern Printer stats;

extern const int consoleWidth;
extern const int consoleHeight;
extern const int fontWidth;
extern const int fontHeight;