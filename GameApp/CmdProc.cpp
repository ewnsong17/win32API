#include "CmdProc.h"
#include "GameProc.h"

VOID CommandProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		case IDC_BUTTON1:
			//난이도를 골라주세요~~는 나중에하고 일단 게임부터?
			ShowWindow(hGameStart, SW_HIDE);
			ShowWindow(hGameEnd, SW_HIDE);
			IsGameStarted = true;
			InvalidateRect(hWnd, nullptr, TRUE);
			break;
		case IDC_BUTTON2:
			if (IDYES == MessageBox(hWnd, L"게임을 종료하시겠습니까?", L"알림", MB_YESNO))
			{
				SendMessage(hWnd, WM_DESTROY, wParam, lParam);
			}
			break;
	}
}