#pragma once
#ifndef __PLAYER__
#define __PLAYER__


#include "World.h"
#include "ContainerCursor.h"

#define xSrartPosition 5
#define ySrartPosition 5

enum Directions {
	GO_RIGHT = 0,
	GO_LEFT = 1,
	GO_DOWN = 2,
	GO_UP = 3
};


class InventoryClass : public ContainerCursor {
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

	bool setItemInHand(ItemClass* Item);
	bool setItemInHand(ItemClass Item);
	bool deleteItemInHand();
	bool isItemInHandExistant();
	ItemClass* getItemInHand();

	bool getIsCursorInInventory();
	void setIsCursorInInventory(bool val);
	int getPrevItemPos();
	void setPrevInvPos(int val);


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
	int prevItemPos = 0;
	bool isCursorInInventory = false;


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
	NPC* getActiveNPC();

	bool pickupItem(WorldEntetymanager* EntetyMgr); // in and out of inventory
	bool dropItem(WorldEntetymanager* EntetyMgr); // in inventory


	void MoveItem();

	bool getIsDialogeActive();
private:
	int xPosition = xSrartPosition;
	int yPosition = ySrartPosition;


	WorldObjectChest* getChest(int x, int y, WorldClass* _World);
	NPC* getNPC(int x, int y, WorldClass* _World);

	WorldObjectChest* ActiveChest;
	bool isChestOpen = false;
	
	bool isDialogeActive = false;

	NPC* ActiveNPC;
};


#endif // !__PLAYER__