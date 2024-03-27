#pragma once
#ifndef __TEXT_BOX__
#define __TEXT_BOX__

#include <string>
#include <vector>
#include "Engine.h"

/*
* 0: Head
* 1: seperator
* 2: Body
* 3: end
*/

enum TextEnum {
	TEXT_HEAD = 0,
	TEXT_SEPERATOR = 1,
	TEXT_BODY = 2,
	TEXT_END = 3
};

class TextBoxSimple {
public:
	TextBoxSimple(int TextFormate[], int elementCount);
	void display(int x, int y, Console* console);
	void display(int x, int y, WORD color, Console* console);
	bool setText(int line, int characterOffset, std::wstring Text);
	void clearText();
	void reformate(int TextFormate[], int elementCount);

private:
	std::vector<int> TextBoxFormate;
	std::vector<std::wstring> TextBuffer;

	const std::wstring MsgBoxComponents[4]{
	L"┌──────────────────┐",
	L"├──────────────────┤",
	L"│                  │",
	L"└──────────────────┘"
	};

};

class TextBox {
public:
	TextBox (int TextFormate[], int elementCount);
	void display(int x, int y, Console* console);
	void display(int x, int y, WORD color, Console* console);
	bool setText(int line, int characterOffset, std::wstring Text);
	void clearText();
	void reformate(int TextFormate[], int elementCount);

private:
	std::vector<int> TextBoxFormate;
	std::vector<std::wstring> TextBuffer;

	const std::wstring MsgBoxComponents[4]{
	L"┌┐",
	L"├┤",
	L"││",
	L"└┘"
	};

	int BoxTextLength = 0;
};

/*
* Actions:
* 0: Nothing 
* 1: dropItem
*		ActionParameter2:
*		0: up
*		1: down
*		2: left
*		3: right
*/

struct Option {
	std::wstring Text;
	int redirect;
	int action;
	int actionPrameter;
	int actionPrameter2;

	Option(const std::wstring& Text, int redirect, int action, int actionPrameter, int actionPrameter2)
		: Text(Text), redirect(redirect), action(action), actionPrameter(actionPrameter), actionPrameter2(actionPrameter2)
	{}
	Option(const std::wstring& Text, int redirect, int action, int actionPrameter)
		: Text(Text), redirect(redirect), action(action), actionPrameter(actionPrameter), actionPrameter2(0)
	{}
	Option(const std::wstring& Text, int redirect, int action)
		: Text(Text), redirect(redirect), action(action), actionPrameter(0), actionPrameter2(0)
	{}
	Option(const std::wstring& Text, int redirect)
		: Text(Text), redirect(redirect), action(0), actionPrameter(0), actionPrameter2(0)
	{}
}

class DialogeBox {
public:
	DialogeBox(std::vector<std::vector<std::wstring>> MainText, std::vector<std::vector<Option>> Options);
	void display(int x, int y, Console* console);
	void setPage(int pageNum);
	void tmpDisableOption(int option);
	void enableOption(int option);
	int getPage() { return currentPage; }


protected:
	bool optionSelected(int option);
	Option* getOptions(int page, int option);
private:
	int TextBoxDeafultFormate[5] = {
		TEXT_HEAD,
		TEXT_BODY,
		TEXT_SEPERATOR,
		TEXT_BODY,
		TEXT_END
	};

	std::vector<std::vector<std::wstring>> MainText;
	std::vector<std::vector<Option>> Options;
	bool DisabledOptions[9];
	TextBox* DisplayTextBox = new TextBox(TextBoxDeafultFormate, 5);
	std::vector<int> TextBoxFormate;
	int currentPage = 0;

	

};




#endif // !__TEXT_BOX__