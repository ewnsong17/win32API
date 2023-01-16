#pragma once
#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

extern LPCWSTR class_name;
extern HINSTANCE g_hInst;
extern HWND g_h_wnd;
extern HHOOK _k_hook;
extern BOOL bEndGame;

INT CreateWndClass(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszcmParam, int cmdShow);

DWORD WINAPI WordThread(LPVOID lpParam);