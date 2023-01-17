#define _CRT_RAND_S
#include "GameData.h"

GameData AppData;

GameData::GameData()
{
	ZeroMemory(&this->hGameStart, sizeof(this->hGameStart));
	ZeroMemory(&this->hGameEnd, sizeof(this->hGameEnd));
	ZeroMemory(&this->hGameTextBox, sizeof(this->hGameTextBox));
	ZeroMemory(&this->hGameEnter, sizeof(this->hGameEnter));
	ZeroMemory(&this->hFont, sizeof(this->hFont));
	ZeroMemory(&this->hOldFont, sizeof(this->hOldFont));
}

VOID GameData::SetFont(HWND hWnd)
{
	SendMessage(hWnd, WM_SETFONT, (WPARAM)this->hFont, MAKELPARAM(TRUE, 0));
}

Word GameData::GetNextWord()
{
	int max_weight = 0;

	for (auto iter = this->word_list.begin(); iter != this->word_list.end(); iter++)
	{
		max_weight += iter->weight;
	}

	unsigned int next_value;
	rand_s(&next_value);

	int new_weight = next_value %= max_weight;

	for (auto iter = this->word_list.begin(); iter != this->word_list.end(); iter++)
	{
		new_weight -= iter->weight;
		if (new_weight <= 0)
		{
			return *iter;
		}
	}
}


Word::Word(int x, int y, LPCWSTR word, int score, int weight)
{
	this->x = x;
	this->y = y;
	this->word = word;
	this->score = score;
	this->weight = weight;
}