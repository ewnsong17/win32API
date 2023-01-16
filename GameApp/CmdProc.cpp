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

			free(*iter);
			AppData.words.erase(iter);
			break;
		}
	}


	//전체 삭제
	if (add_score > 5)
	{
		for (auto iter = AppData.words.begin(); iter != AppData.words.end(); iter++)
		{
			AppData.score += (*iter)->score;
			free(*iter);
		}

		AppData.words.clear();
	}

	InvalidateRect(hWnd, nullptr, TRUE);

	HIMC hImc;
	hImc = ImmGetContext(hWnd);
	ImmNotifyIME(hImc, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
	ImmReleaseContext(hWnd, hImc);
	SetDlgItemText(hWnd, IDC_TEXT_WORD, L"");
}