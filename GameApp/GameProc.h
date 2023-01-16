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
	LPCWSTR titleText = L"단어 맞추기";
	BOOL bGameStart = FALSE;
	BOOL bGameEnd = FALSE;
	std::vector<Word*> words;
	INT score = 0;

	std::vector<LPCWSTR> word_list{
		L"사과", L"언어", L"자바", L"쿼리", L"문자열", L"스크립트", L"데이터", L"인덱스", 
		L"배열", L"스트링", L"벡터", L"구조체", L"딸기", L"산부인과", L"모니터", L"책", 
		L"물병", L"가방", L"전화기", L"마우스", L"인터넷", L"머리", L"안경", L"댓글" };

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
