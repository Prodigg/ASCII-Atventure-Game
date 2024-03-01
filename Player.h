#pragma once
#include "World.h"

#define xSrartPosition 5
#define ySrartPosition 5

enum PlayerDirections {
	GO_RIGHT = 0,
	GO_LEFT = 1,
	GO_DOWN = 2,
	GO_UP = 3
};

class Player {
public:
	bool moveTo(int x, int y, WorldClass* _World);
	bool go(int direction, WorldClass* _World);
	int getX();
	int getY();
	bool interact(WorldClass* World);
	void endInteract();
	bool getIsChestOpen();
	WorldObjectChest* getActiveChest();
	int serchInteractableObject(int x, int y, WorldClass* _World);

	void PrintInventory(Console* console);
	
private:
	int xPosition = xSrartPosition;
	int yPosition = ySrartPosition;
	ItemClass inventoryList[16];
	/*
	* 0: weapon
	* 1: Armor
	* 2: Ring
	* 3: Misc
	*/
	ItemClass EquipList[4];


	WorldObjectChest* getChest(int x, int y, WorldClass* _World);

	WorldObjectChest* ActiveChest;
	bool isChestOpen = false;
	
};

