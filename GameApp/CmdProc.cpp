#define NOMINMAX
#include "GameProc.h"
#include "GameData.h"

VOID GameProc::CmdProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
		case IDC_BTN_START:
		{
			ShowWindow(AppData.hGameStart, SW_HIDE);
			ShowWindow(AppData.hGameEnd, SW_HIDE);
			DestroyWindow(AppData.hGameStart);
			DestroyWindow(AppData.hGameEnd);

			if (AppData.bGameEnd)
			{
				AppData.words.clear();
				AppData.bGameEnd = FALSE;
			}

			AppData.bGameStart = TRUE;

			InvalidateRect(hWnd, nullptr, TRUE);
			UpdateWindow(hWnd);

			GameProc::CreateGameModeWindows(hWnd);

			if (!AppData.bGameStop)
			{
				DWORD threadId = 0;
				DWORD threadParam = 0;
				CreateThread(nullptr, 0, GameMainThread, &threadParam, 0, &threadId);
			}
			
			AppData.bGameStop = FALSE;
			break;
		}
		case IDC_BTN_END:
		{
			if (IDYES == MessageBox(hWnd, L"게임을 종료하시겠습니까?", L"알림", MB_YESNO))
			{
				SendMessage(hWnd, WM_DESTROY, wParam, lParam);
			}
			break;
		}
		case IDC_TEXT_WORD:
		{
			if (HIWORD(wParam) == EN_SETFOCUS)
			{
				SetDlgItemText(hWnd, IDC_TEXT_WORD, L"");
			}
			break;
		}
		case IDC_BTN_ENTER:
		{
			EnterTextProc(hWnd);
			break;
		}
		case IDC_UPDATE_WORD:
		{
			std::vector<int> remove_index;
			int index = -1;
			bool bChange = FALSE;

			for (auto iter = AppData.words.begin(); iter != AppData.words.end(); iter++)
			{
				index++;
				bChange = TRUE;
				(*iter)->y += 25;

				if ((*iter)->y > 530)
				{
					AppData.life--;
					remove_index.push_back(index);
				}
				
				if (AppData.life <= 0)
				{
					AppData.bGameEnd = TRUE;
					AppData.bGameStart = FALSE;

					ShowWindow(AppData.hGameTextBox, SW_HIDE);
					ShowWindow(AppData.hGameEnter, SW_HIDE);
					DestroyWindow(AppData.hGameTextBox);
					DestroyWindow(AppData.hGameEnter);

					InvalidateRect(hWnd, nullptr, TRUE);
					UpdateWindow(hWnd);
					GameProc::RemoveAllWords(FALSE);
					GameProc::CreateGameEndWindows(hWnd);
					return;
				}
			}

			for (int i = 0; i < remove_index.size(); i++)
			{
				auto it = AppData.words.begin() + remove_index[i];
				free(*it);
				AppData.words.erase(it);

				InvalidateRect(hWnd, new RECT{ 630, 0, 640, 640 }, TRUE);
				UpdateWindow(hWnd);
			}

			if (bChange && !AppData.bGameEnd)
			{
				InvalidateRect(hWnd, new RECT{ 0, 0, 640, 630 }, TRUE);
				UpdateWindow(hWnd);
			}
			break;
		}
	}
}

VOID GameProc::EnterTextProc(HWND hWnd)
{
	TCHAR buff[255];
	LPWSTR text = (LPWSTR)buff;

	GetWindowText(AppData.hGameTextBox, text, 1024);

	int add_score = 0;
	for (auto iter = AppData.words.begin(); iter != AppData.words.end(); iter++)
	{
		if (wcscmp(text, (*iter)->word) == 0)
		{
			add_score = (*iter)->score;
			AppData.score += add_score;
			if (AppData.level <= 10 && AppData.score >= AppData.exp[AppData.level - (INT)1])
			{
				AppData.level++;
				AppData.life = std::min(3, AppData.life + 1);
				if (AppData.level == 6 || AppData.level == 11)
				{
					AppData.bomb = std::min(3, AppData.bomb + 1);
				}
			}

			free(*iter);
			AppData.words.erase(iter);
			break;
		}
	}


	//전체 삭제
	if (add_score > 5)
	{
		GameProc::RemoveAllWords(TRUE);
	}

	InvalidateRect(hWnd, new RECT{ 0, 0, 640, 630 }, TRUE);
	UpdateWindow(hWnd);

	HIMC hImc;
	hImc = ImmGetContext(hWnd);
	ImmNotifyIME(hImc, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
	ImmReleaseContext(hWnd, hImc);
	SetDlgItemText(hWnd, IDC_TEXT_WORD, L"");
}

VOID GameProc::EscapeProc(HWND hWnd)
{
	ShowWindow(AppData.hGameTextBox, SW_HIDE);
	ShowWindow(AppData.hGameEnter, SW_HIDE);
	DestroyWindow(AppData.hGameTextBox);
	DestroyWindow(AppData.hGameEnter);

	AppData.bGameStop = TRUE;

	GameProc::CreateGameStopWindows(hWnd);
	InvalidateRect(hWnd, nullptr, TRUE);
	UpdateWindow(hWnd);
}

VOID GameProc::UseBombSkill(HWND hWnd)
{
	if (AppData.bomb > 0)
	{
		if (AppData.words.size() > 0)
		{
			AppData.bomb--;
			GameProc::RemoveAllWords(FALSE);
			InvalidateRect(hWnd, nullptr, TRUE);
			UpdateWindow(hWnd);
		}
	}
}

VOID GameProc::RemoveAllWords(BOOL bAddScore)
{
	for (auto iter = AppData.words.begin(); iter != AppData.words.end(); iter++)
	{
		if (bAddScore)
		{
			AppData.score += (*iter)->score;
		}

		free(*iter);
	}

	AppData.words.clear();
}