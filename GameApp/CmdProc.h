#pragma once
#include <windows.h>

extern HANDLE hThread;

VOID EnterTextProc(HWND hWnd);

VOID CommandProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);