#pragma once
#include <Windows.h>
#include <MMSystem.h>
#include <chrono>
#include <thread>

#define BLACK 0
#define D_BLUE 1
#define D_GREEN 2
#define D_CYAN 3
#define D_RED 4
#define PURPLE 5
#define D_YELLOW 6
#define L_GREY 7
#define D_GREY 8
#define BLUE 9
#define GREEN 10
#define CYAN 11
#define RED 12
#define MAGENTA 13
#define YELLOW 14
#define WHITE 15

int RGBHEX[16] = {
	0x111111,	 //EGA PALETTE DEFAULT BLACK
	0xAA0000,	 //EGA PALETTE DEFAULT BLUE
	0x00AA00,	 //EGA PALETTE DEFAULT GREEN
	0xAAAA00,	 //EGA PALETTE DEFAULT CYAN
	0x0000FF,	 //EGA PALETTE DEFAULT RED
	0xAA00AA,	 //EGA PALETTE DEFAULT PURPLE
	0x0055AA,	 //EGA PALETTE DEFAULT BRWON
	0xAAAAAA,	 //EGA PALETTE DEFAULT LIGHT GRAY
	0x555555,	 //EGA PALETTE DEFAULT DARK GREY
	0xFF5555,	 //EGA PALETTE DEFAULT LIGHT BLUE
	0x55FF55,	 //EGA PALETTE DEFAULT LIGHT GREEN
	0xFFFF55,	 //EGA PALETTE DEFAULT LIGHT CYAN
	0x5555FF,	 //EGA PALETTE DEFAULT LIGHT RED
	0xFF55FF,	 //EGA PALETTE DEFAULT MAGENTA
	0x22FFFF,	 //EGA PALETTE DEFAULT YELLOW
	0xFFFFFF	 //EGA PALETTE DEFAULT WHITE
};

// Setting some windows variabels
static CONSOLE_SCREEN_BUFFER_INFOEX csbiInfo;
static CONSOLE_CURSOR_INFO cursorInfo;
static SMALL_RECT m_rectWindow;
static CHAR_INFO* screen = new CHAR_INFO[nScreenWidth * nScreenHeight];

static HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
static WORD attribute;

int fontSize = 8;

// Debug
bool showDebugMap = false;

void GeneralFunctions()
{
	//Set font
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 12;
	cfi.dwFontSize.Y = 16;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Terminal");
	SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);

	// Hide console cursor
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void UseDefaultCustomColorPalette()
{
	csbiInfo.cbSize = sizeof(csbiInfo);
	GetConsoleScreenBufferInfoEx(hConsole, &csbiInfo);

	// Set new color palette
	for (int i = 0; i < 16; i++)
		csbiInfo.ColorTable[i] = RGBHEX[i];

	// Set Console Window
	csbiInfo.wPopupAttributes = 0;
	csbiInfo.srWindow = { 0, 0, nScreenWidth, nScreenHeight };
	csbiInfo.dwSize = { nScreenWidth, nScreenHeight };
	csbiInfo.wAttributes = attribute;
	SetConsoleScreenBufferInfoEx(hConsole, &csbiInfo);
}

void SoundPlay(const char* sound)
{
	PlaySound(TEXT(sound), NULL, SND_ASYNC);
}

void UpdateConsoleBufferSize()
{
	SetConsoleActiveScreenBuffer(hConsole);
	m_rectWindow = { 0, 0, nScreenWidth, nScreenHeight };

	// Set Console Window
	csbiInfo.wPopupAttributes = 0;
	csbiInfo.srWindow = { 0, 0, nScreenWidth, nScreenHeight };
	csbiInfo.dwSize = { nScreenWidth, nScreenHeight };
	csbiInfo.wAttributes = attribute;
	SetConsoleScreenBufferInfoEx(hConsole, &csbiInfo);
}

void Update(bool updateScreen, bool updateOutside, bool updateInside)
{
	//Debug only drawmap
	if (showDebugMap == true)
	{
		for (int y = 0; y < 9; y++) {
			for (int x = 0; x < 9; x++) {
				OutsideArray[y][x] = mapArray[y][x];
				OutsideColorArray[y][x] = MAGENTA;
			}
		}
	}

	//Main Draw outside
	if (updateOutside == true)
	{
		for (int y = 0; y < nScreenHeight; y++) {
			for (int x = 0; x < nScreenWidth; x++) {
				//Draw color array
				for (int i = -1; i < 16; i++) {
					if ((OutsideColorArray[y][x] == i) && (OutsideColorArray[y][x] != -1))
						screen[y * nScreenWidth + x].Attributes = i;
				}
				//Draw chraracter array
				screen[y * nScreenWidth + x].Char.AsciiChar = OutsideArray[y][x];
			}
		}
	}
	//Main Draw
	if (updateInside == true)
	{
		for (int y = 0; y < nMineFieldHeight; y++) {
			for (int x = 0; x < nMineFieldWidth; x++) {
				//Draw color array
				for (int i = -1; i < 16; i++) {
					if ((mainColorArray[y][x] == i) && (mainColorArray[y][x] != -1))
						screen[(y + yOffset) * nScreenWidth + (x + xOffset)].Attributes = i;
				}
				//Draw chraracter array
				screen[(y + yOffset) * nScreenWidth + (x + xOffset)].Char.AsciiChar = mainArray[y][x];
			}
		}
	}
	GeneralFunctions();
	UseDefaultCustomColorPalette();
	if (updateScreen == true) WriteConsoleOutput(hConsole, screen, { nScreenWidth, nScreenHeight }, { 0, 0 }, &m_rectWindow);
}
