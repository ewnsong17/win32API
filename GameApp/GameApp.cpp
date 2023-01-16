#include "GameApp.h"
#include "GameProc.h"

LPCWSTR class_name = L"단어맞추기";
HINSTANCE g_hInst;
HWND g_h_wnd;
HHOOK _k_hook;
BOOL bEndGame = FALSE;

INT CreateWndClass(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszcmParam, int cmdShow)
{
	g_hInst = hInstance;
	_k_hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, nullptr, 0);

	//윈도우 프로세스 등록
	WNDCLASSEX wnd_class;
	wnd_class.cbSize = sizeof(WNDCLASSEXW);
	wnd_class.cbClsExtra = 0;
	wnd_class.cbWndExtra = 0;
	wnd_class.hbrBackground = HBRUSH(0x10); // =int, RGB 값 전달하여 색깔 처리
	wnd_class.hCursor = LoadCursorW(hInstance, IDC_ARROW); // 마우스 커서 기본 값
	wnd_class.hIcon = LoadIconW(hInstance, IDI_APPLICATION); // 아이콘 기본 값
	wnd_class.hIconSm = LoadIconW(hInstance, IDI_APPLICATION);
	wnd_class.hInstance = hInstance;
	wnd_class.lpfnWndProc = WndProc;
	wnd_class.lpszClassName = class_name;
	wnd_class.lpszMenuName = NULL;
	wnd_class.style = CS_HREDRAW | CS_VREDRAW; // 클라이언트 창 크기 변경시 다시 그리는 옵션

	RegisterClassEx(&wnd_class);

	//윈도우 창 생성
	g_h_wnd = CreateWindow(
		class_name,
		class_name,
		WS_SYSMENU | WS_OVERLAPPED, // 다른 창과 겹칠 수 있는 옵션
		CW_USEDEFAULT, // x
		CW_USEDEFAULT, // y
		640,// width,
		640,// height,
		nullptr,//HWND(0),
		nullptr,//HMENU(0),
		hInstance,
		nullptr
	);

	if (g_h_wnd)
	{
		ShowWindow(g_h_wnd, SW_SHOWDEFAULT);
		UpdateWindow(g_h_wnd);
		MSG msg;

		while (GetMessage(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return (int)msg.wParam;
	}
	else
	{
		MessageBox(nullptr, L"윈도우 창을 열지 못했습니다.", L"오류", MB_OK);
	}

	return 0;
}

VOID CreateNewWord(HWND hWnd, int size)
{
	SendMessage(hWnd, WM_COMMAND, (WPARAM)IDC_MAKE_WORD, MAKELPARAM(TRUE, 0));
}

VOID UpdateWordList(int &index)
{
	int size = words_.size();
	SendMessage(g_h_wnd, WM_COMMAND, (WPARAM)IDC_UPDATE_WORD, MAKELPARAM(TRUE, 0));
	if (size < 20 && (index % 3) == 1)
	{
		index = rand() % 5;
		SendMessage(g_h_wnd, WM_COMMAND, (WPARAM)IDC_MAKE_WORD, MAKELPARAM(TRUE, 0));
	}
}

DWORD WINAPI WordThread(LPVOID lpParam)
{
	int timer = 180;
	int index = 0;
	while (!bEndGame && timer >= 0)
	{
		timer--;
		index++;
		UpdateWordList(index);
		Sleep(1000);
	}

	return 0;
}