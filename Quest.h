#pragma once
#ifndef __QUEST__
#define __QUEST__
#include "TextBox.h"
#include "ItemClass.h"
#include "Entety.h"

using namespace std;

/*
* Consept:
* QuestManager Manages Quest and updates data from those Quests
* Quest is an Object for Storing Quests
* NPC's has interfaces to interface with QuestMgr 
*/

/*
* Impotant:
* Only NPC's or World Entety Mgr can have Quest's
*/


/* 
* QuestObjective has all relevant information for a Quest
* completed: describes if a quest is Completed
* Desription: Descrbes said Quest Objective
* QuestObjectiveID: is an ID given by the QuestObjective
* QuestObjectiveType: is a QuestObject attached to said Quest
* QuestObjectivePtr: is a void Ptr to QuestObject
* additionalInformation: ItemID or other Information
*/

enum QuetsObjectiveTypes {
	QUEST_OBJECTIVE_ITEM_TO_NPC = 0,
	QUEST_OBJECTIVE_TALKE_NPC = 1
};

struct QuestObjective {
	bool completed = false;
	std::wstring Description;
	int QuestObjectiveID;
	int QuestObjectiveType;
	void* QuestObjectivePtr;
	int additionalInformation;

	QuestObjective(bool completed, const std::wstring& Description, int QuestObjectiveType, void* QuestObjectivePtr, int additionalInformation)
		: completed(completed), Description(Description), QuestObjectiveID(-1), QuestObjectiveType(QuestObjectiveType), QuestObjectivePtr(QuestObjectivePtr), additionalInformation(additionalInformation)
	{
	}
};

class QuestManager {
public:
	QuestManager();
	~QuestManager();
	void QuestUpdate();
	void showFirstQuest(int x, int y, Console* console);

	// returns QuestID
	int registerQuest(void* QuestPtr);
	void unregisterQuest(int QuestID);

private:
	vector<void*>QuestObjectiveList;

};

class Quest {
public:
	Quest(std::vector<QuestObjective> QuestObjectivs, QuestManager* QuestMgr);
	void setQuestObjectiveStatus(int QuestObjectiveID, bool status);
	bool getQuestObjectiveStatus(int QuestObjectiveID);
	void drawQuest(int x, int y, Console* console);
	int getQuestID();
	void setQuestID(int QuestID);
	void update();
private:
	std::vector<QuestObjective> QuestObjectivs;
	int DefultQuestDisplayBoxFormate[2] = {
		TEXT_HEAD,
		TEXT_END
	};

	int QuestID;
	QuestManager* QuestMgr;
	TextBox* QuestDisplayTextBox = new TextBox(DefultQuestDisplayBoxFormate, 2);
};





#endif // __QUEST__

