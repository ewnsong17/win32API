#include "GameProc.h"

VOID GameProc::CmdProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
		case IDC_BTN_START:
		{
			DestroyWindow(AppData.hGameStart);
			DestroyWindow(AppData.hGameEnd);

			AppData.bGameStart = true;

			InvalidateRect(hWnd, nullptr, TRUE);

			GameProc::CreateGameModeWindows(hWnd);

			DWORD threadId = 0;
			DWORD threadParam = 0;
			CreateThread(nullptr, 0, GameMainThread, &threadParam, 0, &threadId);
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
			for (auto iter = AppData.words.begin(); iter != AppData.words.end(); iter++)
			{
				(*iter)->y += 15;

				if ((*iter)->y > 540)
				{
					AppData.bGameEnd = TRUE;
					if (IDOK == MessageBox(hWnd, L"게임이 종료되었습니다.", L"알림", MB_OK))
					{
						SendMessage(hWnd, WM_DESTROY, wParam, lParam);
					}
					break;
				}
			}

			if (!AppData.bGameEnd)
			{
				InvalidateRect(hWnd, nullptr, TRUE);
			}
			break;
		}

		case IDC_ADD_WORD:
		{
			Word* word = new Word(35 + (rand() % 531), 20, AppData.word_list[rand() % AppData.word_list.size()]);
			AppData.words.push_back(word);
			InvalidateRect(hWnd, nullptr, FALSE);
			break;
		}
	}
}

VOID GameProc::EnterTextProc(HWND hWnd)
{
	TCHAR buff[255];
	LPWSTR text = (LPWSTR)buff;

	GetWindowText(AppData.hGameTextBox, text, 1024);

	for (auto iter = AppData.words.begin(); iter != AppData.words.end(); iter++)
	{
		if (wcscmp(text, (*iter)->word) == 0)
		{
			free(*iter);
			AppData.words.erase(iter);
			break;
		}
	}

	InvalidateRect(hWnd, nullptr, TRUE);
	SetDlgItemText(hWnd, IDC_TEXT_WORD, L"");
}