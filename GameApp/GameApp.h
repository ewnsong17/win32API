#pragma once
#include <windows.h>
#include <tchar.h>

extern LPCWSTR class_name;
extern HINSTANCE g_hInst;

INT CreateWndClass(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszcmParam, int cmdShow);