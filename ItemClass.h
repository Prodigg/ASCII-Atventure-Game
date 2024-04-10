#pragma once
#include <string>

/*
* Item ID's
* 
* -1: Test Object
* 0: void
* 
*/

class ItemClass {
public:
	ItemClass();
	/*
	* ItemType:
	* 0: Not Equipable
	* 1: Wapon
	* 2: Armor
	* 3: Ring
	* 4: Misc
	*/
	ItemClass(int ItemType, int ItemID, std::wstring _Icon, int DamageModefyer, int ArmorModefyer, int HealthModefyer);
	int getItemID();
	void SetItem(int ItemID, std::wstring _Icon);
	std::wstring getIcon();
	bool operator==(const ItemClass& other) const;
	bool getIsInPlayerInventory();
	void setIsInPlayerInventory(bool val);
	int getItemType();
private:
	int ItemID;
	std::wstring Icon;
	int ItemType = 0;

	bool isItemInInventory = false;

	int DamageModefyer = 0;
	int ArmorModefyer = 0;
	int HealthModefyer = 0;
};
