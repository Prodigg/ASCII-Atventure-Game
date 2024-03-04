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
	int getItemID();
	void SetItem(int ItemID, std::wstring _Icon);
	std::wstring getIcon();
	bool operator==(const ItemClass& other) const;
private:
	int ItemID;
	std::wstring Icon;
	bool isWeapon = false;
	bool isArmor = false;
	bool isRing = false;
	bool isMisc = false;

};
