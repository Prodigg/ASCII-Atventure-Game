#include "Player.h"

std::wstring Inventory[10]{
L"    Inventory    Equipment      ",
L"┌───┬───┬───┬───┐  ┌───┐        ",
L"│   │   │   │   │  │   │ weapon ",
L"├───┼───┼───┼───┤  ├───┤        ",
L"│   │   │   │   │  │   │ Armor  ",
L"├───┼───┼───┼───┤  ├───┤        ",
L"│   │   │   │   │  │   │ Ring   ",
L"├───┼───┼───┼───┤  ├───┤        ",
L"│   │   │   │   │  │   │ Misc.  ",
L"└───┴───┴───┴───┘  └───┘        ",
};

void Player::PrintInventory(Console* console) {
	std::wstring tmpInventory[10];
	for (size_t i = 0; i < 10; i++) { // int tmpInventory from template Inventory
		tmpInventory[i] = Inventory[i];
	}
	int ListPtr = 0;
	for (size_t i = 0; i < 4; i++) { // Items in Inventory
		for (size_t t = 0; t < 4; t++) {
			tmpInventory[2 + (i * 2)].replace(2 + (t * 4), 1, inventoryList[ListPtr].getIcon());
			ListPtr++;
		}
	}
	for (size_t i = 0; i < 4; i++) { // Eqipment
		tmpInventory[2 + (i * 2)].replace(21, 1, EquipList[i].getIcon());
	}

	for (size_t i = 0; i < 10; i++) { //push to textbuffer
		console->Plot(17 + i, 0, tmpInventory[i]);
	}
}

bool Player::moveTo(int x, int y, WorldClass* _World) {
	if (!(_World->getObject(x, y) == 1)) {
		Player::xPosition = x;
		Player::yPosition = y;
		return true;
	}
	return false;
}

bool Player::go(int direction, WorldClass* _World) {
	int tmpCordx = Player::xPosition;
	int tmpCordy = Player::yPosition;
	switch (direction) { // calculate new Position
	case 0: // right
		tmpCordx++;
		break;

	case 1: // left
		tmpCordx--;
		break;

	case 2: // down
		tmpCordy++;
		break;

	case 3: //up
		tmpCordy--;
		break;
	default:
		return false;
		break;
	}
	
	//if (_World.getObject(tmpCordx, tmpCordy) == 1) { // check for invalid positions due to objects
		//return false;
	//}
	if (_World->isBlocking(tmpCordx, tmpCordy) == true) { // check for invalid positions due to objects
		return false;
	}

	Player::xPosition = tmpCordx;
	Player::yPosition = tmpCordy;
	return true;
}

int Player::getX() {
	return Player::xPosition;
}

int Player::getY() {
	return Player::yPosition;
}

int Player::serchInteractableObject(int x, int y, WorldClass* _World) {
	if (_World->EntetyMgr.getEntety(x + 1, y) == 2) return 2;
	if (_World->EntetyMgr.getEntety(x - 1, y) == 2) return 2;
	if (_World->EntetyMgr.getEntety(x, y + 1) == 2) return 2;
	if (_World->EntetyMgr.getEntety(x, y - 1) == 2) return 2;
	return -2;
}

WorldObjectChest* Player::getChest(int x, int y, WorldClass* _World) {
	if (_World->EntetyMgr.getEntety(x + 1, y) == 2) return _World->EntetyMgr.getChest(x + 1, y);
	if (_World->EntetyMgr.getEntety(x - 1, y) == 2) return _World->EntetyMgr.getChest(x - 1, y);
	if (_World->EntetyMgr.getEntety(x, y + 1) == 2) return _World->EntetyMgr.getChest(x, y + 1);
	if (_World->EntetyMgr.getEntety(x, y - 1) == 2) return _World->EntetyMgr.getChest(x, y - 1);
	return NULL;
}

bool Player::interact(WorldClass* World) {
	if (serchInteractableObject(xPosition, yPosition, World) == 2) { // chest found in radius
		Player::ActiveChest = Player::getChest(xPosition, yPosition, World); // query for chest in radius
		isChestOpen = true;
		return true;
	}
	return false;
}

void Player::endInteract() {
	isChestOpen = false;
}

bool Player::getIsChestOpen() {
	return isChestOpen;
}

WorldObjectChest* Player::getActiveChest() {
	return ActiveChest;
}