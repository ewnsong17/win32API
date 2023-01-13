#pragma once
#include <windows.h>
#define IDC_BUTTON1 1003
#define IDC_BUTTON2 1004
#define IDC_TEXTBOX1 1005
#define IDC_BUTTON3 1006

extern HWND hGameStart;
extern HWND hGameEnd;
extern HWND hGameTextBox;
extern HWND hGameEnter;
extern HFONT hFont, oldFont;
extern LPCWSTR titleText;
extern BOOL IsGameStarted;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);