#include "CmdProc.h"
#include "GameProc.h"

VOID CommandProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		case IDC_BUTTON1:
			//���̵��� ����ּ���~~�� ���߿��ϰ� �ϴ� ���Ӻ���?
			break;
		case IDC_BUTTON2:
			if (IDYES == MessageBox(nullptr, L"������ �����Ͻðڽ��ϱ�?", L"�˸�", MB_YESNO))
			{
				SendMessage(hWnd, WM_DESTROY, wParam, lParam);
			}
			break;
	}
}