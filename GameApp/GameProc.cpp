#define _CRT_RAND_S
#include "GameApp.h"
#include "GameProc.h"
#include "GameData.h"

VOID GameProc::PaintTextImage(HWND hWnd)
{
	PAINTSTRUCT ps;

	HDC hdc = BeginPaint(hWnd, &ps);
	HDC hMemDC = CreateCompatibleDC(hdc);
	HDC hBackMemDC = CreateCompatibleDC(hdc);

	//��� ���� ����
	SetBkMode(hdc, TRANSPARENT);

	CreateBackGround(hdc, hMemDC, hBackMemDC);

	CreateText(hdc);

	//���� ���� �� ����
	if (!AppData.bGameStop && AppData.bGameStart)
	{
		HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
		FillRect(hdc, &AppData.end_line, hBrush);
	}

	//�޸� ����
	DeleteDC(hMemDC);
	DeleteDC(hBackMemDC);

	//����Ʈ ����
	EndPaint(hWnd, &ps);
}

VOID GameProc::CreateBackGround(HDC& hdc, HDC& hMemDC, HDC& hBackMemDC)
{
	BITMAP bit;

	//���� ���۸��� �غ�
	HBITMAP backBitMap = CreateCompatibleBitmap(hdc, GameApp.width, GameApp.height);
	HBITMAP hOldBitMap = (HBITMAP)SelectObject(hBackMemDC, backBitMap);

	//���ȭ�� �׸���
	HBITMAP hBit = (HBITMAP)LoadImage(nullptr, L"background.jpg", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	//hMemDC�� �ε��� �̹��� �� �ֱ�
	GetObject(hBit, sizeof(bit), &bit);
	HBITMAP hOld = (HBITMAP)SelectObject(hMemDC, hBit);

	//���� ���۸��� ���� �� �����ͼ� �ε��ϱ�
	BitBlt(hBackMemDC, 0, 0, GameApp.width, GameApp.height, hMemDC, 0, 0, SRCCOPY);

	//���� ���� ȭ�鿡 �׷��� ó���ϱ�
	BitBlt(hdc, 0, 0, GameApp.width, GameApp.height, hBackMemDC, 0, 0, SRCCOPY);

	//�޸� �� �ٽ� ���� ������ ����
	SelectObject(hBackMemDC, hOld);

	//���� �� ���̻� ���� ������ ������ �޸� ����
	DeleteObject(hBit);

	//�ؽ�Ʈ ��Ʈ �����ϱ�
	AppData.hOldFont = (HFONT)SelectObject(hdc, AppData.hFont);
}

VOID GameProc::CreateGameEndWindows(HWND hWnd)
{
	//���� �ٽ��ϱ� ��ư
	AppData.hGameStart = CreateWindow(
		L"button",
		L"�ٽ��ϱ�",
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

VOID GameProc::CreateGameStopWindows(HWND hWnd)
{
	//���� �̾��ϱ� ��ư
	AppData.hGameStart = CreateWindow(
		L"button",
		L"�̾��ϱ�",
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

VOID GameProc::CreateGameModeWindows(HWND hWnd)
{
	//���� �� �Է�â
	AppData.hGameTextBox = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"edit",
		L"�Է��ϼ���.",
		WS_CHILD | WS_VISIBLE | SW_HIDE | ES_CENTER,
		180,
		555,
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
		555,
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

	//���� ��Ŀ��
	SetFocus(AppData.hGameTextBox);
}

VOID GameProc::CreateInitialWindows(HWND hWnd)
{
	//HY�߰�� ��Ʈ ����
	LOGFONT lf;
	ZeroMemory(&lf, sizeof(lf));
	wcscpy_s(lf.lfFaceName, L"HY�߰��");

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

VOID GameProc::CreateGameToolTipText(HDC& hdc)
{
	//�ܰ�
	SetTextColor(hdc, RGB(125, 0, 125));
	std::wstring levelText = L"";
	levelText += std::to_wstring(AppData.level);
	levelText += L"�ܰ�";

	TextOut(hdc, 12, 550, levelText.c_str(), wcslen(levelText.c_str()));

	//���ھ�
	SetTextColor(hdc, RGB(125, 0, 255));
	std::wstring scoreText = L"���ھ� : ";
	scoreText += std::to_wstring(AppData.score);
	scoreText += L"��";

	TextOut(hdc, 10, 570, scoreText.c_str(), wcslen(scoreText.c_str()));

	//��ź
	SetTextColor(hdc, RGB(100, 0, 0));
	std::wstring bombText = L"��ź (F1)";
	for (int i = 0; i < AppData.bomb; i++)
	{
		bombText += L"  ��";
	}
	TextOut(hdc, 490, 550, bombText.c_str(), wcslen(bombText.c_str()));

	//������
	SetTextColor(hdc, RGB(0, 255, 100));
	std::wstring lifeText = L"������   ";
	for (int i = 0; i < AppData.life; i++)
	{
		lifeText += L"  ��";
	}
	TextOut(hdc, 491, 570, lifeText.c_str(), wcslen(lifeText.c_str()));
}

VOID GameProc::CreateGameResumeEndText(HDC& hdc)
{
	std::wstring scoreText;
	if (AppData.bGameStop)
	{
		scoreText = L"�Ͻ����� �����Դϴ�.  ";
	}
	else
	{
		scoreText = L"������ ����Ǿ����ϴ�.  ";
	}

	scoreText += std::to_wstring(AppData.level);
	scoreText += L"�ܰ�. �� ���ھ�: ";
	scoreText += std::to_wstring(AppData.score);
	scoreText += L"��";

	TextOut(hdc, 175, 65, scoreText.c_str(), wcslen(scoreText.c_str()));
}

VOID GameProc::CreateGameWordListText(HDC& hdc)
{
	for (auto iter = AppData.words.begin(); iter != AppData.words.end(); iter++)
	{
		LPCWSTR word = (*iter)->word;
		if ((*iter)->weight <= 3)
		{
			//���� �� ����
			SetTextColor(hdc, RGB(0, 0, 255));
		}
		else
		{
			SetTextColor(hdc, RGB(0, 0, 0));
		}
		TextOut(hdc, (*iter)->x, (*iter)->y, word, wcslen(word));
	}
}

VOID GameProc::CreateText(HDC& hdc)
{
	if (AppData.bGameStop || AppData.bGameEnd)
	{
		GameProc::CreateGameResumeEndText(hdc);
	}
	else if (AppData.bGameStart)
	{
		GameProc::CreateGameToolTipText(hdc);
		GameProc::CreateGameWordListText(hdc);
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
		case WM_CHAR:
			if (wParam == 1)
			{
				SendMessage(hWnd, EM_SETSEL, 0, -1);
				return 1;
			}
			break;
		default:
			return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}


DWORD WINAPI GameProc::GameMainThread(LPVOID lpParam)
{
	unsigned int add_index = 0;
	unsigned int next_index = 0;
	while (!AppData.bGameEnd)
	{
		if (!AppData.bGameStop)
		{
			add_index++;
			UpdateWords(add_index, next_index);
		}

		Sleep(1000);
	}

	return 0;
}

VOID GameProc::UpdateWords(unsigned int& index, unsigned int& next_index)
{
	int size = AppData.words.size();

	if (size < 20 + AppData.level && index >= next_index)
	{
		index = 0;

		rand_s(&next_index);
		next_index %= (AppData.level_cool_l[(long long) AppData.level - 1] - AppData.level_cool_f[(long long) AppData.level - 1] + 1); // 0 ~ 3
		next_index += AppData.level_cool_f[(long long) AppData.level - 1]; // 3 ~ 6

		float count = AppData.level_count[(long long)AppData.level - 1];

		if (ceilf(count) == count)
		{
			for (int i = 0; i < count; i++)
			{
				Word word_ = AppData.GetNextWord();
				unsigned int x;
				rand_s(&x);
				Word* word = new Word(35 + (x % 515) - wcslen(word_.word), (i == 0 ? 5 : 55), word_.word, word_.score, word_.weight);
				AppData.words.push_back(word);
			}
		}
		else
		{
			unsigned int r_cnt;
			int cnt = round(count);

			rand_s(&r_cnt);

			r_cnt %= cnt;

			for (int i = 0; i < r_cnt + 1; i++)
			{
				Word word_ = AppData.GetNextWord();
				unsigned int x;
				rand_s(&x);
				Word* word = new Word(35 + (x % 515) - wcslen(word_.word), (i == 0 ? 5 : 55), word_.word, word_.score, word_.weight);
				AppData.words.push_back(word);
			}
		}
	}

	SendMessage(GameApp.h_wnd, WM_COMMAND, (WPARAM)IDC_UPDATE_WORD, MAKELPARAM(TRUE, 0));
}