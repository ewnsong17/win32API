#include "GameApp.h"
#include "GameProc.h"

GameData AppData;

GameData::GameData()
{
	ZeroMemory(&this->hGameStart, sizeof(this->hGameStart));
	ZeroMemory(&this->hGameEnd, sizeof(this->hGameEnd));
	ZeroMemory(&this->hGameTextBox, sizeof(this->hGameTextBox));
	ZeroMemory(&this->hGameEnter, sizeof(this->hGameEnter));
	ZeroMemory(&this->hFont, sizeof(this->hFont));
	ZeroMemory(&this->hOldFont, sizeof(this->hOldFont));
}

VOID GameData::SetFont(HWND hWnd)
{
	SendMessage(hWnd, WM_SETFONT, (WPARAM)this->hFont, MAKELPARAM(TRUE, 0));
}

VOID GameProc::PaintTextImage(HWND hWnd)
{
	PAINTSTRUCT ps;

	HDC hdc = BeginPaint(hWnd, &ps);
	HDC hMemDC = CreateCompatibleDC(hdc);

	//��� ���� ����
	SetBkMode(hdc, TRANSPARENT);

	CreateBackGround(hdc, hMemDC);

	CreateText(hdc);

	//�޸� ����
	DeleteDC(hMemDC);

	//����Ʈ ����
	EndPaint(hWnd, &ps);
}

VOID GameProc::CreateBackGround(HDC &hdc, HDC &hMemDC)
{
	BITMAP bit;

	//���ȭ�� �׸���
	HBITMAP hBit = (HBITMAP)LoadImage(nullptr, L"background.jpg", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	
	//hMemDC�� �ε��� �̹��� �� �ֱ�
	GetObject(hBit, sizeof(bit), &bit);
	HBITMAP hOld = (HBITMAP)SelectObject(hMemDC, hBit);

	//���� �� ������ ī���ؼ� ���� ����
	BitBlt(hdc, 0, 0, GameApp.width, GameApp.height, hMemDC, 0, 0, SRCCOPY);

	//�޸� �� �ٽ� ���� ������ ����
	SelectObject(hMemDC, hOld);

	//���� �� ���̻� ���� ������ ������ �޸� ����
	DeleteObject(hBit);

	//�ؽ�Ʈ ��Ʈ �����ϱ�
	AppData.hOldFont = (HFONT)SelectObject(hdc, AppData.hFont);
}

VOID GameProc::CreateGameModeWindows(HWND hWnd)
{
	//���� �� �Է�â
	AppData.hGameTextBox = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"edit",
		L"�Է��ϼ���.",
		WS_CHILD | WS_VISIBLE | SW_HIDE | ES_CENTER,
		180,
		550,
		200,
		30,
		hWnd,
		(HMENU)IDC_TEXT_WORD,
		GameApp.h_inst,
		nullptr
	);

	//���� �޽��� ����â
	AppData.hGameEnter = CreateWindow(
		L"button",
		L"����",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		400,
		550,
		50,
		30,
		hWnd,
		(HMENU)IDC_BTN_ENTER,
		GameApp.h_inst,
		nullptr
	);

	//��Ʈ �ϰ� ����
	AppData.SetFont(AppData.hGameTextBox);
	AppData.SetFont(AppData.hGameEnter);
}

VOID GameProc::CreateInitialWindows(HWND hWnd)
{
	//HY����M ��Ʈ ����
	LOGFONT lf;
	ZeroMemory(&lf, sizeof(lf));
	wcscpy_s(lf.lfFaceName, L"HY����M");

	AppData.hFont = CreateFontIndirect(&lf);

	//���ӽ��� ��ư
	AppData.hGameStart = CreateWindow(
		L"button",
		L"���ӽ���",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		155,
		550,
		100,
		30,
		hWnd,
		(HMENU)IDC_BTN_START,
		GameApp.h_inst,
		nullptr
	);

	//�������� ��ư
	AppData.hGameEnd = CreateWindow(
		L"button",
		L"��������",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		355,
		550,
		100,
		30,
		hWnd,
		(HMENU)IDC_BTN_END,
		GameApp.h_inst,
		nullptr
	);

	//��Ʈ �ϰ� ����
	AppData.SetFont(AppData.hGameStart);
	AppData.SetFont(AppData.hGameEnd);
}

VOID GameProc::CreateText(HDC& hdc)
{
	if (AppData.bGameStart)
	{
		std::wstring scoreText = L"���ھ� : ";
		scoreText += std::to_wstring(AppData.score);
		scoreText += L"��";

		TextOut(hdc, 10, 570, scoreText.c_str(), wcslen(scoreText.c_str()));
		for (auto iter = AppData.words.begin(); iter != AppData.words.end(); iter++)
		{
			LPCWSTR word = (*iter)->word;
			TextOut(hdc, (*iter)->x, (*iter)->y, word, wcslen(word));
		}
	}
	else
	{
		TextOut(hdc, 260, 65, AppData.titleText, wcslen(AppData.titleText));
	}
}

LRESULT CALLBACK GameProc::WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
		case WM_CREATE:
			CreateInitialWindows(hWnd);
			break;
		case WM_DESTROY:
			DeleteObject(AppData.hFont);
			UnhookWindowsHookEx(GameApp.k_hook);
			PostQuitMessage(0);
			break;
		case WM_COMMAND:
			CmdProc(hWnd, uMessage, wParam, lParam);
			break;
		case WM_PAINT:
			PaintTextImage(hWnd);
			break;
		case WM_ERASEBKGND:
			break;
		default:
			return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}


DWORD WINAPI GameProc::GameMainThread(LPVOID lpParam)
{
	int init_time = 180;
	int add_index = 0;
	while (!AppData.bGameEnd && init_time >= 0)
	{
		init_time--;
		add_index++;
		UpdateWords(add_index);
		Sleep(500);
	}

	return 0;
}

Word::Word(int x, int y, LPCWSTR word)
{
	this->x = x;
	this->y = y;
	this->word = word;
}

VOID GameProc::UpdateWords(int& index)
{
	SendMessage(GameApp.h_wnd, WM_COMMAND, (WPARAM)IDC_UPDATE_WORD, MAKELPARAM(TRUE, 0));

	int size = AppData.words.size();
	if (size < 20 && (index % 3) == 1)
	{
		index = rand() % 5;
		SendMessage(GameApp.h_wnd, WM_COMMAND, (WPARAM)IDC_ADD_WORD, MAKELPARAM(TRUE, 0));
	}
}