#pragma once
#pragma comment(lib, "imm32.lib")
#include <Windows.h>
#include <vector>
#include <imm.h>
#include <string>
#include <time.h>
#include <iostream>

constexpr int IDC_BTN_START = 1003;
constexpr int IDC_BTN_END = 1004;
constexpr int IDC_TEXT_WORD = 1005;
constexpr int IDC_BTN_ENTER = 1006;
constexpr int IDC_UPDATE_WORD = 1007;

class Word
{
public:
	int x, y, score, weight;
	LPCWSTR word;

	Word(int x, int y, LPCWSTR word, int score, int weight);
};

class GameData
{
public:
	HWND hGameStart, hGameEnd, hGameTextBox, hGameEnter;
	HFONT hFont, hOldFont;
	LPCWSTR titleText = L"단어 맞추기";
	BOOL bGameStart = FALSE;
	BOOL bGameEnd = FALSE;
	std::vector<Word*> words;
	INT score = 0;
	INT level = 1;
	std::vector<INT> exp = {20, 30, 45, 60, 90, 120, 150, 180, 300, 500, 0};
	RECT end_line = {0, 540, 640, 542};

	std::vector<Word> word_list
	{
		Word(0, 20, L"사과", 1, 10),
		Word(0, 20, L"가방", 1, 10),
		Word(0, 20, L"신사임당", 2, 8),
		Word(0, 20, L"컴퓨터", 1, 9),
		Word(0, 20, L"한글과컴퓨터", 4, 7),
		Word(0, 20, L"피라미드", 2, 8),
		Word(0, 20, L"물감", 1, 10),
		Word(0, 20, L"의자", 1, 10),
		Word(0, 20, L"모니터", 1, 9),
		Word(0, 20, L"사다리꼴", 2, 8),
		Word(0, 20, L"마름모", 1, 9),
		Word(0, 20, L"다이아몬드", 3, 7),
		Word(0, 20, L"아이스크림", 3, 7),
		Word(0, 20, L"스크래쳐", 2, 8),
		Word(0, 20, L"애니데스크", 3, 7),
		Word(0, 20, L"파워포인트", 3, 7),
		Word(0, 20, L"김밥", 1, 10),
		Word(0, 20, L"생크림", 1, 9),
		Word(0, 20, L"강좌", 1, 10),
		Word(0, 20, L"유니티", 1, 9),
		Word(0, 20, L"서커스단", 2, 8),
		Word(0, 20, L"광대", 1, 10),
		Word(0, 20, L"갈비뼈", 1, 9),
		Word(0, 20, L"소포모어", 2, 8),
		Word(0, 20, L"상대적박탈감", 4, 6),
		Word(0, 20, L"햄버거", 1, 9),
		Word(0, 20, L"인천상륙작전", 4, 6),
		Word(0, 20, L"선풍기", 1, 9),
		Word(0, 20, L"에어컨", 1, 9),
		Word(0, 20, L"메모장", 1, 9),
		Word(0, 20, L"그림판", 1, 9),
		Word(0, 20, L"평행사변형", 3, 7),
		Word(0, 20, L"마이구미", 2, 8),
		Word(0, 20, L"콕콕콕", 1, 9),
		Word(0, 20, L"코딩", 1, 10),
		Word(0, 20, L"귤", 1, 11),
		Word(0, 20, L"감", 1, 11),
		Word(0, 20, L"꽃", 1, 11),
		Word(0, 20, L"생각", 1, 10),
		Word(0, 20, L"양말", 1, 10),
		Word(0, 20, L"과자", 1, 10),
		Word(0, 20, L"허상", 1, 10),
		Word(0, 20, L"공식", 1, 10),
		Word(0, 20, L"간장", 1, 10),
		Word(0, 20, L"수학", 1, 10),
		Word(0, 20, L"과학", 1, 10),
		Word(0, 20, L"영어", 1, 10),
		Word(0, 20, L"직업", 1, 10),
		Word(0, 20, L"탐정", 1, 10),
		Word(0, 20, L"게임", 1, 10),
		Word(0, 20, L"국어", 1, 10),
		Word(0, 20, L"근육", 1, 10),
		Word(0, 20, L"책가방", 1, 9),
		Word(0, 20, L"음식", 1, 10),
		Word(0, 20, L"쓰레기", 1, 9),
		Word(0, 20, L"휴지통", 1, 9),
		Word(0, 20, L"전자키보드", 3, 7),
		Word(0, 20, L"자동차", 1, 9),
		Word(0, 20, L"사슴", 1, 10),
		Word(0, 20, L"도적", 1, 10),
		Word(0, 20, L"전자파", 1, 9),
		Word(0, 20, L"소리", 1, 10),
		Word(0, 20, L"마을", 1, 10),
		Word(0, 20, L"마스크", 1, 9),
		Word(0, 20, L"한국", 1, 10),
		Word(0, 20, L"소크라테스", 3, 7),
		Word(0, 20, L"식물", 1, 10),
		Word(0, 20, L"무구정광대다라니경", 7, 3),
	};

	GameData();
	VOID SetFont(HWND hWnd);
	Word GetNextWord();
};

extern GameData AppData;

class GameProc
{
public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
	static VOID CmdProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
	static VOID CreateInitialWindows(HWND hWnd);
	static VOID CreateGameModeWindows(HWND hWnd);
	static VOID CreateGameEndWindows(HWND hWnd);
	static VOID PaintTextImage(HWND hWnd);
	static VOID CreateBackGround(HDC& hdc, HDC& hMemDC, HDC& hBackMemDC);
	static VOID CreateText(HDC& hdc);
	static DWORD WINAPI GameMainThread(LPVOID lpParam);
	static VOID UpdateWords(unsigned int& index);
	static VOID EnterTextProc(HWND hWnd);
};
