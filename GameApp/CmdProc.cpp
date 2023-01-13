#include "CmdProc.h"
#include "GameProc.h"

VOID CommandProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		case IDC_BUTTON1:
			//���̵��� ����ּ���~~�� ���߿��ϰ� �ϴ� ���Ӻ���?
			ShowWindow(hGameStart, SW_HIDE);
			ShowWindow(hGameEnd, SW_HIDE);
			IsGameStarted = true;
			InvalidateRect(hWnd, nullptr, TRUE);
			break;
		case IDC_BUTTON2:
			if (IDYES == MessageBox(hWnd, L"������ �����Ͻðڽ��ϱ�?", L"�˸�", MB_YESNO))
			{
				SendMessage(hWnd, WM_DESTROY, wParam, lParam);
			}
			break;
	}
}