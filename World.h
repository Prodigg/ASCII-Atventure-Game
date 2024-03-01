#pragma once
#include <iostream>
#include <list>

#include "ItemClass.h"
#include "Entety.h"
#include "Engine.h"
#include "Map.h"





//////////////// Chest \\\\\\\\\\\\\\\\


	class WorldClass{
	public:
		std::wstring getObjectSprite(int objectID);
		WORD getObjectColor(int objectID);
		bool drawWorld(int x, int y, int DisplayX, int DisplayY);
		WorldClass(Console* _Console);
		// returns ObjectID
		int getObject(int x, int y);
		bool isBlocking(int x, int y);
		WorldEntetymanager EntetyMgr;

		// returns WorldSprite
		// Warning doesnt return player 
		std::wstring getWorldObject(int x, int y);
	private:

		WorldMap map;
		Console* console;
		
	};