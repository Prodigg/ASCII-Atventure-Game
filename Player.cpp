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

std::wstring InventoryPickup[3]{
	L"┌───┐",
	L"│   │",
	L"└───┘"
};

Player::Player() {
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
	// chest
	if (_World->EntetyMgr.getEntety(x + 1, y) == 2) return 2;
	if (_World->EntetyMgr.getEntety(x - 1, y) == 2) return 2;
	if (_World->EntetyMgr.getEntety(x, y + 1) == 2) return 2;
	if (_World->EntetyMgr.getEntety(x, y - 1) == 2) return 2;

	if (_World->EntetyMgr.getEntety(x + 1, y) == 3) return 3;
	if (_World->EntetyMgr.getEntety(x - 1, y) == 3) return 3;
	if (_World->EntetyMgr.getEntety(x, y + 1) == 3) return 3;
	if (_World->EntetyMgr.getEntety(x, y - 1) == 3) return 3;
	return -2;
}

WorldObjectChest* Player::getChest(int x, int y, WorldClass* _World) {
	if (_World->EntetyMgr.getEntety(x + 1, y) == 2) return static_cast<WorldObjectChest*>(_World->EntetyMgr.getChest(x + 1, y));
	if (_World->EntetyMgr.getEntety(x - 1, y) == 2) return static_cast<WorldObjectChest*>(_World->EntetyMgr.getChest(x - 1, y));
	if (_World->EntetyMgr.getEntety(x, y + 1) == 2) return static_cast<WorldObjectChest*>(_World->EntetyMgr.getChest(x, y + 1));
	if (_World->EntetyMgr.getEntety(x, y - 1) == 2) return static_cast<WorldObjectChest*>(_World->EntetyMgr.getChest(x, y - 1));
	return NULL;
}

NPC* Player::getNPC(int x, int y, WorldClass* _World) {
	if (_World->EntetyMgr.getEntety(x + 1, y) == 3) return static_cast<NPC*>(_World->EntetyMgr.getNPC(x + 1, y));
	if (_World->EntetyMgr.getEntety(x - 1, y) == 3) return static_cast<NPC*>(_World->EntetyMgr.getNPC(x - 1, y));
	if (_World->EntetyMgr.getEntety(x, y + 1) == 3) return static_cast<NPC*>(_World->EntetyMgr.getNPC(x, y + 1));
	if (_World->EntetyMgr.getEntety(x, y - 1) == 3) return static_cast<NPC*>(_World->EntetyMgr.getNPC(x, y - 1));
	return NULL;
}

bool Player::interact(WorldClass* World) {
	if (getIsInventoryOpen()) return false;

	if (serchInteractableObject(xPosition, yPosition, World) == 2) { // chest found in radius
		Player::ActiveChest = Player::getChest(xPosition, yPosition, World); // query for chest in radius
		isChestOpen = true;
		return true;
	}

	if (serchInteractableObject(xPosition, yPosition, World) == 3) { // NPC found in radius
		Player::ActiveNPC = Player::getNPC(xPosition, yPosition, World); // query for chest in radius
		isDialogeActive = true;
		return true;
	}
	return false;
}

void Player::endInteract() {
	if (isChestOpen) {
		isChestOpen = false;
		if (isItemInHandExistant()) {
			if (getIsCursorInInventory()) {
				setInventoryItem(getItemInHand(), getPrevItemPos());
				deleteItemInHand();
				return;
			}
			getActiveChest()->putItem(getPrevItemPos(), *getItemInHand());
			deleteItemInHand();
			return;
		}
	}
	if (isDialogeActive) {
		ActiveNPC->setPage(0); // set defult page
		isDialogeActive = false;
	}
}

bool Player::getIsChestOpen() {
	return isChestOpen;
}

WorldObjectChest* Player::getActiveChest() {
	return ActiveChest;
}

void Player::MoveItem() {
	if (this->getIsCursorInInventory()) {
		if (this->isItemInHandExistant()) { // put Item out of hand
			if (!this->isInventoryItemExistant(this->getInventoryCursor())) {
				this->setInventoryItem(this->getItemInHand(), this->getInventoryCursor());
				this->deleteItemInHand();
			}
		}
		else { // put Item in Hand
			this->setItemInHand(this->getInventoryItem(this->getInventoryCursor()));
			this->removeInventoryItem(this->getInventoryCursor());
		}
	}
	else {
		if (this->isItemInHandExistant()) { // put Item out of hand
		
			if (!ActiveChest->isItemExistant(ActiveChest->getInventoryCursor())) {
				ActiveChest->putItem(ActiveChest->getInventoryCursor(), *this->getItemInHand());
				this->deleteItemInHand();
			}
		}
		else { // put Item in Hand
			this->setItemInHand(ActiveChest->getItem(ActiveChest->getInventoryCursor()));
			this->setPrevInvPos(ActiveChest->getInventoryCursor());
			ActiveChest->removeItem(ActiveChest->getInventoryCursor());
		}
	}
	return;
}

bool Player::getIsDialogeActive() {
	return isDialogeActive;
}

NPC* Player::getActiveNPC() {
	return ActiveNPC;
}

bool Player::pickupItem(WorldEntetymanager* EntetyMgr) {
	if (EntetyMgr->getEntety(xPosition, yPosition) != 4) return false; // no item on floor
	// check for first free slot
	int freeInvSlot = -1;
	for (size_t i = 0; i < 16; i++) {
		if (!Player::isInventoryItemExistant(i)) {
			freeInvSlot = i;
			break;
		}
	}
	// no free slot avalable
	if (freeInvSlot == -1) return false;
	// get ItemOnFloor and put in Inv
	ItemOnFloor* tmpItemOnFloorPtr = static_cast<ItemOnFloor*>(EntetyMgr->getItem(Player::xPosition, Player::yPosition));
	Player::setInventoryItem(tmpItemOnFloorPtr->getItem(), freeInvSlot);
	

	// delete Item on ground
	delete static_cast<ItemOnFloor*>(EntetyMgr->getItem(Player::xPosition, Player::yPosition));

	return true;
}

bool Player::dropItem(WorldEntetymanager* EntetyMgr) {
	if (!(getIsInventoryOpen() || getIsChestOpen())) return false; // no inv or chest is open
	if (EntetyMgr->getEntety(xPosition, yPosition) != -1) return false; // entety already ocupying space

	// retrive Item from Container
	ItemClass TmpItem;
	if (getIsChestOpen()) { // for chests
		if (getIsCursorInInventory()) {
			TmpItem = *getInventoryItem(getInventoryCursor()); // from Inv
			removeInventoryItem(getInventoryCursor());
		}
		else {
			TmpItem = getActiveChest()->getItem(getActiveChest()->getInventoryCursor()); // from chest
			getActiveChest()->removeItem(getActiveChest()->getInventoryCursor());
		}
	}
	else if (getIsInventoryOpen()) { // for inventory
			TmpItem = *getInventoryItem(getInventoryCursor());
			removeInventoryItem(getInventoryCursor());
	}

	// set Item on floor
	ItemOnFloor* NewItemOnFloor = static_cast<ItemOnFloor*>(malloc(sizeof ItemOnFloor));
	NewItemOnFloor = new ItemOnFloor(xPosition, yPosition, TmpItem, EntetyMgr);
	// don't delete floor Item until Item is picked up

	
}

///////////////////// Inventory \\\\\\\\\\\\\\\\\\\\


InventoryClass::InventoryClass() {
	ItemClass* tmpItem = new ItemClass();
	tmpItem->SetItem(0, L" ");
	for (size_t i = 0; i < 16; i++) { // init Inventory
		inventoryList[i] = *tmpItem;
	}

	for (size_t i = 0; i < 4; i++) { // init Eqipment
		EquipList[i] = *tmpItem;
	}

	ItemInHand = *tmpItem;

	delete tmpItem;
}

bool InventoryClass::openInventory() {
	if (!(isInventoryOpen)) {
		setParameters(0, 0, 0);
		isInventoryOpen = true;
		return true;
	}
	return false;
}

bool InventoryClass::getIsInventoryOpen() {
	return isInventoryOpen;
}

void InventoryClass::closeInventory() {
	isInventoryOpen = false;
	if (isItemInHandExistant()) {
		setInventoryItem(getItemInHand(), getPrevItemPos());
		deleteItemInHand();
	}
}

void InventoryClass::PrintInventory(Console* console, int x, int y) {
	std::wstring tmpInventory[10];
	std::wstring tmpHand[3];
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
		console->Plot(y + i, x + 0, tmpInventory[i]);
	}

	for (size_t i = 0; i < 3; i++) {
		tmpHand[i] = InventoryPickup[i];
	}
	tmpHand[1].replace(2, 1, ItemInHand.getIcon());

	for (size_t i = 0; i < 3; i++) {
		console->Plot(y + 10 + i, x, tmpHand[i]);
	}

	if (isCursorInInventory) {
		highliteInvSpace(getInventoryCursor(), console, x, y);
	}

	return;
}

void InventoryClass::setInventoryItem(ItemClass* Item, int index) {
	inventoryList[index] = *Item;
}

ItemClass* InventoryClass::getInventoryItem(int index) {
	return &inventoryList[index];
}

void InventoryClass::ClearInventory() {
	ItemClass* voidItem = new ItemClass;
	voidItem->SetItem(0, L" ");

	for (size_t i = 0; i < 16; i++) {
		inventoryList[i] = *voidItem;
	}
	delete voidItem;
}

void InventoryClass::setEquipment(ItemClass* Item, int Index) {
	EquipList[Index] = *Item;
}

ItemClass* InventoryClass::getEquipment(int Index) {
	return &EquipList[Index];
}

void InventoryClass::removeInventoryItem(int Index) {
	ItemClass* voidItem = new ItemClass;
	voidItem->SetItem(0, L" ");
	inventoryList[Index] = *voidItem;
	delete voidItem;
}

bool InventoryClass::setItemInHand(ItemClass* Item) {
	ItemClass* voidItem = new ItemClass;
	voidItem->SetItem(0, L" ");
	if (ItemInHand == *voidItem) {
		delete voidItem;
		if (getIsCursorInInventory()) {
			prevItemPos = getInventoryCursor();
		}
		ItemInHand = *Item;
		return true;
	}
	delete voidItem;
	return false;
}

bool InventoryClass::setItemInHand(ItemClass Item) {
	return setItemInHand(&Item);
}

void InventoryClass::setPrevInvPos(int val) {
	prevItemPos = val;
}

bool InventoryClass::deleteItemInHand() {
	ItemClass* voidItem = new ItemClass;
	voidItem->SetItem(0, L" ");
	if (ItemInHand == *voidItem) {
		delete voidItem;
		return false;
	}
	ItemInHand = *voidItem;
	delete voidItem;
	return true;
}

bool InventoryClass::isItemInHandExistant() {
	ItemClass* voidItem = new ItemClass;
	voidItem->SetItem(0, L" ");
	if (ItemInHand == *voidItem) {
		delete voidItem;
		return false;
	}
	delete voidItem;
	return true;
}

bool InventoryClass::isInventoryItemExistant(int Index) {
	ItemClass* voidItem = new ItemClass;
	voidItem->SetItem(0, L" ");
	if (inventoryList[Index] == *voidItem) {
		delete voidItem;
		return false;
	}
	delete voidItem;
	return true;
}

ItemClass* InventoryClass::getItemInHand() {
	return &ItemInHand;
}

bool InventoryClass::getIsCursorInInventory() {
	return isCursorInInventory;
}

void InventoryClass::setIsCursorInInventory(bool val) {
	isCursorInInventory = val;
	return;
}

int InventoryClass::getPrevItemPos() {
	return prevItemPos;
}

