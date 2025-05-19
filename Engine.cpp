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
	Terminal::HWNDconsole = GetConsoleWindow();
	resizeWindow(1400, 900);
}

Terminal::~Terminal() {

}

void Terminal::print() {
	for (size_t i = Terminal::screenSizeX - 1; i > 0; i--) {
		for (size_t t = Terminal::screenSizeY - 1; t > 0; t--) {
			if (Terminal::console->getChar(i, t) == L" " && Terminal::console->getColor(i, t) == 0x07) { 
				console->Plot(i, t, L"}"); 
			}
			else break;
		}
	}


	for (size_t i = 0; i < Terminal::screenSizeX; i++) {
		for (size_t t = 0; t < Terminal::screenSizeY; t++) {
			if (!((Terminal::console->getChar(i, t) == L"}") && Terminal::console->getColor(i, t) == 0x07)) {
				SetConsoleTextAttribute(Terminal::hConsole, Terminal::console->getColor(i, t));
				std::wcout << Terminal::console->getChar(i, t);
			}
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

bool Terminal::isKeyPressed() {
	return _kbhit();
}

void Terminal::clear() {
	system("cls");
	return;
}

void Terminal::resizeWindow(int width, int hight) {
	MoveWindow(HWNDconsole, r.left, r.top, width, hight, TRUE);
}


/////////////////// Window \\\\\\\\\\\\\\\

/*

Window::Window(int sizeX, int sizeY, Console* console, int screensizeX, int screensizeY) :
console(console),
screensizeX(screensizeX), 
screensizeY(screensizeY) {
	window_.create(sf::VideoMode(sizeX, sizeY), "Atventure Game");

	// init font
	if (!font.loadFromFile("Resurces//arial.ttf")) {
		throw 1;
	}
	sf::Text TestText("Test", font, 20);
	window_.draw(TestText);
	window_.display();
}

Window::~Window() {
}

bool Window::handleEvents() {
	if (window_.pollEvent(event_)) { // new event
		switch (event_.type) { // handle different events
		case sf::Event::Closed:
			window_.close();
			break;

		case sf::Event::Resized:
			std::wcout << L"resized" << std::endl;
			//sf::FloatRect visibleArea(0, 0, event_.size.width, event_.size.height);
			view.setSize(event_.size.width, event_.size.height);
			window_.setView(sf::View(sf::FloatRect(0, 0, event_.size.width, event_.size.height)));
			//sf::Vector2u tmpVec(event_.size.width, event_.size.height);
			//window_->setSize(sf::Vector2u(event_.size.width, event_.size.height));
			clearscreen();
			render();
			break;

			// key pressed
		case sf::Event::KeyPressed:
			keyData.alt = event_.key.alt;
			keyData.shift = event_.key.shift;
			keyData.control = event_.key.control;
			keyData.key = sf::Keyboard::localize(event_.key.scancode);
			return true;
				break;
		default:
			break;
		}
	}
	return false;
}

KeyEventData* Window::getKeyAction() {
	return &keyData;
}

void Window::render() {
	for (size_t i = Window::screensizeX - 1; i > 0; i--) {
		for (size_t t = Window::screensizeY - 1; t > 0; t--) {
			if (Window::console->getChar(i, t) == L" " && Window::console->getColor(i, t) == 0x07) {
				console->Plot(i, t, L"}");
			}
			else break;
		}
	}

	int lastTval = 0;

	for (size_t i = 0; i < Window::screensizeX; i++) {
		for (size_t t = 0; t < Window::screensizeY; t++) 
			if (!((Window::console->getChar(i, t) == L"}") && Window::console->getColor(i, t) == 0x07)) {
				//TODO: add color
				sf::Text drawText(Window::console->getChar(i, t), font, 20);
				drawText.setPosition((drawText.getLetterSpacing() + 20) * t, (drawText.getLineSpacing() + 20) * i);
				window_.draw(drawText);
				//ScreenBuffer += Window::console->getChar(i, t);
			}
		}
		//sf::Text drawText(L"\n", font, 20);
		//drawText.setPosition(drawText.getLetterSpacing() * t, drawText.getLineSpacing() * i);
		//window_.draw(drawText);
	}
	//sf::Text drawText(ScreenBuffer, font, 20);
	//window_.draw(drawText);
	window_.display();
	return;
}

void Window::clearscreen() {
	window_.clear();
}*/