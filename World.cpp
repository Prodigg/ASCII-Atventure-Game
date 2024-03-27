#include "World.h"
#include <string>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <math.h>




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
				if (tmpEntetyID != 4) { // not an Item
					StringBuffer = WorldClass::getObjectSprite(map.WoldMap[i][t]);
					StringBuffer = WorldClass::getObjectSprite(tmpEntetyID);
				}
				else { // item
					StringBuffer = EntetyMgr.getItemSprite(t, i);
				}
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
	case 3:	// NPC %
		return L"%";
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
	case 3:	// NPC %
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

int WorldClass::findShortestDirection(int startX, int startY, int endX, int endY, int lastMove) {
	// calculate reference Distance
	double ReferanceDistance = pythagurasCalculate(startX, endX, startY, endY);

	// calculate move distance
	double MoveDistances[4];
	MoveDistances[0] = pythagurasCalculate(startX + 1, endX, startY, endY);
	MoveDistances[1] = pythagurasCalculate(startX - 1, endX, startY, endY);
	MoveDistances[2] = pythagurasCalculate(startX, endX, startY + 1, endY);
	MoveDistances[3] = pythagurasCalculate(startX, endX, startY - 1, endY);

	// claculate Move score
	int MoveScore[4];
	for (size_t i = 0; i < 4; i++) {
		MoveScore[i] = MoveDistances[i] / ReferanceDistance;
	}

	// calculate allowed moves 
	bool AllowedMoves[4];

	// disallow last move
	AllowedMoves[lastMove] = false;
	
	// check walls
	AllowedMoves[0] = !isBlocking(startX + 1, startY);
	AllowedMoves[1] = !isBlocking(startX - 1, startY);
	AllowedMoves[2] = !isBlocking(startX, startY + 1);
	AllowedMoves[3] = !isBlocking(startX, startY - 1);

	// find best move
	int topChoise = -1;
	double topVal = 0;
	for (size_t i = 0; i < 4; i++) {
		if (topVal < MoveScore[i] && AllowedMoves[i] == true) {
			topVal = MoveScore[i];
			topChoise = i;
		}
	}

	return topChoise;

}

double WorldClass::pythagurasCalculate(double x1, double x2, double y1, double y2) {
	double dx = abs(x1 - x2);
	double dy = abs(y1 - y2);
	return sqrt((dx * dx) + (dy * dy));
}

WorldEntetymanager* WorldClass::getEntetyMgr() {
	return &EntetyMgr;
}