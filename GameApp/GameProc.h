#pragma once
#include <windows.h>

static HWND hGameStart;
static HWND hGameEnd;
constexpr static LPCWSTR titleText = L"단어 맞추기 게임";
constexpr static auto IDC_BUTTON1 = 1003;
constexpr static auto IDC_BUTTON2 = 1004;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);