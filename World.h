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

		WorldEntetymanager* getEntetyMgr();

		// returns WorldSprite
		// Warning doesnt return player 
		std::wstring getWorldObject(int x, int y);

		/// <summary>
		/// returns next Direction to Move
		/// 0: right
		/// 1: left
		/// 2: Down
		/// 3: up
		/// </summary>
		/// <param name="startX"></param>
		/// <param name="startY"></param>
		/// <param name="endX"></param>
		/// <param name="endY"></param>
		/// <returns></returns>
		int findShortestDirection(int startX, int startY, int endX, int endY, int lastMove);
	private:
		double pythagurasCalculate(double x1, double x2, double y1, double y2);

		WorldMap map;
		Console* console;
		
	};