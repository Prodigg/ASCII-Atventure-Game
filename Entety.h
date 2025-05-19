#pragma once
#ifndef __ENTETY__
#define __ENTETY__


#include "ItemClass.h"
#include "Engine.h"
#include "ContainerCursor.h"
#include "TextBox.h"
//#include "World.h"
//#include "Player.h"

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

	virtual void update() { /* Do nothing */ }

private:
	int xPosition = 0;
	int yPosition = 0;
	int _ObjectID = 0;
	bool Blocking = true;
};

enum NPCStates {
	NPC_IDLE = 0,
	NPC_DIALOGE = 1,
	NPC_WALKING = 2,
	NPC_DEAD = 3
};

struct AliveEntetyStats {
	int health;
	int damage;
	int armor;
};



struct posData {
	int x;
	int y;
};

struct ItemOnGroundData {
	int x; 
	int y;
	void* _Item;
	int ITEM_ID;
};

struct WorldEntetyData {
	int x;
	int y;
	int Entety_ID;
	int Entety_Type;
	void* EntetyPtr;
};

enum ENTETY_TYPES {
	ENTETY_CHEST = 2,
	ENTETY_NPC = 3,
	ENTETY_ITEM_ON_FLOOR = 4,
	ENTETY_HOSTILE_NPC = 5
};

class WorldEntetymanager {
public:
	WorldEntetymanager();
	int getEntety(int x, int y);
	~WorldEntetymanager();
	bool isEntetyBlocking(int x, int y);
	void* getChest(int x, int y);

	// returns ITEM_ID
	int registerItem(int x, int y, void* _Item);
	void unregisterItem(int ITEM_ID);
	void* getItem(int x, int y);
	std::wstring getItemSprite(int x, int y);

	// returns NPC_ID
	int registerNPC(int x, int y, void* _NPC);
	void unregisterNPC(int NPC_ID);
	void* getNPC(int x, int y);

	//********** New Entety System *********\\
	
	// returns EntetyID
	int registerEntety(int x, int y, int EntetyType, void* EntetyPtr);
	void unregisterEntety(int EntetyID);
	void* getEntetyPtr(int x, int y);

	void updateAllEntetys();

private:
	/*
	WorldObjectChest ChestArray[CHEST_WORLD_COUNT];
	std::vector<void*> NPCArray;
	std::vector<posData> NPCPos;
	std::vector<ItemOnGroundData> ItemOnFloorArray;
	*/
	std::vector<WorldEntetyData> EntetyDataArray;
};

struct NPCItemSaveData {
	ItemClass Item;
	int NPCItemID;

	NPCItemSaveData(const ItemClass& Item, int NPCItemID)
		: Item(Item), NPCItemID(NPCItemID)
	{}
};

class NPC : public WorldObject, public DialogeBox {
public:
	NPC(int x, int y, int displayX, int displayY, std::vector<std::vector<std::wstring>> MainText, std::vector<std::vector<Option>> Options, WorldEntetymanager* WorldMgr, std::vector<NPCItemSaveData> Inventory);
	NPC(int x, int y, int displayX, int displayY, std::vector<std::vector<std::wstring>> MainText, std::vector<std::vector<Option>> Options, WorldEntetymanager* WorldMgr);

	~NPC();
	void optionSelected(int option, void* player);
	bool checkForItem(int ItemID);
	int getNPCState();
	void setNPCState(int val);
	void updatePtr() {};

private:
	int lastMove = 0;
	int npcState = 0;
	int NPC_ID;

	int displayX;
	int displayY;

	AliveEntetyStats stats;
	WorldEntetymanager* WordlMgr;
	std::vector<NPCItemSaveData> Inventory;
};  

enum HOSTILE_NPC_STATES {
	HOSTILE_NPC_IDLE = 0,
	HOSTILE_NPC_ATTACKING = 1,
	HOSTILE_NPC_FLEE = 2
};

#define NPC_HOSTILE_RADIUS 2
/*
class HostileNPC : public WorldObject {
public:
	HostileNPC(int x, int y, WorldEntetymanager* EntetyMgr, WorldClass* World, Player* player, int HP, int Damage, int Armor, int chanceToHit);
	~HostileNPC();
	AliveEntetyStats* getStats();
	bool attacked(int damage);
	void damage(int damage);

	void setHostileNPCState(int state);
	int getHostileNPCState();

	bool move(int Direction);

	/*
	* is the Update function for this NPC
	* Checks if it is dead and moves NPC
	
	void update(int PotentialMove);
private:
	AliveEntetyStats stats;
	int ChanceToHit;

	int EntetyID;
	WorldEntetymanager* EntetyMgr;

	int HostileNPCState = 0;

	WorldClass* World;
	Player* player;

	int lastMove = 0;

};*/



class ItemOnFloor : public WorldObject {
public:
	ItemOnFloor(int x, int y, ItemClass Item, WorldEntetymanager* EntetyMgr);
	ItemClass* getItem();
	~ItemOnFloor();

private:
	int ITEM_ID;
	ItemClass Item;
	WorldEntetymanager* EntetyMgr;
};

class WorldObjectChest : public WorldObject, public ContainerCursor {
public:
	WorldObjectChest(int x, int y, WorldEntetymanager* EntetyMgr, ItemClass* _ItemList[16]);
	WorldObjectChest(int x, int y, WorldEntetymanager* EntetyMgr);
	WorldObjectChest();
	~WorldObjectChest();

	ItemClass getItem(int Pos);
	void putItem(int Pos, ItemClass Item);
	void PrintInventory(Console* console, int x, int y);
	bool isItemExistant(int Pos);
	void removeItem(int Pos);

	void setIsCursorInChest(bool val);
	bool getIsCursorInChest();
private:
	ItemClass ItemList[16];

	bool isCursorInChest = false;
	WorldEntetymanager* EntetyMgr;
	int EntetyID;
	//std::list<ItemClass> Item;
};


#endif // !__ENTETY__