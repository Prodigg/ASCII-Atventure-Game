#include "ContainerCursor.h"
#include <iostream>

int ContainerCursor::calculateInvIndex(int x, int y) {
	return y * 4 + x;
}

void ContainerCursor::highliteInvSpace(int Index, Console* console) {
	highliteInvSpace(Index, console, InvCursorX, InvCursorY);
}

bool ContainerCursor::setInventoryCursor(int x, int y) {
	if (x < 0 || x > 3 || y < 0 || y > 3) return false;
	InvCursorIndex = calculateInvIndex(x, y);
	InvCursorX = x;
	InvCursorY = y;
	return true;
}

bool ContainerCursor::setInventoryCursor(int Index) {
	if (Index < 0 || Index > 15) return false;
	InvCursorIndex = Index;
	InvCursorX = Index % 4;
	InvCursorY = std::floor(Index / 4);
	return true;
}

bool ContainerCursor::movecusor(int direction) {
	switch (direction) {
	case 0: // Right
		return setInventoryCursor(InvCursorX + 1, InvCursorY);
		break;
	case 1: // Left
		return setInventoryCursor(InvCursorX - 1, InvCursorY);
		break;
	case 2:	// Down
		return setInventoryCursor(InvCursorX, InvCursorY + 1);
		break;
	case 3:	// Up
		return setInventoryCursor(InvCursorX, InvCursorY - 1);
		break;
	default:
		return false;
		break;
	}
}

int ContainerCursor::getInventoryCursor() {
	return InvCursorIndex;
}

void ContainerCursor::highliteInvSpace(int Index, Console* console, int InvPos_x, int InvPos_y) {
	console->PlortColor(InvPos_y + 2 + (std::floor(Index / 4) * 2), 2 + ((Index % 4) * 4), 0xF0);
	return;
}


void ContainerCursor::setParameters(int InvCursorX, int InvCursorY, int InvCursorIndex) {
	ContainerCursor::InvCursorX = InvCursorX;
	ContainerCursor::InvCursorY = InvCursorY;
	ContainerCursor::InvCursorIndex = InvCursorIndex;
	return;
}

void ContainerCursor::removeInvCursor(Console* console) {
	console->PlortColor(InvCursorX, InvCursorY, 7);
}