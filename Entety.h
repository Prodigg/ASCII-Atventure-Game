#pragma once
#include "ItemClass.h"
#include "Engine.h"

#define CHEST_X_SIZE 4
#define CHEST_Y_SIZE 4
#define CHEST_WORLD_COUNT 2

class WorldObject {
public:
	void setPosition(int x, int y);
	int getxPosition();
	int getyPosition();
	int getObjectID();
	void setBlocking(bool blocking);
	bool isBlocking();

	WorldObject(int ObjectID, int x, int y, bool blocking);

private:
	int xPosition = 0;
	int yPosition = 0;
	int _ObjectID = 0;
	bool Blocking = true;
};

class WorldObjectChest : public WorldObject {
public:
	WorldObjectChest(int x, int y);
	WorldObjectChest();
	ItemClass getItem(int Pos);
	void putItem(int Pos, ItemClass Item);
	void PrintInventory(Console* console);
private:
	ItemClass ItemList[16];

	//std::list<ItemClass> Item;
};

class WorldEntetymanager {
public:
	WorldEntetymanager();
	int getEntety(int x, int y);
	~WorldEntetymanager();
	bool isEntetyBlocking(int x, int y);
	WorldObjectChest* getChest(int x, int y);
private:
	WorldObjectChest ChestArray[CHEST_WORLD_COUNT];
};


