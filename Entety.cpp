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


const std::wstring ChestUI[10]{
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
		highliteInvSpace(getInventoryCursor(), console, x, y);
	}

}

void WorldObjectChest::setIsCursorInChest(bool val) {
	isCursorInChest = val;
}

bool WorldObjectChest::getIsCursorInChest() {
	return isCursorInChest;
}

bool WorldObjectChest::isItemExistant(int Pos) {
	ItemClass* voidItem = new ItemClass;
	voidItem->SetItem(0, L" ");
	if (getItem(Pos) == *voidItem) {
		delete voidItem;
		return false;
	}
	delete voidItem;
	return true;
}

void WorldObjectChest::removeItem(int Pos) {
	ItemClass* voidItem = new ItemClass;
	voidItem->SetItem(0, L" ");
	putItem(Pos, *voidItem);
	delete voidItem;
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

	// search chest
	for (size_t i = 0; i < CHEST_WORLD_COUNT; i++) {
		xObject = WorldEntetymanager::ChestArray[i].getxPosition();
		yObject = WorldEntetymanager::ChestArray[i].getyPosition();
		if (xObject == x && yObject == y) {
			return WorldEntetymanager::ChestArray[i].getObjectID();
		}
	}
	// search NPC
	for (size_t i = 0; i < NPCPos.size(); i++) {
		if (NPCPos.at(i).x == x && NPCPos.at(i).y == y) {
			NPC* tmpNPCPointer = static_cast<NPC*> (NPCArray.at(i));
			return tmpNPCPointer->getObjectID();
		}
	}

	// search Item
	for (size_t i = 0; i < ItemOnFloorArray.size(); i++) {
		if (ItemOnFloorArray.at(i).x == x && ItemOnFloorArray.at(i).y == y) {
			ItemOnFloor* tmpItemOnFloorPointer = static_cast<ItemOnFloor*> (ItemOnFloorArray.at(i)._Item);
			return tmpItemOnFloorPointer->getObjectID();
		}
	}
	
	return -1;
}


bool WorldEntetymanager::isEntetyBlocking(int x, int y) {
	int xObject = 0;
	int yObject = 0;

	// Chest
	for (size_t i = 0; i < CHEST_WORLD_COUNT; i++) {
		xObject = WorldEntetymanager::ChestArray[i].getxPosition();
		yObject = WorldEntetymanager::ChestArray[i].getyPosition();
		if (xObject == x && yObject == y) {
			return WorldEntetymanager::ChestArray[i].isBlocking();
		}
	}

	// NPC
	for (size_t i = 0; i < NPCPos.size(); i++) {
		if (NPCPos.at(i).x == x && NPCPos.at(i).y == y) {
			NPC* tmpNPCPointer = static_cast<NPC*>(NPCArray.at(i));
			return tmpNPCPointer->isBlocking();
		}
	}

	// Item
	for (size_t i = 0; i < ItemOnFloorArray.size(); i++) {
		if (ItemOnFloorArray.at(i).x == x && ItemOnFloorArray.at(i).y == y) {
			ItemOnFloor* tmpItemOnFloorPointer = static_cast<ItemOnFloor*>(ItemOnFloorArray.at(i)._Item);
			return tmpItemOnFloorPointer->isBlocking();
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

int WorldEntetymanager::registerNPC(int x, int y, void* _NPC) {
	NPCArray.push_back(_NPC);
	posData* tmpPosData = new posData;
	tmpPosData->x = x;
	tmpPosData->y = y;
	NPCPos.push_back(*tmpPosData);
	delete tmpPosData;
	return NPCArray.size() - 1;
}

void WorldEntetymanager::unregisterNPC(int NPC_ID) {
	std::vector<void*>::iterator* NPCArrayIterator = new std::vector<void*>::iterator;
	*NPCArrayIterator = NPCArray.begin() + NPC_ID;
	NPCArray.erase(*NPCArrayIterator);
	delete NPCArrayIterator;
	
	std::vector<posData>::iterator* NPCPosArrayIterator = new std::vector<posData>::iterator;
	*NPCPosArrayIterator = NPCPos.begin() + NPC_ID;
	NPCPos.erase(*NPCPosArrayIterator);
	delete NPCPosArrayIterator;
}

void* WorldEntetymanager::getNPC(int x, int y) {
	for (size_t i = 0; i < NPCPos.size(); i++) {
		if (NPCPos.at(i).x == x && NPCPos.at(i).y == y) {
			return NPCArray.at(i);
		}
	}
	return NULL;
}

int WorldEntetymanager::registerItem(int x, int y, void* _Item) {
	ItemOnGroundData* ItemOnGroundtmpData = new ItemOnGroundData;
	ItemOnGroundtmpData->x = x;
	ItemOnGroundtmpData->y = y;
	int tmpItemID = 0;
	for (size_t i = 0; i < ItemOnFloorArray.size(); i++) {
		if (ItemOnFloorArray.at(i).ITEM_ID == tmpItemID) tmpItemID++;
	}

	ItemOnGroundtmpData->_Item = _Item;
	ItemOnGroundtmpData->ITEM_ID = tmpItemID;
	ItemOnFloorArray.push_back(*ItemOnGroundtmpData);
	delete ItemOnGroundtmpData;

	return tmpItemID;
}

void WorldEntetymanager::unregisterItem(int ITEM_ID) {
	int ItemInArray = -1;
	std::vector<ItemOnGroundData>::iterator* ItemArrayIterator = new std::vector<ItemOnGroundData>::iterator;
	for (size_t i = 0; i < ItemOnFloorArray.size(); i++) {
		if (ItemOnFloorArray.at(i).ITEM_ID == ITEM_ID) {
			ItemInArray = i;
			break;
		}
	}
	if (ItemInArray == -1) return;

	*ItemArrayIterator = ItemOnFloorArray.begin() + ItemInArray;
	ItemOnFloorArray.erase(*ItemArrayIterator);
	delete ItemArrayIterator;
	return;
}

void* WorldEntetymanager::getItem(int x, int y) {
	for (size_t i = 0; i < ItemOnFloorArray.size(); i++) {
		if(ItemOnFloorArray.at(i).x == x && ItemOnFloorArray.at(i).y == y) {
			return ItemOnFloorArray.at(i)._Item;
		}
	}
}

std::wstring WorldEntetymanager::getItemSprite(int x, int y) {
	ItemOnFloor* TmpItemPtr = static_cast<ItemOnFloor*>(getItem(x, y));
	return TmpItemPtr->getItem()->getIcon();
}

//////////////// NPC \\\\\\\\\\\\\\\\

enum NPCDialogActions {
	DO_NOTHING = 0,
	GIVE_ITEM = 1
};
enum NPCDialogActionsParameters {
	NO_PARAMETER = 0,
	ITEM_INVENTORY_ID = 1
};


NPC::NPC(int x, int y, int displayX, int displayY, std::vector<std::vector<std::wstring>> MainText, std::vector<std::vector<Option>> Options, WorldEntetymanager* WorldMgr, std::vector<ItemClass> Inventory) : 
WorldObject(3, x, y, true), 
DialogeBox(MainText, Options),
displayX(displayX),
displayY(displayY),
WordlMgr(WorldMgr),
Inventory(Inventory) {

	// register NPC in World Manager
	NPC_ID = WorldMgr->registerNPC(x, y, this);
}

NPC::~NPC() {
	NPC::WordlMgr->unregisterNPC(NPC_ID);
}


void NPC::optionSelected(int option) {
	int action = getOptions(getPage(), option)->action;
	int actionArgument = getOptions(getPage(), option)->actionPrameter;
	if (action == 1) { // drop Item on floor
		int ItemPos = -1;

		// find NPCItemInInventory
		for (size_t i = 0; i < Inventory.size(); i++) {
			if (Inventory.at(i).NPCItemID == actionArgument) {
				ItemPos = i;
				break;
			}
		}
		// check if Item was found 
		if (ItemPos == -1) return;

		// get Direction from actionParameter2
		int x = getxPosition();
		int y = getyPosition();
		int actionArgument2 = getOptions(getPage(), option)->actionPrameter2;
		if (actionArgument2 == 0) y = y - 1;
		else if (actionArgument2 == 1) y = y + 1;
		else if (actionArgument2 == 2) x = x + 1;
		else if (actionArgument2 == 3) x = x - 1;
		else return;

		// drop Item
		ItemOnFloor* NewItemOnFloor = static_cast<ItemOnFloor*>(malloc(sizeof ItemOnFloor));
		NewItemOnFloor = new ItemOnFloor(x, y, Inventory.at(ItemPos).Item, WordlMgr);
	}
}

////////////// ItemOnFloor \\\\\\\\\\\\\\\\

ItemOnFloor::ItemOnFloor(int x, int y, ItemClass Item, WorldEntetymanager* EntetyMgr) : 
	WorldObject(4, x, y, false), 
	Item(Item),
	EntetyMgr(EntetyMgr) {
	ITEM_ID = EntetyMgr->registerItem(x, y, this);
}

ItemOnFloor::~ItemOnFloor() {
	EntetyMgr->unregisterItem(ITEM_ID);
}

ItemClass* ItemOnFloor::getItem() {
	return &Item;
}