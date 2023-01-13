#include "GameProc.h"
#include "GameApp.h"
#include "CmdProc.h"

HWND hGameStart = { 0 };
HWND hGameEnd = { 0 };
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

	std::cout << "btn1 : " << hGameStart << '\n';

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