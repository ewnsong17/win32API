#include "GameProc.h"
#include "GameApp.h"
#include "CmdProc.h"

HWND hGameStart = {};
HWND hGameEnd = {};
HWND hGameTextBox = {};
HWND hGameEnter = {};
HFONT hFont = {}, oldFont = {};
LPCWSTR titleText = L"�ܾ� ���߱� ����";
BOOL IsGameStarted = false;

VOID CreateBackGround(HWND hWnd)
{
	PAINTSTRUCT ps;
	BITMAP bit;

	HDC hdc = BeginPaint(hWnd, &ps);
	HDC hMemDC = CreateCompatibleDC(hdc);

	//���ȭ�� �׸���
	HBITMAP hBit = (HBITMAP)LoadImage(NULL, L"background.jpg", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBit, sizeof(bit), &bit);
	HBITMAP hOld = (HBITMAP)SelectObject(hMemDC, hBit);
	BitBlt(hdc, 0, 0, 640, 640, hMemDC, 0, 0, SRCCOPY);
	SelectObject(hMemDC, hOld);
	DeleteObject(hBit);

	//�ؽ�Ʈ ��Ʈ �����ϱ�
	oldFont = (HFONT)SelectObject(hdc, hFont);

	//�۾� �׸���
	if (!IsGameStarted)
	{
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 245, 65, titleText, wcslen(titleText));
	}

	DeleteDC(hMemDC);
	EndPaint(hWnd, &ps);
}

VOID CreateSystemClasses(HWND hWnd)
{
	//��Ʈ �ε��ϱ�
	LOGFONT lf;
	ZeroMemory(&lf, sizeof(lf));
	wcscpy_s(lf.lfFaceName, L"HY����M");
	hFont = CreateFontIndirect(&lf);

	//���ӽ���
	hGameStart = CreateWindow(
		L"button",
		L"���ӽ���",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		155,
		550,
		100,
		30,
		hWnd,
		(HMENU)IDC_BUTTON1,
		g_hInst,
		nullptr
	);

	//��ư ��Ʈ �����ϱ�
	SendMessage(hGameStart, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

	//��������
	hGameEnd = CreateWindow(
		L"button",
		L"��������",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		355,
		550,
		100,
		30,
		hWnd,
		(HMENU)IDC_BUTTON2,
		g_hInst,
		nullptr
	);

	//��ư ��Ʈ �����ϱ�
	SendMessage(hGameEnd, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

	//���� �� �Է�â
	hGameTextBox = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"Edit",
		L"�Է��ϼ���.",
		WS_CHILD | SW_HIDE | ES_CENTER,
		180,
		550,
		200,
		30,
		hWnd,
		(HMENU)IDC_TEXTBOX1,
		g_hInst,
		nullptr
	);

	//�ؽ�Ʈ ��Ʈ �����ϱ�
	SendMessage(hGameTextBox, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

	//���� �޽��� ����â
	hGameEnter = CreateWindow(
		L"button",
		L"����",
		WS_CHILD | BS_PUSHBUTTON,
		400,
		550,
		50,
		30,
		hWnd,
		(HMENU)IDC_BUTTON3,
		g_hInst,
		nullptr
	);

	//��ư ��Ʈ �����ϱ�
	SendMessage(hGameEnter, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
		case WM_CREATE: // ���α׷� ���� �� �����ϴ� ���
			CreateSystemClasses(hWnd);
			break;
		case WM_DESTROY: // ���α׷� ���� �� �����ϴ� ���
			//��Ʈ ���� �����ϱ�
			DeleteObject(hFont);
			//Ű���� �ν� �����ϱ�
			UnhookWindowsHookEx(_k_hook);
			PostQuitMessage(0);
			break;
		case WM_COMMAND:
			CommandProc(hWnd, uMessage, wParam, lParam);
			break;
		case WM_PAINT:
			CreateBackGround(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT)lParam;

	if (wParam == WM_KEYDOWN && nCode == HC_ACTION && key->vkCode == 13 && IsGameStarted)
	{
		SetDlgItemText(g_h_wnd, IDC_TEXTBOX1, L"");
	}
	return CallNextHookEx(nullptr, nCode, wParam, lParam);
}