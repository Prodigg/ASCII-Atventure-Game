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