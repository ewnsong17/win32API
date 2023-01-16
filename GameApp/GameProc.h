#pragma once
#pragma comment(lib, "imm32.lib")
#include <Windows.h>
#include <vector>
#include <imm.h>
#include <string>

constexpr int IDC_BTN_START = 1003;
constexpr int IDC_BTN_END = 1004;
constexpr int IDC_TEXT_WORD = 1005;
constexpr int IDC_BTN_ENTER = 1006;
constexpr int IDC_UPDATE_WORD = 1007;
constexpr int IDC_ADD_WORD = 1008;

class Word
{
public:
	int x, y;
	LPCWSTR word;

	Word(int x, int y, LPCWSTR word);
};

class GameData
{
public:
	HWND hGameStart, hGameEnd, hGameTextBox, hGameEnter;
	HFONT hFont, hOldFont;
	LPCWSTR titleText = L"�ܾ� ���߱�";
	BOOL bGameStart = FALSE;
	BOOL bGameEnd = FALSE;
	std::vector<Word*> words;
	INT score = 0;

	std::vector<LPCWSTR> word_list{
		L"���", L"���", L"�ڹ�", L"����", L"���ڿ�", L"��ũ��Ʈ", L"������", L"�ε���", 
		L"�迭", L"��Ʈ��", L"����", L"����ü", L"����", L"����ΰ�", L"�����", L"å", 
		L"����", L"����", L"��ȭ��", L"���콺", L"���ͳ�", L"�Ӹ�", L"�Ȱ�", L"���" };

	GameData();
	VOID SetFont(HWND hWnd);
};

extern GameData AppData;

class GameProc
{
public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
	static VOID CmdProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
	static VOID CreateInitialWindows(HWND hWnd);
	static VOID CreateGameModeWindows(HWND hWnd);
	static VOID PaintTextImage(HWND hWnd);
	static VOID CreateBackGround(HDC& hdc, HDC& hMemDC, HDC& hBackMemDC);
	static VOID CreateText(HDC& hdc);
	static DWORD WINAPI GameMainThread(LPVOID lpParam);
	static VOID UpdateWords(int& index);
	static VOID EnterTextProc(HWND hWnd);
};
