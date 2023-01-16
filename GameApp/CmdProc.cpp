#include "CmdProc.h"
#include "GameProc.h"
#include "GameApp.h"

HANDLE hThread;

VOID EnterTextProc(HWND hWnd)
{
	TCHAR buff[255];
	LPWSTR text = (LPWSTR)buff;

	GetWindowText(hGameTextBox, text, 1024);

	for (auto iter = words_.begin(); iter != words_.end(); iter++)
	{
		if (wcscmp(text, (*iter)->word) == 0)
		{
			free(*iter);
			words_.erase(iter);
			break;
		}
	}

	InvalidateRect(hWnd, nullptr, TRUE);

	SetDlgItemText(hWnd, IDC_TEXT_WORD, L"");
}

VOID CommandProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
		case IDC_BTN_START:
		{
			//난이도를 골라주세요~~는 나중에하고 일단 게임부터?

			bGameStarted = TRUE;

			ShowWindow(hGameStart, SW_HIDE);
			ShowWindow(hGameEnd, SW_HIDE);

			ShowWindow(hGameTextBox, SW_SHOW);
			ShowWindow(hGameEnter, SW_SHOW);

			InvalidateRect(hWnd, nullptr, TRUE);

			DWORD threadId = 0;
			DWORD threadParam = 0;
			hThread = CreateThread(nullptr, 0, WordThread, &threadParam, 0, &threadId);
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
			switch (HIWORD(wParam))
			{
				case EN_SETFOCUS:
					SetDlgItemText(hWnd, IDC_TEXT_WORD, L"");
					break;
			}
			break;
		}
		case IDC_BTN_ENTER:
		{
			EnterTextProc(hWnd);
			break;
		}
		case IDC_MAKE_WORD:
		{

			HDC hdc = GetDC(g_h_wnd);

			//단어 추가
			Word* word = new Word(35 + (rand() % 531), 20, false, word_list[rand() % word_list.size()]);
			words_.push_back(word);
			InvalidateRect(hWnd, nullptr, FALSE);

			break;
		}
		case IDC_UPDATE_WORD:
		{
			for (auto iter = words_.begin(); iter != words_.end(); iter++)
			{
				(*iter)->y += 15;

				if ((*iter)->y > 540)
				{
					bEndGame = true;
					if (IDOK == MessageBox(hWnd, L"게임이 종료되었습니다.", L"알림", MB_OK))
					{
						SendMessage(hWnd, WM_DESTROY, wParam, lParam);
					}
					break;
				}
			}

			if (!bEndGame)
			{
				InvalidateRect(hWnd, nullptr, TRUE);
			}
			break;
		}
	}
}