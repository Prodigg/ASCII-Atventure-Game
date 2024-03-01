#include "Engine.h"
#include <iostream>
#include <conio.h>
#include <io.h>
#include <fcntl.h>
#include <Windows.h>

Console::Console() {
	// init PrintArray
	for (size_t i = 0; i < PRINT_ARRAY_X; i++) {
		for (size_t t = 0; t < PRINT_ARRAY_Y; t++) {
			Console::PrintArray[i][t] = L" ";
		}
	}

	for (size_t i = 0; i < PRINT_ARRAY_X; i++) {
		for (size_t t = 0; t < PRINT_ARRAY_Y; t++) {
			Console::PrintColorArray[i][t] = 7;
		}
	}

}

Console ::~Console() {
}

void Console::Plot(int x, int y, std::wstring str, WORD TextColor) {
	std::wstring* wstringArray = new std::wstring[str.length() + 1];
	for (size_t i = 0; i < str.length() + 1; i++) {
		wstringArray[i] = L" ";
	}
	for (size_t i = 0; i < str.length() + 1; i++) {
		wstringArray[i].replace(1, 1, str); // ignore warning, false positive
	}
	//wstringArray[str.length() + 1] = L"\0";
	for (size_t i = 0; i < str.length() + 1; i++) {
		Console::PrintColorArray[x][y] = TextColor;
		Console::PrintArray[x][y] = str;
	}

	delete[] wstringArray;
	return;
}

void Console::Plot(int x, int y, std::wstring str) {
	Console::Plot(x, y, str, 7);
}

void Console::Clear() {
	for (size_t i = 0; i < PRINT_ARRAY_X; i++) {
		for (size_t t = 0; t < PRINT_ARRAY_Y; t++) {
			Console::PrintArray[i][t] = ' ';
		}
	}
}

std::wstring Console::getChar(int x, int y) {
	return Console::PrintArray[x][y];
}

void Console::ClearColor() {
	for (size_t i = 0; i < PRINT_ARRAY_X; i++) {
		for (size_t t = 0; t < PRINT_ARRAY_Y; t++) {
			Console::PrintColorArray[i][t] = 7;
		}
	}
	return;
}

WORD Console::getColor(int x, int y) {
	return Console::PrintColorArray[x][y];
}

Terminal::Terminal(int ScreenSizeX, int ScreenSizeY, Console* Console) : 
	console(Console), 
	screenSizeX(ScreenSizeX),
	screenSizeY(ScreenSizeY)  
{
	_setmode(_fileno(stdout), _O_WTEXT); // set CMD text Mode
	Terminal::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

Terminal::~Terminal() {

}

void Terminal::print() {

	for (size_t i = 0; i < Terminal::screenSizeX; i++) {
		for (size_t t = 0; t < Terminal::screenSizeY; t++) {
			SetConsoleTextAttribute(Terminal::hConsole, Terminal::console->getColor(i, t));
			std::wcout << Terminal::console->getChar(i, t);
		}
		std::wcout << std::endl;
	}
	return;
}

char Terminal::getKeyAction() {
	char tmp = ' ';
	tmp = _getch();
	return tmp;
}

void Terminal::clear() {
	system("cls");
	return;
}