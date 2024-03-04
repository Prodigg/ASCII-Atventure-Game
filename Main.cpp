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
	if (i == 3 && (GlobalWorld.isBlocking(x + 1, y) == true || MainCaracter.getIsChestOpen() || MainCaracter.getIsInventoryOpen())) { //is Wall to the right
		return false;
	}

	if (i == 4 && (GlobalWorld.isBlocking(x - 1, y) == true || MainCaracter.getIsChestOpen() || MainCaracter.getIsInventoryOpen())) { //is Wall to the left
		return false;
	}

	if (i == 5 && (GlobalWorld.isBlocking(x, y + 1) == true || MainCaracter.getIsChestOpen() || MainCaracter.getIsInventoryOpen())) { //is Wall down
		return false;
	}

	if (i == 6 && (GlobalWorld.isBlocking(x, y - 1) == true || MainCaracter.getIsChestOpen() || MainCaracter.getIsInventoryOpen())) { //is Wall above
		return false;
	}

	if (i == 7 && (!(MainCaracter.serchInteractableObject(x, y, &GlobalWorld) == 2) || MainCaracter.getIsChestOpen() == true || MainCaracter.getIsInventoryOpen())) { // nothing to interact with
		return false;
	}

	if (i == 8 && !MainCaracter.getIsChestOpen()) { // not a chest to return from
		return false;
	}

	if (i == 9 && (MainCaracter.getIsChestOpen() || MainCaracter.getIsInventoryOpen())) { // inventory or other container open
		return false;
	}

	if (i == 10 && !MainCaracter.getIsInventoryOpen()) { // no inventory to return from
		return false;
	}

	return true;
}

void drawMenu(int x, int y) {
	int t = 0;
	for (int i = 0; i < 12; i++) {
		if (ActionAvalable(x, y, i) == true) {
			MainConsole.Plot(10 + t, 0, Menu[i]);
			t++;
		}
	}
	
}



void showMsgBox(int MsgID) { //must define Msg Box before
	for (int i = 0; i < 8; i++) {
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
		MainConsole.ClearColor();
		MainTerminal.clear();

		if (!MainCaracter.getIsChestOpen() && !MainCaracter.getIsInventoryOpen()) {
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
				if (MainCaracter.interact(&GlobalWorld)) {
					MainCaracter.getActiveChest()->PrintInventory(&MainConsole, 0, 17);
					MainCaracter.PrintInventory(&MainConsole, 20, 17);

				} else showMsgBox(0);
				break;
			case 'i': // invantory
				if (MainCaracter.openInventory()) {
					MainCaracter.PrintInventory(&MainConsole, 0, 20);
				}
				break;
			default:
				showMsgBox(0);
				break;
			}
		} 
		
		else if (MainCaracter.getIsChestOpen()) {

			switch (menu) {
			case 'f':
				MainCaracter.endInteract();
				//MainConsole.Clear();
				//MainTerminal.clear();
				break;
			case 'w':
				MainCaracter.movecusor(GO_UP);
				break;
			case 'a':
				MainCaracter.movecusor(GO_LEFT);
				break;
			case 's':
				MainCaracter.movecusor(GO_DOWN);
				break;
			case 'd':
				MainCaracter.movecusor(GO_RIGHT);
				break;
			case 'e':	// put Item In hand / set item out of hand
				if (MainCaracter.isItemInHandExistant()) { // put Item out of hand
					if (MainCaracter.isInventoryItemExistant(MainCaracter.getInventoryCursor())) {
						MainCaracter.setInventoryItem(MainCaracter.getInventoryItem(MainCaracter.getInventoryCursor()), MainCaracter.getInventoryCursor());
						MainCaracter.deleteItemInHand();
					}
				}
				else { // put Item in Hand
					MainCaracter.setItemInHand(MainCaracter.getInventoryItem(MainCaracter.getInventoryCursor()));
					MainCaracter.removeInventoryItem(MainCaracter.getInventoryCursor());
				}
				break;
			default:
				showMsgBox(0);
				break;
			}

			if (MainCaracter.getIsChestOpen()) { 
				MainCaracter.getActiveChest()->PrintInventory(&MainConsole, 0, 17);
				MainCaracter.PrintInventory(&MainConsole, 30, 17);
			}
		}


		else if (MainCaracter.getIsInventoryOpen()) {
			ItemClass* testItem = new ItemClass;
			switch (menu) {
			case 'i':
				MainCaracter.closeInventory();
				break;
			case 'w':
				MainCaracter.movecusor(GO_UP);
				break;
			case 'a':
				MainCaracter.movecusor(GO_LEFT);
				break;
			case 's':
				MainCaracter.movecusor(GO_DOWN);
				break;
			case 'd':
				MainCaracter.movecusor(GO_RIGHT);
				break;
			case 'e':	// put Item In hand / set item out of hand
				if (MainCaracter.isItemInHandExistant()) { // put Item out of hand
					if (!MainCaracter.isInventoryItemExistant(MainCaracter.getInventoryCursor())) {
						MainCaracter.setInventoryItem(MainCaracter.getItemInHand(), MainCaracter.getInventoryCursor());
						MainCaracter.deleteItemInHand();
					}
				}
				else { // put Item in Hand
					MainCaracter.setItemInHand(MainCaracter.getInventoryItem(MainCaracter.getInventoryCursor()));
					MainCaracter.removeInventoryItem(MainCaracter.getInventoryCursor());
				}
				break;
			case 'r':	// spawn test Item
				testItem->SetItem(-1, L"k");
				MainCaracter.setInventoryItem(testItem, 2);
				testItem->SetItem(-1, L"P");
				MainCaracter.setInventoryItem(testItem, 4);
				break;
			default:
				showMsgBox(0);
				break;
			}

			if (MainCaracter.getIsInventoryOpen()) {
				MainCaracter.PrintInventory(&MainConsole, 0, 20);
			}
			delete testItem;
		}
	}
}