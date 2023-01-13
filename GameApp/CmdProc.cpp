#include "CmdProc.h"
#include "GameProc.h"
#include "GameApp.h"

VOID CommandProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
		case IDC_BUTTON1:
			//���̵��� ����ּ���~~�� ���߿��ϰ� �ϴ� ���Ӻ���?

			IsGameStarted = true;

			ShowWindow(hGameStart, SW_HIDE);
			ShowWindow(hGameEnd, SW_HIDE);

			ShowWindow(hGameTextBox, SW_SHOW);
			ShowWindow(hGameEnter, SW_SHOW);

			InvalidateRect(hWnd, nullptr, TRUE);
			break;
		case IDC_BUTTON2:
			if (IDYES == MessageBox(hWnd, L"������ �����Ͻðڽ��ϱ�?", L"�˸�", MB_YESNO))
			{
				SendMessage(hWnd, WM_DESTROY, wParam, lParam);
			}
			break;
		case IDC_TEXTBOX1:
			switch (HIWORD(wParam))
			{
				case EN_SETFOCUS:
					SetDlgItemText(hWnd, IDC_TEXTBOX1, L"");
					break;
			}
			break;
		case IDC_BUTTON3:
			SetDlgItemText(hWnd, IDC_TEXTBOX1, L"");
			break;
	}
}