#pragma once
#include <windows.h>
#include <vector>

#define IDC_BTN_START 1003
#define IDC_BTN_END 1004
#define IDC_TEXT_WORD 1005
#define IDC_BTN_ENTER 1006
#define IDC_MAKE_WORD 1007
#define IDC_UPDATE_WORD 1008

extern HWND hGameStart;
extern HWND hGameEnd;
extern HWND hGameTextBox;
extern HWND hGameEnter;
extern HFONT hFont, oldFont;
extern LPCWSTR titleText;
extern BOOL bGameStarted;

class Word
{
public:
	int x, y;
	bool bShow;
	LPCWSTR word;

	Word(int x, int y, bool bShow, LPCWSTR word);
};

extern std::vector<LPCWSTR> word_list;
extern std::vector<Word*> words_;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);