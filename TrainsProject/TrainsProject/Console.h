#pragma once
#include <sstream>
#include <string>
#include "Printer.h"

using namespace std;

void setConsoleProperties();

void setCursorAt(int, int);

void printAtCenter(string st, const Printer& p);

void scrollOff(int width, int height);

void setConsoleSize(int width, int height);

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

#define ENTER_KEY 13
#define SPACEBAR 32
#define BACK_SPACE 8
#define ESC 27
#define ARROW_KEY 224
#define UP 72
#define DOWN 80
#define ASCII_ZERO 48