#include "Engine.h"
#include <iostream>
#include <conio.h>
#include <io.h>
#include <fcntl.h>
#include <Windows.h>
#include <vector>

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
	/*
	std::vector<std::wstring>* wstringVector = new std::vector<std::wstring>;
	//std::wstring* wstringArray = new std::wstring[str.size()];
	for (size_t i = 0; i < str.size(); i++) {
		//wstringArray[i] = L" ";
		//wstringVector->push_back(L" ");
	}
	
	for (size_t i = 0; i < str.size(); i++) {
		//wstringArray[i].replace(1, 1, str, i); // ignore warning, false positive
		wstringVector->push_back(str.at(i));
	}
	//wstringArray[str.length() + 1] = L"\0";*/
	for (size_t i = 0; i < str.size(); i++) {
		Console::PrintColorArray[x][i + y] = TextColor;
		Console::PrintArray[x][i + y] = str.at(i);
	}

	//delete[] wstringArray;
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

void Console::PlortColor(int x, int y, WORD TextColor) {
	Console::PrintColorArray[x][y] = TextColor;
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
	for (size_t i = Terminal::screenSizeX - 1; i > 0; i--) {
		for (size_t t = Terminal::screenSizeY - 1; t > 0; t--) {
			if (Terminal::console->getChar(i, t) == L" ") { 
				console->Plot(i, t, L""); 
			}
			else break;
		}
	}


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