#pragma once
#include <windows.h>

constexpr static LPCWSTR class_name = L"�ܾ���߱�";
static HINSTANCE g_hInst;

INT CreateWndClass(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszcmParam, int cmdShow);