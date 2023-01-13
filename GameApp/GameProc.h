#pragma once
#include <windows.h>
#define IDC_BUTTON1 1003
#define IDC_BUTTON2 1004

extern HWND hGameStart;
extern HWND hGameEnd;
extern HFONT hFont, oldFont;
extern LPCWSTR titleText;
extern BOOL IsGameStarted;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);