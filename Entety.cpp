#include "Entety.h"
#include "ItemClass.h"

#include <string>
#include <iostream>
////////// World Object \\\\\\\\\\\\\\\\

void WorldObject::setPosition(int x, int y) {
	WorldObject::xPosition = x;
	WorldObject::yPosition = y;
}

int WorldObject::getxPosition() {
	return WorldObject::xPosition;
}

int WorldObject::getyPosition() {
	return WorldObject::yPosition;
}

WorldObject::WorldObject(int ObjectID, int x, int y, bool blocking) : _ObjectID(ObjectID), xPosition(x), yPosition(y), Blocking(blocking) {};

int WorldObject::getObjectID() {
	return WorldObject::_ObjectID;
}

void WorldObject::setBlocking(bool blocking) {
	WorldObject::Blocking = blocking;
}

bool WorldObject::isBlocking() {
	return WorldObject::Blocking;
}

/////////// World Object Chest \\\\\\\\\\\\\\\\

WorldObjectChest::WorldObjectChest(int x, int y) : WorldObject(2, x, y, true) {
	ItemClass newItem;
	newItem.SetItem(0, L" ");
	for (size_t i = 0; i < 16; i++) {
		WorldObjectChest::ItemList[i] = newItem;
	}
};

WorldObjectChest::WorldObjectChest() : WorldObject(2, 0, 0, true){
	ItemClass newItem;
	newItem.SetItem(0, L" ");
	for (size_t i = 0; i < 16; i++) {
		WorldObjectChest::ItemList[i] = newItem;
	}
};

ItemClass WorldObjectChest::getItem(int Pos) {
	return WorldObjectChest::ItemList[Pos];
}

void WorldObjectChest::putItem(int Pos, ItemClass Item) {
	WorldObjectChest::ItemList[Pos] = Item;
	return;
}


std::wstring ChestUI[10]{
L"      Chest      ",
L"┌───┬───┬───┬───┐",
L"│   │   │   │   │",
L"├───┼───┼───┼───┤",
L"│   │   │   │   │",
L"├───┼───┼───┼───┤",
L"│   │   │   │   │",
L"├───┼───┼───┼───┤",
L"│   │   │   │   │",
L"└───┴───┴───┴───┘",
};

void WorldObjectChest::PrintInventory(Console* console, int x, int y) {
	std::wstring tmpChest[10];
	for (size_t i = 0; i < 10; i++) {
		tmpChest[i] = ChestUI[i];
	}
	int ListPtr = 0;
	for (size_t i = 0; i < 4; i++) {
		for (size_t t = 0; t < 4; t++) {
			tmpChest[2 + (i * 2)].replace(2 + (t * 4), 1, ItemList[ListPtr].getIcon());
			ListPtr++;
		}
	}
	for (int i = 0; i < 10; i++) {
		console->Plot(y + i, x + 0, tmpChest[i]);
	}

	if (isCursorInChest) {
		highliteInvSpace(getInventoryCursor(), console);
	}

}


///////////// WorldEntetymanager \\\\\\\\\\\\\\\\

WorldEntetymanager::WorldEntetymanager() {
	ItemClass tmpItem;
	WorldObjectChest tmpChest(0, 0);

	WorldEntetymanager::ChestArray[0] = tmpChest;
	WorldEntetymanager::ChestArray[0].setPosition(10, 10);

	tmpItem.SetItem(-1, L"#");
	WorldEntetymanager::ChestArray[0].putItem(2, tmpItem);


	WorldEntetymanager::ChestArray[1] = tmpChest;
	WorldEntetymanager::ChestArray[1].setPosition(12, 10);

	tmpItem.SetItem(-1, L"@");
	WorldEntetymanager::ChestArray[1].putItem(2, tmpItem);

	tmpItem.SetItem(-1, L"P");
	WorldEntetymanager::ChestArray[1].putItem(4, tmpItem);
	//delete &tmpItem;
}

WorldEntetymanager::~WorldEntetymanager() {
}

int WorldEntetymanager::getEntety(int x, int y) {
	int xObject = 0;
	int yObject = 0;
	for (size_t i = 0; i < CHEST_WORLD_COUNT; i++) {
		xObject = WorldEntetymanager::ChestArray[i].getxPosition();
		yObject = WorldEntetymanager::ChestArray[i].getyPosition();
		if (xObject == x && yObject == y) {
			return WorldEntetymanager::ChestArray[i].getObjectID();
		}
	}
	return -1;
}


bool WorldEntetymanager::isEntetyBlocking(int x, int y) {
	int xObject = 0;
	int yObject = 0;
	for (size_t i = 0; i < CHEST_WORLD_COUNT; i++) {
		xObject = WorldEntetymanager::ChestArray[i].getxPosition();
		yObject = WorldEntetymanager::ChestArray[i].getyPosition();
		if (xObject == x && yObject == y) {
			return WorldEntetymanager::ChestArray[i].isBlocking();
		}
	}
	return false;
}

WorldObjectChest* WorldEntetymanager::getChest(int x, int y) {
	int xObject = 0;
	int yObject = 0;
	for (size_t i = 0; i < CHEST_WORLD_COUNT; i++) {
		xObject = WorldEntetymanager::ChestArray[i].getxPosition();
		yObject = WorldEntetymanager::ChestArray[i].getyPosition();
		if (xObject == x && yObject == y) {
			return &WorldEntetymanager::ChestArray[i];
		}
	}
	return NULL;
}