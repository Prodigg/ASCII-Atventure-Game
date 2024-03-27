#pragma once
#ifndef __ENGINE__
#define __ENGINE__


#include <string>
#include <Windows.h>

#define PRINT_ARRAY_X 50
#define PRINT_ARRAY_Y 80

class Console {
public:
	Console ();
	void Plot(int x, int y, std::wstring str);
	void Plot(int x, int y, std::wstring str, WORD TextColor);
	void PlortColor(int x, int y, WORD TextColor);
	void Clear();
	void ClearColor();
	std::wstring getChar(int x, int y);
	WORD getColor(int x, int y);

	~Console ();

private:
	std::wstring PrintArray[PRINT_ARRAY_X][PRINT_ARRAY_Y]; // caracters
	WORD PrintColorArray[PRINT_ARRAY_X][PRINT_ARRAY_Y]; // collor codes
};

class Terminal {
public:
	Terminal ( int ScreenSizeX, int ScreenSizeY, Console* Console);
	void print();
	~Terminal ();
	char getKeyAction();
	void clear();

	void resizeWindow(int width, int hight);

private:
	int screenSizeX;
	int screenSizeY;
	Console* console;
	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	CONSOLE_FONT_INFOEX cfi;
	HWND HWNDconsole;
	RECT r;
};
#endif // !__ENGINE__