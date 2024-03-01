#include "World.h"
#include <string>
#include <fcntl.h>
#include <io.h>
#include <iostream>




//////////// WorldClass \\\\\\\\\\\\\\

#define seeRange int(4)

bool WorldClass::drawWorld(int x, int y, int DisplayX, int DisplayY) {
	int xPos = DisplayX;
	int yPos = DisplayY;
	std::wstring StringBuffer = L"";
	WORD ColorBuffer = 0x00;
	for (size_t i = y - seeRange; i < y + seeRange + 1; i++) {
		for (size_t t = x - seeRange; t < x + seeRange + 1; t++) {
			if (i == y && t == x) { // player pos?
				StringBuffer = WorldClass::getObjectSprite(100); 
				ColorBuffer = WorldClass::getObjectColor(100) + WorldClass::getObjectColor(map.WoldMap[i][t]);
			} 
			else { 
				int tmpEntetyID = WorldClass::EntetyMgr.getEntety(t, i);
				StringBuffer = WorldClass::getObjectSprite(map.WoldMap[i][t]); 
				StringBuffer = WorldClass::getObjectSprite(tmpEntetyID);
				ColorBuffer = WorldClass::getObjectColor(map.WoldMap[i][t]) + WorldClass::getObjectColor(tmpEntetyID);
			}
			console->Plot(yPos, xPos, StringBuffer, ColorBuffer);
			xPos++;
		}
		//std::wcout << std::endl;
		xPos = 0;
		yPos++;
	}
	
	return true;
}

std::wstring WorldClass::getObjectSprite(int ObjectID) {
	switch (ObjectID) {
	case -1: // void
		return L" ";
		break;
	case 0: //ground ░
		return L" ";
	case 1:	//wall █
		return L" ";
	case 2:	// Chest #
		return L"#";
	case 100: //Player *
		return L"*";

	default:
		break;
	}
	return L"?";
}

WORD WorldClass::getObjectColor(int ObjectID) {
	switch (ObjectID) {
	case 0: //ground ░ (backround: blue Text: defult)
		return 0x90;
	case 1:	//wall █
		return 0x10;
	case 2:	// Chest #
		return 0x07;
	case 100: //Player *
		return 0x07;

	default:
		break;
	}
	return 0x07;
}

int WorldClass::getObject(int x, int y) {
	return map.WoldMap[y][x];
}


std::wstring WorldClass::getWorldObject(int x, int y) {
	return WorldClass::getObjectSprite(map.WoldMap[x][y]);
}


WorldClass::WorldClass(Console* _Console) : console(_Console) {}

bool WorldClass::isBlocking(int x, int y) {
	bool tmp = EntetyMgr.isEntetyBlocking(x, y);
	if (getObject(x, y) == 1) tmp = true;
	return tmp;
}