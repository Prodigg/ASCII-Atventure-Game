#include "ItemClass.h"

/////////// IremClass \\\\\\\\\\

ItemClass::ItemClass() : ItemID(-1), Icon(L"?"), ItemType(0) {}
ItemClass::ItemClass(int ItemType, int ItemID, std::wstring _Icon, int DamageModefyer, int ArmorModefyer, int HealthModefyer) :
ItemID(ItemID),
Icon(_Icon), 
DamageModefyer(DamageModefyer),
ArmorModefyer(ArmorModefyer),
HealthModefyer(HealthModefyer),
ItemType(ItemType) {}

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
	return ItemID == other.ItemID && Icon == other.Icon && ItemType == other.ItemType;
}
bool ItemClass::getIsInPlayerInventory() {
	return isItemInInventory;
}

void ItemClass::setIsInPlayerInventory(bool val) {
	isItemInInventory = val;
}

int ItemClass::getItemType() {
	return ItemType;
}