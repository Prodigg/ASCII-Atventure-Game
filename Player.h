#pragma once
#include "World.h"

#define xSrartPosition 5
#define ySrartPosition 5

enum Directions {
	GO_RIGHT = 0,
	GO_LEFT = 1,
	GO_DOWN = 2,
	GO_UP = 3
};


class InventoryClass
{
public:
	InventoryClass();
	void setInventoryItem(ItemClass* Item, int index);
	ItemClass* getInventoryItem(int index);
	void removeInventoryItem(int Index);
	void ClearInventory();
	bool openInventory();
	void closeInventory();
	bool getIsInventoryOpen();
	void PrintInventory(Console* console, int x, int y);
	bool isInventoryItemExistant(int Index);

	void setEquipment(ItemClass* Item, int Index);
	ItemClass* getEquipment(int Index);

	bool highliteInvSpace(int Index, Console* console, int InvPos_x, int InvPos_y);

	bool setInventoryCursor(int x, int y);
	bool setInventoryCursor(int Index);
	bool movecusor(int direction);

	bool setItemInHand(ItemClass* Item);
	bool deleteItemInHand();
	bool isItemInHandExistant();
private:
	ItemClass inventoryList[16];

	/*
	* 0: weapon
	* 1: Armor
	* 2: Ring
	* 3: Misc
	*/
	ItemClass EquipList[4];

	ItemClass ItemInHand;

	bool isInventoryOpen = false;
	int InvCursorX = 0;
	int InvCursorY = 0;

	int InvCursorIndex = 0;

	int calculateInvIndex(int x, int y);
};


class Player : public InventoryClass {
public:
	Player();
	bool moveTo(int x, int y, WorldClass* _World);
	bool go(int direction, WorldClass* _World);
	int getX();
	int getY();
	bool interact(WorldClass* World);
	void endInteract();
	bool getIsChestOpen();
	WorldObjectChest* getActiveChest();
	int serchInteractableObject(int x, int y, WorldClass* _World);

private:
	int xPosition = xSrartPosition;
	int yPosition = ySrartPosition;


	WorldObjectChest* getChest(int x, int y, WorldClass* _World);

	WorldObjectChest* ActiveChest;
	bool isChestOpen = false;
	
};
