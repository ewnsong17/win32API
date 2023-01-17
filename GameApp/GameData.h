#pragma once
#include <Windows.h>
#include <vector>

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
	LPCWSTR titleText = L"�ܾ� ���߱�";
	BOOL bGameStart = FALSE;
	BOOL bGameEnd = FALSE;
	BOOL bGameStop = FALSE;
	std::vector<Word*> words;
	INT score = 0, level = 1, bomb = 3, life = 3;
	
	std::vector<INT> exp = { 10, 25, 40, 60, 85, 110, 140, 175, 210, 250, 0 };
	std::vector<INT> level_cool_f = { 3, 3, 3, 2, 2, 2, 2, 1, 2, 1, 0 };
	std::vector<INT> level_cool_l = { 5, 4, 3, 4, 3, 2, 2, 3, 3, 2, 1 };
	std::vector<INT> level_count = { 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2 };
	RECT end_line = { 0, 540, 640, 545 };

	std::vector<Word> word_list
	{
		Word(0, 20, L"���", 1, 10),
		Word(0, 20, L"����", 1, 10),
		Word(0, 20, L"�Ż��Ӵ�", 2, 8),
		Word(0, 20, L"��ǻ��", 1, 9),
		Word(0, 20, L"�ѱ۰���ǻ��", 4, 7),
		Word(0, 20, L"�Ƕ�̵�", 2, 8),
		Word(0, 20, L"����", 1, 10),
		Word(0, 20, L"����", 1, 10),
		Word(0, 20, L"�����", 1, 9),
		Word(0, 20, L"��ٸ���", 2, 8),
		Word(0, 20, L"������", 1, 9),
		Word(0, 20, L"���̾Ƹ��", 3, 7),
		Word(0, 20, L"���̽�ũ��", 3, 7),
		Word(0, 20, L"��ũ����", 2, 8),
		Word(0, 20, L"�ִϵ���ũ", 3, 7),
		Word(0, 20, L"�Ŀ�����Ʈ", 3, 7),
		Word(0, 20, L"���", 1, 10),
		Word(0, 20, L"��ũ��", 1, 9),
		Word(0, 20, L"����", 1, 10),
		Word(0, 20, L"����Ƽ", 1, 9),
		Word(0, 20, L"��Ŀ����", 2, 8),
		Word(0, 20, L"����", 1, 10),
		Word(0, 20, L"�����", 1, 9),
		Word(0, 20, L"�������", 2, 8),
		Word(0, 20, L"�������Ż��", 4, 6),
		Word(0, 20, L"�ܹ���", 1, 9),
		Word(0, 20, L"��õ�������", 4, 6),
		Word(0, 20, L"��ǳ��", 1, 9),
		Word(0, 20, L"������", 1, 9),
		Word(0, 20, L"�޸���", 1, 9),
		Word(0, 20, L"�׸���", 1, 9),
		Word(0, 20, L"����纯��", 3, 7),
		Word(0, 20, L"���̱���", 2, 8),
		Word(0, 20, L"������", 1, 9),
		Word(0, 20, L"�ڵ�", 1, 10),
		Word(0, 20, L"��", 1, 11),
		Word(0, 20, L"��", 1, 11),
		Word(0, 20, L"��", 1, 11),
		Word(0, 20, L"����", 1, 10),
		Word(0, 20, L"�縻", 1, 10),
		Word(0, 20, L"����", 1, 10),
		Word(0, 20, L"���", 1, 10),
		Word(0, 20, L"����", 1, 10),
		Word(0, 20, L"����", 1, 10),
		Word(0, 20, L"����", 1, 10),
		Word(0, 20, L"����", 1, 10),
		Word(0, 20, L"����", 1, 10),
		Word(0, 20, L"����", 1, 10),
		Word(0, 20, L"Ž��", 1, 10),
		Word(0, 20, L"����", 1, 10),
		Word(0, 20, L"����", 1, 10),
		Word(0, 20, L"����", 1, 10),
		Word(0, 20, L"å����", 1, 9),
		Word(0, 20, L"����", 1, 10),
		Word(0, 20, L"������", 1, 9),
		Word(0, 20, L"������", 1, 9),
		Word(0, 20, L"����Ű����", 3, 7),
		Word(0, 20, L"�ڵ���", 1, 9),
		Word(0, 20, L"�罿", 1, 10),
		Word(0, 20, L"����", 1, 10),
		Word(0, 20, L"������", 1, 9),
		Word(0, 20, L"�Ҹ�", 1, 10),
		Word(0, 20, L"����", 1, 10),
		Word(0, 20, L"����ũ", 1, 9),
		Word(0, 20, L"�ѱ�", 1, 10),
		Word(0, 20, L"��ũ���׽�", 3, 7),
		Word(0, 20, L"�Ĺ�", 1, 10),
		Word(0, 20, L"����������ٶ�ϰ�", 7, 3),
	};

	GameData();
	VOID SetFont(HWND hWnd);
	Word GetNextWord();
};

extern GameData AppData;