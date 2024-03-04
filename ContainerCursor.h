#pragma once
#include "Engine.h"

class ContainerCursor {
public:
	void highliteInvSpace(int Index, Console* console, int InvPos_x, int InvPos_y);
	void highliteInvSpace(int Index, Console* console);

	bool setInventoryCursor(int x, int y);
	bool setInventoryCursor(int Index);
	bool movecusor(int direction);
	int getInventoryCursor();
	void removeInvCursor(Console* console);

protected:
	void setParameters(int InvCursorX, int InvCursorY, int InvCursorIndex);

private:
	int InvCursorX = 0;
	int InvCursorY = 0;

	int InvCursorIndex = 0;

	int calculateInvIndex(int x, int y);
};

