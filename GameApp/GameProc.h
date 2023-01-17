#pragma once
#pragma comment(lib, "imm32.lib")
#include <Windows.h>
#include <imm.h>
#include <string>
#include <time.h>
#include <iostream>

constexpr int IDC_BTN_START = 1003;
constexpr int IDC_BTN_END = 1004;
constexpr int IDC_TEXT_WORD = 1005;
constexpr int IDC_BTN_ENTER = 1006;
constexpr int IDC_UPDATE_WORD = 1007;

class GameProc
{
public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
	static VOID CmdProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
	static VOID CreateInitialWindows(HWND hWnd);
	static VOID CreateGameModeWindows(HWND hWnd);
	static VOID CreateGameStopWindows(HWND hWnd);
	static VOID CreateGameEndWindows(HWND hWnd);
	static VOID PaintTextImage(HWND hWnd);
	static VOID CreateBackGround(HDC& hdc, HDC& hMemDC, HDC& hBackMemDC);
	static VOID CreateText(HDC& hdc);
	static VOID CreateGameToolTipText(HDC& hdc);
	static VOID CreateGameResumeEndText(HDC& hdc);
	static VOID CreateGameWordListText(HDC& hdc);
	static DWORD WINAPI GameMainThread(LPVOID lpParam);
	static VOID UpdateWords(unsigned int& index);
	static VOID EnterTextProc(HWND hWnd);
	static VOID EscapeProc(HWND hWnd);
	static VOID UseBombSkill(HWND hWnd);
	static VOID RemoveAllWords(BOOL bAddScore);
};
