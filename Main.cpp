#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <Windows.h>
#include <locale.h>
#include <wincon.h>
#include <conio.h>

#include "World.h"
#include "GlobalDefinitions.h"
#include "Player.h"
#include "Entety.h"
#include "Engine.h"

/* Windows CMD Colors
*		Zuertst backround, dann text color Bsp: text: red, backround yellow 0x6C
	0 = Schwarz       8 = Grau
    1 = Blau        9 = Hellblau
    2 = Grün       A = Hellgrün
    3 = Türkis        B = Helltürkis
    4 = Rot         C = Hellrot
    5 = Lila      D = Helllila
    6 = Gelb      E = Hellgelb
    7 = Hellgrau  F = Weiß
*/


bool ActionAvalable(int x, int y, int i) {
	if (i == 3 && GlobalWorld.isBlocking(x + 1, y) == true && MainCaracter.getIsChestOpen()) { //is Wall to the right
		return false;
	}

	if (i == 4 && GlobalWorld.isBlocking(x - 1, y) == true || MainCaracter.getIsChestOpen()) { //is Wall to the left
		return false;
	}

	if (i == 5 && GlobalWorld.isBlocking(x, y + 1) == true || MainCaracter.getIsChestOpen()) { //is Wall down
		return false;
	}

	if (i == 6 && GlobalWorld.isBlocking(x, y - 1) == true || MainCaracter.getIsChestOpen()) { //is Wall above
		return false;
	}

	if (i == 7 && (!(MainCaracter.serchInteractableObject(x, y, &GlobalWorld) == 2)) || MainCaracter.getIsChestOpen() == true) { // nothing to interact with
		return false;
	}

	if (i == 8 && !MainCaracter.getIsChestOpen()) { // not a chest to return from
		return false;
	}

	return true;
}

void drawMenu(int x, int y) {
	int t = 0;
	for (size_t i = 0; i < 10; i++) {
		if (ActionAvalable(x, y, i) == true) {
			MainConsole.Plot(10 + t, 0, Menu[i]);
			t++;
		}
	}
	
}



void showMsgBox(int MsgID) { //must define Msg Box before
	for (size_t i = 0; i < 8; i++) {
		MainConsole.Plot(27 + i, 0, MsgBox[MsgID][i], 0xC);
		//std::wcout << std::endl;
	}
}

int main() {
	char menu = ' ';
	int x;
	int y;

	while (true) {
		x = MainCaracter.getX();
		y = MainCaracter.getY();
		
		GlobalWorld.drawWorld(x, y, 0, 0);
		drawMenu(x, y);
		MainTerminal.print();

		menu = MainTerminal.getKeyAction();
		MainConsole.Clear();
		MainTerminal.clear();

		if (!MainCaracter.getIsChestOpen()) {
			switch (menu) {
			case 'd': // move right
				MainCaracter.go(GO_RIGHT, &GlobalWorld);
				break;
			case 'a': // move left
				MainCaracter.go(GO_LEFT, &GlobalWorld);
				break;
			case 's': // move down
				MainCaracter.go(GO_DOWN, &GlobalWorld);
				break;
			case 'w': // move up
				MainCaracter.go(GO_UP, &GlobalWorld);
				break;
			case 'f': // interact
				MainCaracter.interact(&GlobalWorld);
				MainCaracter.getActiveChest()->PrintInventory(&MainConsole);
				break;
			default:
				showMsgBox(0);
				break;
			}
		}
		else {

			switch (menu) {
			case 'f':
				MainCaracter.endInteract();
				MainConsole.Clear();
				MainTerminal.clear();
				break;
			default:
				showMsgBox(0);
				break;
			}
			if(MainCaracter.getIsChestOpen())	MainCaracter.getActiveChest()->PrintInventory(&MainConsole);
		}
	}
}