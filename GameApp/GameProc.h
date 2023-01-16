#pragma once
#pragma comment(lib, "imm32.lib")
#include <Windows.h>
#include <vector>
#include <imm.h>
#include <string>
#include <time.h>

constexpr int IDC_BTN_START = 1003;
constexpr int IDC_BTN_END = 1004;
constexpr int IDC_TEXT_WORD = 1005;
constexpr int IDC_BTN_ENTER = 1006;
constexpr int IDC_UPDATE_WORD = 1007;

class Word
{
public:
	int x, y, score;
	LPCWSTR word;

	Word(int x, int y, LPCWSTR word, int score);
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

	std::vector<Word> word_list
	{
		Word(0, 20, L"사과", 1),
		Word(0, 20, L"가방", 1),
		Word(0, 20, L"신사임당", 2),
		Word(0, 20, L"컴퓨터", 1),
		Word(0, 20, L"한글과컴퓨터", 4),
		Word(0, 20, L"피라미드", 2),
		Word(0, 20, L"물감", 1),
		Word(0, 20, L"의자", 1),
		Word(0, 20, L"모니터", 1),
		Word(0, 20, L"사다리꼴", 2),
		Word(0, 20, L"마름모", 1),
		Word(0, 20, L"다이아몬드", 3),
		Word(0, 20, L"아이스크림", 3),
		Word(0, 20, L"스크래쳐", 2),
		Word(0, 20, L"애니데스크", 3),
		Word(0, 20, L"파워포인트", 3),
		Word(0, 20, L"김밥", 1),
		Word(0, 20, L"생크림", 1),
		Word(0, 20, L"강좌", 3),
		Word(0, 20, L"유니티", 1),
		Word(0, 20, L"서커스단", 2),
		Word(0, 20, L"광대", 1),
		Word(0, 20, L"갈비뼈", 1),
		Word(0, 20, L"소포모어", 2),
		Word(0, 20, L"상대적박탈감", 4),
		Word(0, 20, L"햄버거", 1),
		Word(0, 20, L"인천상륙작전", 4),
		Word(0, 20, L"선풍기", 1),
		Word(0, 20, L"무구정광대다라니경", 7),
	};

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
	static VOID UpdateWords(unsigned int& index);
	static VOID EnterTextProc(HWND hWnd);
};
