#include "Quest.h"
//TODO: Quest system Testen und vertigstellen


Quest::Quest(std::vector<QuestObjective> QuestObjectivs) : 
QuestObjectivs(QuestObjectivs){
	int* tmpArray = new int[QuestObjectivs.size() + 2];
	tmpArray[0] = TEXT_HEAD;
	for (size_t i = 0; i < QuestObjectivs.size(); i++) {
		tmpArray[i + 1] = TEXT_BODY;
	}
	tmpArray[QuestObjectivs.size() + 2] = TEXT_END;
	QuestDisplayTextBox->reformate(tmpArray, QuestObjectivs.size() + 2);
	delete[] tmpArray;
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