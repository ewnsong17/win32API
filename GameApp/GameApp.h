#pragma once
#include <windows.h>
#include <tchar.h>
#include <iostream>

extern LPCWSTR class_name;
extern HINSTANCE g_hInst;
extern HWND g_h_wnd;
extern HHOOK _k_hook;

INT CreateWndClass(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszcmParam, int cmdShow);