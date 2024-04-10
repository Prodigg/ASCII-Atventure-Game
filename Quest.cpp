#include "Quest.h"
//TODO: Quest system Testen und vertigstellen


Quest::Quest(std::vector<QuestObjective> QuestObjectivs, QuestManager* QuestMgr) :
QuestObjectivs(QuestObjectivs), 
QuestMgr(QuestMgr) {
	int* tmpArray = new int[QuestObjectivs.size() + 2];
	tmpArray[0] = TEXT_HEAD;
	for (size_t i = 0; i < QuestObjectivs.size(); i++) {
		tmpArray[i + 1] = TEXT_BODY;
	}
	tmpArray[QuestObjectivs.size() + 1] = TEXT_END;
	QuestDisplayTextBox->reformate(tmpArray, QuestObjectivs.size() + 2);
	delete[] tmpArray;
	QuestID = QuestMgr->registerQuest(this);
}

void Quest::drawQuest(int x, int y, Console* console) {
	QuestDisplayTextBox->clearText();
	// find longest string
	int longestString = 0;
	for (size_t i = 0; i < QuestObjectivs.size(); i++) {
		if (longestString < QuestObjectivs.at(i).Description.length()) longestString = QuestObjectivs.at(i).Description.length();
	}
	
	// construct Quest Display Strings
	for (size_t i = 0; i < QuestObjectivs.size(); i++) {
		std::wstring TmpString = L" ";
		// check completed status
		if (QuestObjectivs.at(i).completed == true) {
			TmpString += L"█"; // completed
		}
		else {
			TmpString += L"░"; // not completed
		}
		TmpString += L" | ";
		TmpString += QuestObjectivs.at(i).Description;

		QuestDisplayTextBox->setText(i + 1, 1, TmpString);

	}
	QuestDisplayTextBox->display(x, y, console);
	return;	
}

void Quest::setQuestObjectiveStatus(int QuestObjectiveID, bool status) {
	// search for QuestObjectiveID
	int QuestObjectivePos = -1;
	for (size_t i = 0; i < QuestObjectivs.size(); i++) {
		if (QuestObjectivs.at(i).QuestObjectiveID == QuestObjectiveID) {
			QuestObjectivePos = i;
			break;
		}
	}

	// return if no QuestQobjective was found
	if (QuestObjectivePos == -1) return;

	// set QuestObjective to status
	QuestObjectivs.at(QuestObjectivePos).completed = status;
	return;
}

bool Quest::getQuestObjectiveStatus(int QuestObjectiveID) {
	// search for QuestObjectiveID
	int QuestObjectivePos = -1;
	for (size_t i = 0; i < QuestObjectivs.size(); i++) {
		if (QuestObjectivs.at(i).QuestObjectiveID == QuestObjectiveID) {
			QuestObjectivePos = i;
			break;
		}
	}

	// return if no QuestQobjective was found
	if (QuestObjectivePos == -1) return false;

	return QuestObjectivs.at(QuestObjectivePos).completed;
}

int Quest::getQuestID() {
	return Quest::QuestID;
}

void Quest::setQuestID(int QuestID) {
	Quest::QuestID = QuestID;
}

void Quest::update() {
	for (size_t i = 0; i < QuestObjectivs.size(); i++) {
		
			switch (QuestObjectivs.at(i).QuestObjectiveType) {
			case QUEST_OBJECTIVE_ITEM_TO_NPC: // NPC must have certan Item
				if (static_cast<NPC*>(QuestObjectivs.at(i).QuestObjectivePtr)->checkForItem(QuestObjectivs.at(i).additionalInformation)) {
					QuestObjectivs.at(i).completed = true;
				}
				break;
			case QUEST_OBJECTIVE_TALKE_NPC:
				if (static_cast<NPC*>(QuestObjectivs.at(i).QuestObjectivePtr)->getNPCState() == NPC_DIALOGE) {
					QuestObjectivs.at(i).completed = true;
				}
				break;
			default:
				break;
			}
	}
}

/////////////////// QuestManager \\\\\\\\\\\\\\\\

QuestManager::QuestManager() {
}

QuestManager ::~QuestManager() {
}


void QuestManager::QuestUpdate() {
	for (size_t i = 0; i < QuestObjectiveList.size(); i++) {
		static_cast<Quest*>(QuestObjectiveList.at(i))->update();
	}
}

int QuestManager::registerQuest(void* QuestPtr) {
	// search for free QuestID
	int TmpQuestID = 0;
	for (size_t i = 0; i < QuestObjectiveList.size(); i++) {
		if (static_cast<Quest*>(QuestObjectiveList.at(i))->getQuestID() == TmpQuestID) TmpQuestID++;
	}
	// set QuestID
	static_cast<Quest*>(QuestPtr)->setQuestID(TmpQuestID);

	// add Quest to Array
	QuestObjectiveList.push_back(QuestPtr);
	return TmpQuestID;
}

void QuestManager::unregisterQuest(int QuestID) {
	// find Quest
	int QuestPos = -1;
	for (size_t i = 0; i < QuestObjectiveList.size(); i++) {
		if (static_cast<Quest*>(QuestObjectiveList.at(i))->getQuestID() == QuestID) {
			QuestPos = i;
			break;
		}
	}

	// check if Quest was found
	if (QuestPos == -1) return;

	// delete Quest from QuestObjectiveArray
	std::vector<void*>::iterator* QuestArrayIterator = new std::vector<void*>::iterator;
	*QuestArrayIterator = QuestObjectiveList.begin() + QuestPos;
	QuestObjectiveList.erase(*QuestArrayIterator);
	delete QuestArrayIterator;

	return;
}


void QuestManager::showFirstQuest(int x, int y, Console* console) {
	return static_cast<Quest*>(QuestObjectiveList.at(0))->drawQuest(x, y, console);
}