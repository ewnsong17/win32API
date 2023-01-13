#pragma once
#include <windows.h>

constexpr static LPCWSTR class_name = L"단어맞추기";
static HINSTANCE g_hInst;

INT CreateWndClass(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszcmParam, int cmdShow);