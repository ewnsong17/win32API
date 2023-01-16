#define _CRT_RAND_S
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
	HDC hBackMemDC = CreateCompatibleDC(hdc);

	//배경 투명 설정
	SetBkMode(hdc, TRANSPARENT);

	//글자 색 설정
	SetTextColor(hdc, RGB(0, 0, 255));

	CreateBackGround(hdc, hMemDC, hBackMemDC);

	CreateText(hdc);

	//메모리 해제
	DeleteDC(hMemDC);
	DeleteDC(hBackMemDC);

	//페인트 해제
	EndPaint(hWnd, &ps);
}

VOID GameProc::CreateBackGround(HDC& hdc, HDC& hMemDC, HDC& hBackMemDC)
{
	BITMAP bit;

	//더블 버퍼링에 준비
	HBITMAP backBitMap = CreateCompatibleBitmap(hdc, GameApp.width, GameApp.height);
	HBITMAP hOldBitMap = (HBITMAP)SelectObject(hBackMemDC, backBitMap);

	//배경화면 그리기
	HBITMAP hBit = (HBITMAP)LoadImage(nullptr, L"background.jpg", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	//hMemDC에 로딩한 이미지 값 넣기
	GetObject(hBit, sizeof(bit), &bit);
	HBITMAP hOld = (HBITMAP)SelectObject(hMemDC, hBit);

	//더블 버퍼링에 넣은 값 꺼내와서 로딩하기
	BitBlt(hBackMemDC, 0, 0, GameApp.width, GameApp.height, hMemDC, 0, 0, SRCCOPY);

	//이후 실제 화면에 그래픽 처리하기
	BitBlt(hdc, 0, 0, GameApp.width, GameApp.height, hBackMemDC, 0, 0, SRCCOPY);

	//메모리 값 다시 이전 값으로 변경
	SelectObject(hBackMemDC, hOld);

	//변경 후 더이상 쓸모 없어진 데이터 메모리 해제
	DeleteObject(hBit);

	//텍스트 폰트 변경하기
	AppData.hOldFont = (HFONT)SelectObject(hdc, AppData.hFont);
}

VOID GameProc::CreateGameModeWindows(HWND hWnd)
{
	//게임 시 입력창
	AppData.hGameTextBox = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"edit",
		L"입력하세요.",
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

	//게임 메시지 전송창
	AppData.hGameEnter = CreateWindow(
		L"button",
		L"전송",
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

	//폰트 일괄 지정
	AppData.SetFont(AppData.hGameTextBox);
	AppData.SetFont(AppData.hGameEnter);

	//오토 포커스
	SetFocus(AppData.hGameTextBox);
}

VOID GameProc::CreateInitialWindows(HWND hWnd)
{
	//HY엽서M 폰트 지정
	LOGFONT lf;
	ZeroMemory(&lf, sizeof(lf));
	wcscpy_s(lf.lfFaceName, L"HY엽서M");

	AppData.hFont = CreateFontIndirect(&lf);

	//게임시작 버튼
	AppData.hGameStart = CreateWindow(
		L"button",
		L"게임시작",
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

	//게임종료 버튼
	AppData.hGameEnd = CreateWindow(
		L"button",
		L"게임종료",
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

	//폰트 일괄 지정
	AppData.SetFont(AppData.hGameStart);
	AppData.SetFont(AppData.hGameEnd);
}

VOID GameProc::CreateText(HDC& hdc)
{
	if (AppData.bGameStart)
	{
		std::wstring scoreText = L"스코어 : ";
		scoreText += std::to_wstring(AppData.score);
		scoreText += L"점";

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
	int init_time = 180;
	unsigned int add_index = 0;
	while (!AppData.bGameEnd && init_time >= 0)
	{
		init_time--;
		add_index++;
		UpdateWords(add_index);
		Sleep(1000);
	}

	return 0;
}

Word::Word(int x, int y, LPCWSTR word, int score)
{
	this->x = x;
	this->y = y;
	this->word = word;
	this->score = score;
}

VOID GameProc::UpdateWords(unsigned int& index)
{
	int size = AppData.words.size();
	if (size < 20 && (index % 3) == 1)
	{
		rand_s(&index);

		index %= 5;

		unsigned int num;
		rand_s(&num);

		Word word_ = AppData.word_list[num % AppData.word_list.size()];

		unsigned int x;
		rand_s(&x);
		Word* word = new Word(35 + (x % 521), 20, word_.word, word_.score);
		AppData.words.push_back(word);
	}

	SendMessage(GameApp.h_wnd, WM_COMMAND, (WPARAM)IDC_UPDATE_WORD, MAKELPARAM(TRUE, 0));
}