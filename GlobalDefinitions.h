#pragma once
#include <string>
#include <fcntl.h>

#include "World.h"
#include "Player.h"
#include "Engine.h"

//////////// World Objects \\\\\\\\\\\\

Console MainConsole;
Player MainCaracter;
WorldClass GlobalWorld(&MainConsole);
Terminal MainTerminal(PRINT_ARRAY_X, PRINT_ARRAY_Y, &MainConsole);

/////////// UI Interface \\\\\\\\\\\\

std::wstring Menu[12] = {
	L"┌──────────────────┐",
	L"│     Actions      │",
	L"├────────────────┬─┤",
	L"│ Move Right     │a│",
	L"│ Move Left      │d│",
	L"│ Move Down      │s│",
	L"│ Move Up        │w│",
	L"│ Interact       │f│",
	L"│ Close          │f│",
	L"│ Inventory      │i│",
	L"│ Close          │i│",
	L"└────────────────┴─┘"
};

std::wstring MsgBox[1][8]{
	{
	L"┌──────────────────┐",
	L"│      Error       │",
	L"├──────────────────┤",
	L"│    User Imput    │",
	L"│ ist keine Aktion │",
	L"│die zur verfügung │",
	L"│      steht       │"	,
	L"└──────────────────┘"
	}
};





