#pragma once
#include <Windows.h>
#include <time.h>

class GameAppWindow
{
public:
	HINSTANCE h_inst;
	HHOOK k_hook;
	WNDCLASSEX wnd_class;
	HWND h_wnd;
	LPCWSTR class_name = L"단어게임";
	INT width = 640, height = 640;
	MSG call_msg;

	GameAppWindow();
	VOID RegisterWndClass(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszcmParam, int cmdShow);
	VOID CreateWndWindow();
	INT ShowWndWindow();
	static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
};

extern GameAppWindow GameApp;