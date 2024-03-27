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
//#include "Engine.h"
#include "TextBox.h"

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

void defultSFfunc() {};

bool ActionAvalable(int x, int y, int i) {
	if (i == 3 && (GlobalWorld.isBlocking(x + 1, y) == true || MainCaracter.getIsChestOpen() || MainCaracter.getIsInventoryOpen() || MainCaracter.getIsDialogeActive())) { //is Wall to the right
		return false;
	}

	if (i == 4 && (GlobalWorld.isBlocking(x - 1, y) == true || MainCaracter.getIsChestOpen() || MainCaracter.getIsInventoryOpen() || MainCaracter.getIsDialogeActive())) { //is Wall to the left
		return false;
	}

	if (i == 5 && (GlobalWorld.isBlocking(x, y + 1) == true || MainCaracter.getIsChestOpen() || MainCaracter.getIsInventoryOpen() || MainCaracter.getIsDialogeActive())) { //is Wall down
		return false;
	}

	if (i == 6 && (GlobalWorld.isBlocking(x, y - 1) == true || MainCaracter.getIsChestOpen() || MainCaracter.getIsInventoryOpen() || MainCaracter.getIsDialogeActive())) { //is Wall above
		return false;
	}

	if (i == 7 && (!(MainCaracter.serchInteractableObject(x, y, &GlobalWorld) == 2) || MainCaracter.getIsChestOpen() == true || MainCaracter.getIsInventoryOpen())) { // nothing to interact with
		return false;
	}

	if (i == 8 && !(MainCaracter.getIsChestOpen() || MainCaracter.getIsDialogeActive())) { // not a chest to return from
		return false;
	}

	if (i == 9 && (MainCaracter.getIsChestOpen() || MainCaracter.getIsInventoryOpen() || MainCaracter.getIsDialogeActive())) { // inventory or other container open
		return false;
	}

	if (i == 10 && !MainCaracter.getIsInventoryOpen()) { // no inventory to return from
		return false;
	}

	if (i == 11 && !MainCaracter.getIsChestOpen()) { // no Inv to Switch
		return false;
	}
	if (i == 12 && (!(MainCaracter.getIsChestOpen() || MainCaracter.getIsInventoryOpen()) || MainCaracter.isItemInHandExistant())) { // pickup item
		return false;
	}
	if (i == 13 && (!(MainCaracter.getIsChestOpen() || MainCaracter.getIsInventoryOpen()) || !MainCaracter.isItemInHandExistant())) { // drop Item
		return false;
	}
	if (i == 14 && (!(MainCaracter.getIsChestOpen() || MainCaracter.getIsInventoryOpen()))) { // drop Item on floor
		return false;
	}
	if (i == 15 && (MainCaracter.getIsChestOpen() || MainCaracter.getIsInventoryOpen() || !(GlobalWorld.EntetyMgr.getEntety(MainCaracter.getX(), MainCaracter.getY()) == 4))) { // pickup Item from floor
		return false;
	}

	return true;
}

void drawMenu(int x, int y) {
	int t = 0;
	for (int i = 0; i < 17; i++) {
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

int TestFormate[] = {
	TEXT_HEAD,
	TEXT_BODY,
	TEXT_BODY,
	TEXT_SEPERATOR,
	TEXT_BODY,
	TEXT_END
};

WorldObjectChest* activeChest;

std::vector<std::vector<std::wstring>> TestNPCText = {
	{
		L"Hallo, ich heisse Test.",
		L"Ich bin ein test NPC.",
		L"Wie geht es dir?"
	},
	{
		L"das ist schön zuhören"
	},
	{
		L"schade"
	}
};

void spezalTestFunction() {
	std::cout << "Test";
}

std::vector<std::vector<Option>> TestNPCOptions = {
	{
		{L"gut", 1},
		{L"schlecht", 2}
	}, 
	{},
	{}
};

//DialogeBox TextDialoge(TestMainText, TestOptions);
//std::vector<ItemClass> tmpInv;

int main() {
	char menu = ' ';
	int x;
	int y;
	ItemClass TesttmpItem;
	TesttmpItem.SetItem(-1, L"O");
	ItemOnFloor* TestItemOnFloor = new ItemOnFloor(16, 10, TesttmpItem, GlobalWorld.getEntetyMgr());
	
	NPC TestNPC(14, 10, 0, 30, TestNPCText, TestNPCOptions, GlobalWorld.getEntetyMgr());

	ItemClass tmpItem;

	WorldObjectChest* TestChest1 = new WorldObjectChest(10, 10, GlobalWorld.getEntetyMgr());
	tmpItem.SetItem(-1, L"#");
	TestChest1->putItem(2, tmpItem);

	WorldObjectChest* TestChest2 = new WorldObjectChest(12, 10, GlobalWorld.getEntetyMgr());
	tmpItem.SetItem(-1, L"@");
	TestChest2->putItem(2, tmpItem);

	tmpItem.SetItem(-1, L"P");
	TestChest2->putItem(4, tmpItem);


	while (true) {
		x = MainCaracter.getX();
		y = MainCaracter.getY();

		//TextDialoge.display(0, 30, &MainConsole);

		GlobalWorld.drawWorld(x, y, 0, 0);
		drawMenu(x, y);
		MainTerminal.print();

		menu = MainTerminal.getKeyAction();
		MainConsole.Clear();
		MainConsole.ClearColor();
		MainTerminal.clear();

		if (!MainCaracter.getIsChestOpen() && !MainCaracter.getIsInventoryOpen() && !MainCaracter.getIsDialogeActive()) {
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
					if (MainCaracter.getIsChestOpen()) { // chest
						MainCaracter.setIsCursorInInventory(false);
						MainCaracter.getActiveChest()->setIsCursorInChest(true);
						MainCaracter.getActiveChest()->PrintInventory(&MainConsole, 0, 17);
						MainCaracter.PrintInventory(&MainConsole, 20, 17);
					}
					else if (MainCaracter.getIsDialogeActive()) { // NPC
						MainCaracter.getActiveNPC()->display(0, 17, &MainConsole);
					}
				} else showMsgBox(0);
				break;
			case 'i': // invantory
				if (MainCaracter.openInventory()) {
					MainCaracter.PrintInventory(&MainConsole, 0, 20);
					MainCaracter.setIsCursorInInventory(true);
				}
				break;
			case 'r': // pickup Item
				MainCaracter.pickupItem(&GlobalWorld.EntetyMgr);
				break;
			default:
				showMsgBox(0);
				break;
			}
		} 
		
		else if (MainCaracter.getIsChestOpen()) {
			activeChest = MainCaracter.getActiveChest();
			switch (menu) {
			case 'f':
				MainCaracter.setIsCursorInInventory(false);
				activeChest->setIsCursorInChest(true);
				MainCaracter.endInteract();
				//MainConsole.Clear();
				//MainTerminal.clear();
				break;
			case 'w':
				if (MainCaracter.getIsCursorInInventory()) MainCaracter.movecusor(GO_UP);
				else activeChest->movecusor(GO_UP);
				break;
			case 'a':
				if (MainCaracter.getIsCursorInInventory()) MainCaracter.movecusor(GO_LEFT);
				else activeChest->movecusor(GO_LEFT);
				break;
			case 's':
				if (MainCaracter.getIsCursorInInventory()) MainCaracter.movecusor(GO_DOWN);
				else activeChest->movecusor(GO_DOWN);
				break;
			case 'd':
				if (MainCaracter.getIsCursorInInventory()) MainCaracter.movecusor(GO_RIGHT);
				else activeChest->movecusor(GO_RIGHT);
				break;
			case 'e':	// put Item In hand / set item out of hand
				MainCaracter.MoveItem();
				break;
			case 'q':
				if (MainCaracter.getIsCursorInInventory()) {
					MainCaracter.setIsCursorInInventory(false);
					activeChest->setIsCursorInChest(true);
				}
				else {
					MainCaracter.setIsCursorInInventory(true);
					activeChest->setIsCursorInChest(false);
				}
				
				break;
			case 'r': // pickup / drop Item
				//if(GlobalWorld.EntetyMgr.getItem(MainCaracter.getX(), MainCaracter.getY()))
				MainCaracter.dropItem(&GlobalWorld.EntetyMgr);
				break;
			default:
				showMsgBox(0);
				break;
			}

			if (MainCaracter.getIsChestOpen()) { 
				MainCaracter.getActiveChest()->PrintInventory(&MainConsole, 0, 17);
				MainCaracter.PrintInventory(&MainConsole, 20, 17);
			}
		}


		else if (MainCaracter.getIsInventoryOpen()) {
			ItemClass* testItem = new ItemClass;
			switch (menu) {
			case 'i':
				MainCaracter.closeInventory();
				MainCaracter.setIsCursorInInventory(false);
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
			case 'r': // pickup / drop Item
				MainCaracter.dropItem(&GlobalWorld.EntetyMgr);
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

		else if (MainCaracter.getIsDialogeActive()) {
			switch (menu) {
			case '1':
				MainCaracter.getActiveNPC()->optionSelected(1);
				break;
			case '2':
				MainCaracter.getActiveNPC()->optionSelected(2);
				break;
			case '3':
				MainCaracter.getActiveNPC()->optionSelected(3);
				break;
			case '4':
				MainCaracter.getActiveNPC()->optionSelected(4);
				break;
			case '5':
				MainCaracter.getActiveNPC()->optionSelected(5);
				break;
			case '6':
				MainCaracter.getActiveNPC()->optionSelected(6);
				break;
			case '7':
				MainCaracter.getActiveNPC()->optionSelected(7);
				break;
			case '8':
				MainCaracter.getActiveNPC()->optionSelected(8);
				break;
			case '9':
				MainCaracter.getActiveNPC()->optionSelected(9);
				break;
			case 'f':
				MainCaracter.endInteract();
				break;
			default:
				showMsgBox(0);
				break;
			}

			if (MainCaracter.getIsDialogeActive()) {
				MainCaracter.getActiveNPC()->display(0, 17, &MainConsole);
			}
		}
	}
}