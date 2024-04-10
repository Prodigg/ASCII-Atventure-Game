#include "TextBox.h"

TextBoxSimple::TextBoxSimple(int TextFormate[], int elementCount) {
	reformate(TextFormate, elementCount);
}

void TextBoxSimple::display(int x, int y, Console* console) {
	for (size_t i = 0; i < TextBuffer.size(); i++) {
		console->Plot(y + i, x, TextBuffer.at(i));
	}
}

void TextBoxSimple::display(int x, int y, WORD color, Console* console) {
	for (size_t i = 0; i < TextBuffer.size(); i++) {
		console->Plot(x, y + i, TextBuffer.at(i), color);
	}
}

bool TextBoxSimple::setText(int line, int characterOffset, std::wstring Text) {
	TextBuffer.at(line).replace(characterOffset, Text.length(), Text);
	return true;
}

void TextBoxSimple::clearText() {
	TextBuffer.clear();

	// init TextBuffer
	for (size_t i = 0; i < TextBoxFormate.size(); i++) {
		TextBuffer.push_back(MsgBoxComponents[TextBoxFormate.at(i)]);
	}
}

void TextBoxSimple::reformate(int TextFormate[], int elementCount) {
	// init TextBoxFormate
	TextBoxSimple::TextBoxFormate.clear();
	TextBoxSimple::TextBuffer.clear();
	for (size_t i = 0; i < elementCount; i++) {
		TextBoxSimple::TextBoxFormate.push_back(TextFormate[i]);
	}

	// init TextBuffer
	for (size_t i = 0; i < TextBoxFormate.size(); i++) {
		TextBuffer.push_back(MsgBoxComponents[TextBoxFormate.at(i)]);
	}
}

/////////////// TextBox \\\\\\\\\\\\

TextBox::TextBox(int TextFormate[], int elementCount) {
	reformate(TextFormate, elementCount);
}

void TextBox::display(int x, int y, Console* console) {
	display(x, y, 7, console);
}

void TextBox::display(int x, int y, WORD color, Console* console) {
	for (size_t g = 0; g < TextBuffer.size(); g++) {
		for (size_t i = 0; i < TextBuffer.at(g).length(); i++) {
			if (TextBuffer.at(g).at(i) == L'|') { // make sub
				TextBuffer.at(g).replace(i, 1, L"│");
				if (TextBuffer.at(g - 1).at(i) == L'─') TextBuffer.at(g - 1).replace(i, 1, L"┬");
				else if (TextBuffer.at(g - 1).at(i) == L'┴') TextBuffer.at(g - 1).replace(i, 1, L"┼");
	
				if (TextBuffer.at(g + 1).at(i) == L'─') TextBuffer.at(g + 1).replace(i, 1, L"┴");
				else if (TextBuffer.at(g + 1).at(i) == L'┬') TextBuffer.at(g + 1).replace(i, 1, L"┼");
			}
		}
	}
	for (size_t i = 0; i < TextBuffer.size(); i++) {
		console->Plot(y + i, x, TextBuffer.at(i), color);
	}
}

bool TextBox::setText(int line, int characterOffset, std::wstring Text) {
	int TextLength = Text.length();
	if (TextLength > BoxTextLength) { // make box wider
		int numCharToAdd = TextLength - BoxTextLength;
		for (size_t i = 0; i < TextBuffer.size(); i++) {
			if (TextBoxFormate.at(i) != TEXT_BODY) {
				for (size_t t = 0; t < numCharToAdd; t++) {
					TextBuffer.at(i).insert(1, 1, L'─');
				}
			}
			else {
				for (size_t t = 0; t < numCharToAdd; t++) {
					TextBuffer.at(i).insert(TextBuffer.at(i).length() - 1, 1, L' ');
				}
			}
		}
		BoxTextLength = TextLength;
	}
	TextBuffer.at(line).replace(characterOffset, Text.length(), Text);
	return true;
}

void TextBox::clearText() {
	TextBuffer.clear();
	BoxTextLength = 0;

	// init TextBuffer
	for (size_t i = 0; i < TextBoxFormate.size(); i++) {
		TextBuffer.push_back(MsgBoxComponents[TextBoxFormate.at(i)]);
	}
}

void TextBox::reformate(int TextFormate[], int elementCount) {
	// init TextBoxFormate
	TextBox::TextBoxFormate.clear();
	TextBox::TextBuffer.clear();
	for (size_t i = 0; i < elementCount; i++) {
		TextBox::TextBoxFormate.push_back(TextFormate[i]);
	}

	// init TextBuffer
	for (size_t i = 0; i < TextBoxFormate.size(); i++) {
		TextBuffer.push_back(MsgBoxComponents[TextBoxFormate.at(i)]);
	}
}


///////////////// DialogeBox \\\\\\\\\\\\\\\\\

DialogeBox::DialogeBox(std::vector<std::vector<std::wstring>> MainText, std::vector<std::vector<Option>> Options) :
MainText(MainText),
Options(Options) {
	for (size_t i = 0; i < 9; i++) {
		DisabledOptions[i] = false;
	}
	DisplayTextBox = new TextBox(TextBoxDeafultFormate, 5); // init TextBox
}

void DialogeBox::setPage(int pageNum) {
	currentPage = pageNum;
}

bool DialogeBox::optionSelected(int option) {
	currentPage = Options.at(currentPage).at(option - 1).redirect;
	return true;
}

void DialogeBox::display(int x, int y, Console* console) {
	// clear Buffers for new Calculation
	DisplayTextBox->clearText();
	TextBoxFormate.clear();

	// calculate new formate
	TextBoxFormate.push_back(TEXT_HEAD);
	for (size_t i = 0; i < MainText.at(currentPage).size(); i++) { // main Text
		TextBoxFormate.push_back(TEXT_BODY);
	}
	TextBoxFormate.push_back(TEXT_SEPERATOR);
	for (size_t i = 0; i < Options.at(currentPage).size(); i++) { // options
		if(DisabledOptions[i] == false) {
			TextBoxFormate.push_back(TEXT_BODY);
		}
	}
	TextBoxFormate.push_back(TEXT_END);

	// push formate into TextBox
	int* tmpArray = new int[TextBoxFormate.size()];
	for (size_t i = 0; i < TextBoxFormate.size(); i++) {
		tmpArray[i] = TextBoxFormate.at(i);
	}
	DisplayTextBox->reformate(tmpArray, TextBoxFormate.size());
	delete[] tmpArray;

	// set main Text
	for (size_t i = 0; i < MainText.at(currentPage).size(); i++) {
		DisplayTextBox->setText(i + 1, 1, MainText.at(currentPage).at(i));
	}
	int longestString = 0;

	// find longest string
	for (size_t i = 0; i < MainText.at(currentPage).size(); i++) {
		if (MainText.at(currentPage).at(i).size() > longestString) {		// new longest string
			longestString = MainText.at(currentPage).at(i).size();
		}
	}
	for (size_t i = 0; i < Options.at(currentPage).size(); i++) {
		if (Options.at(currentPage).at(i).Text.size() + 4 > longestString && DisabledOptions[i] == false) {		// new longest string
			longestString = Options.at(currentPage).at(i).Text.size();
		}
	}

	// construct Options 
	for (size_t i = 0; i < Options.at(currentPage).size(); i++) {
		if (DisabledOptions[i] == false) {
			std::wstring tmpString = L"";
			tmpString += Options.at(currentPage).at(i).Text;

			// fill empty space
			for (size_t t = 0; t < longestString - Options.at(currentPage).at(i).Text.size() - 4; t++) {
				tmpString += L" ";
			}
			// push option at the end
			tmpString += L"| ";
			tmpString += std::to_wstring(i + 1);
			tmpString += L" ";
			DisplayTextBox->setText(MainText.at(currentPage).size() + i + 2, 1, tmpString);
		}
	}
	DisplayTextBox->display(x, y, console);
}

Option* DialogeBox::getOptions(int page, int option) {
	return &Options.at(page).at(option-1);
}

bool DialogeBox::isOptionAvalable(int option) {
	if (Options.at(currentPage).size() < option - 1) return false;
	if (DisabledOptions[option - 1] == true) return false;
	return true;
}

void DialogeBox::DisableOption(int option) {
	DisabledOptions[option] = true;
}

void DialogeBox::enableOption(int option) {
	DisabledOptions[option] = false;
}