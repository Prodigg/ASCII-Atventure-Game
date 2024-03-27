#pragma once
#ifndef __QUEST__
#define __QUEST__
#include "TextBox.h"
#include "ItemClass.h"
#include "Entety.h"

struct QuestObjective {
	bool completed = false;
	std::wstring Description;
	int QuestObjectiveID;
};

class Quest {
public:
	Quest(std::vector<QuestObjective> QuestObjectivs);
	void setQuestObjectiveStatus(int QuestObjectiveID, bool status);
	bool getQuestObjectiveStatus(int QuestObjectiveID);
	void drawQuest(int x, int y, Console* console);

private:
	std::vector<QuestObjective> QuestObjectivs;
	int DefultQuestDisplayBoxFormate[2] = {
		TEXT_HEAD,
		TEXT_END
	};

	TextBox* QuestDisplayTextBox = new TextBox(DefultQuestDisplayBoxFormate, 2);
};

#endif // __QUEST__

