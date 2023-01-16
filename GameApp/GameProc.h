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
	LPCWSTR titleText = L"�ܾ� ���߱�";
	BOOL bGameStart = FALSE;
	BOOL bGameEnd = FALSE;
	std::vector<Word*> words;
	INT score = 0;

	std::vector<Word> word_list
	{
		Word(0, 20, L"���", 1),
		Word(0, 20, L"����", 1),
		Word(0, 20, L"�Ż��Ӵ�", 2),
		Word(0, 20, L"��ǻ��", 1),
		Word(0, 20, L"�ѱ۰���ǻ��", 4),
		Word(0, 20, L"�Ƕ�̵�", 2),
		Word(0, 20, L"����", 1),
		Word(0, 20, L"����", 1),
		Word(0, 20, L"�����", 1),
		Word(0, 20, L"��ٸ���", 2),
		Word(0, 20, L"������", 1),
		Word(0, 20, L"���̾Ƹ��", 3),
		Word(0, 20, L"���̽�ũ��", 3),
		Word(0, 20, L"��ũ����", 2),
		Word(0, 20, L"�ִϵ���ũ", 3),
		Word(0, 20, L"�Ŀ�����Ʈ", 3),
		Word(0, 20, L"���", 1),
		Word(0, 20, L"��ũ��", 1),
		Word(0, 20, L"����", 3),
		Word(0, 20, L"����Ƽ", 1),
		Word(0, 20, L"��Ŀ����", 2),
		Word(0, 20, L"����", 1),
		Word(0, 20, L"�����", 1),
		Word(0, 20, L"�������", 2),
		Word(0, 20, L"�������Ż��", 4),
		Word(0, 20, L"�ܹ���", 1),
		Word(0, 20, L"��õ�������", 4),
		Word(0, 20, L"��ǳ��", 1),
		Word(0, 20, L"����������ٶ�ϰ�", 7),
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
