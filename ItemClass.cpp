#include "ItemClass.h"

/////////// IremClass \\\\\\\\\\

int ItemClass::getItemID() {
	return ItemClass::ItemID;
}

void ItemClass::SetItem(int ItemID, std::wstring _Icon) {
	ItemClass::Icon = _Icon;
	ItemClass::ItemID = ItemID;
	return;
}

std::wstring ItemClass::getIcon() {
	return ItemClass::Icon;
}

bool ItemClass::operator==(const ItemClass& other) const {
	return ItemID == other.ItemID && Icon == other.Icon && isWeapon == other.isWeapon && isArmor == other.isArmor && isRing == other.isRing && isMisc == other.isMisc;
}
