#include "GameProc.h"
#include "GameApp.h"
#include "CmdProc.h"

HWND hGameStart = { 0 };
HWND hGameEnd = { 0 };
HFONT hFont = {}, oldFont = {};
LPCWSTR titleText = L"단어 맞추기 게임";
BOOL IsGameStarted = false;

VOID CreateBackGround(HWND hWnd)
{
	PAINTSTRUCT ps;
	BITMAP bit;

	HDC hdc = BeginPaint(hWnd, &ps);
	HDC hMemDC = CreateCompatibleDC(hdc);

	//배경화면 그리기
	HBITMAP hBit = (HBITMAP)LoadImage(NULL, L"background.jpg", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBit, sizeof(bit), &bit);
	HBITMAP hOld = (HBITMAP)SelectObject(hMemDC, hBit);
	BitBlt(hdc, 0, 0, 640, 640, hMemDC, 0, 0, SRCCOPY);
	SelectObject(hMemDC, hOld);
	DeleteObject(hBit);

	//텍스트 폰트 지정하기
	oldFont = (HFONT)SelectObject(hdc, hFont);

	//글씨 그리기
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
	//폰트 로딩하기
	LOGFONT lf;
	ZeroMemory(&lf, sizeof(lf));
	wcscpy_s(lf.lfFaceName, L"HY엽서M");
	hFont = CreateFontIndirect(&lf);

	//게임시작
	hGameStart = CreateWindow(
		L"button",
		L"게임시작",
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

	//버튼 폰트 지정하기
	SendMessage(hGameStart, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

	std::cout << "btn1 : " << hGameStart << '\n';

	//게임종료
	hGameEnd = CreateWindow(
		L"button",
		L"게임종료",
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

	//버튼 폰트 지정하기
	SendMessage(hGameEnd, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_CREATE: // 프로그램 실행 시 도달하는 헤더
		CreateSystemClasses(hWnd);
		break;
	case WM_DESTROY: // 프로그램 종료 시 도달하는 헤더
		//폰트 설정 해제하기
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