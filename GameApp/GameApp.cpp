#include "GameApp.h"
#include "GameProc.h"

#ifndef NDEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") 
#endif

GameAppWindow GameApp;

GameAppWindow::GameAppWindow()
{
	ZeroMemory(&this->h_inst, sizeof(this->h_inst));
	ZeroMemory(&this->k_hook, sizeof(this->k_hook));
	ZeroMemory(&this->wnd_class, sizeof(this->wnd_class));
	ZeroMemory(&this->h_wnd, sizeof(this->h_wnd));
	ZeroMemory(&this->call_msg, sizeof(this->call_msg));

	k_hook = SetWindowsHookEx(WH_KEYBOARD_LL, GameAppWindow::KeyboardProc, nullptr, 0);
}

VOID GameAppWindow::RegisterWndClass(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszcmParam, int cmdShow)
{
	this->wnd_class.cbSize = sizeof(WNDCLASSEX);
	this->wnd_class.cbClsExtra = 0;
	this->wnd_class.cbWndExtra = 0;
	this->wnd_class.hbrBackground = HBRUSH(0x10);
	this->wnd_class.hCursor = LoadCursor(hInstance, IDC_ARROW);
	this->wnd_class.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	this->wnd_class.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
	this->wnd_class.hInstance = hInstance;
	this->wnd_class.lpfnWndProc = GameProc::WndProc;
	this->wnd_class.lpszClassName = this->class_name;
	this->wnd_class.lpszMenuName = nullptr;
	this->wnd_class.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&this->wnd_class);
}

VOID GameAppWindow::CreateWndWindow()
{
	this->h_wnd = CreateWindow(
		this->class_name,
		this->class_name,
		WS_SYSMENU | WS_OVERLAPPED,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		this->width,
		this->height,
		nullptr,
		nullptr,
		this->h_inst,
		nullptr
	);
}

INT GameAppWindow::ShowWndWindow()
{
	if (this->h_wnd)
	{
		ShowWindow(this->h_wnd, SW_SHOWDEFAULT);
		UpdateWindow(this->h_wnd);

		while (GetMessage(&call_msg, nullptr, 0, 0))
		{
			TranslateMessage(&call_msg);
			DispatchMessage(&call_msg);
		}

		return (int)call_msg.wParam;
	}
	else
	{
		MessageBox(nullptr, L"게임을 실행하지 못했습니다.", L"오류", MB_OK);
	}
	return 0;
}

LRESULT CALLBACK GameAppWindow::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT)lParam;
	if (wParam == WM_KEYDOWN && nCode == HC_ACTION && GetForegroundWindow() == GameApp.h_wnd)
	{
		switch (key->vkCode)
		{
			case VK_RETURN:
				GameProc::EnterTextProc(GameApp.h_wnd);
				break;
			case VK_ESCAPE:
				GameProc::EscapeProc(GameApp.h_wnd);
				break;
			case VK_F1:
				GameProc::UseBombSkill(GameApp.h_wnd);
				break;
			default:
//				std::cout << "input key : " << key->vkCode << '\n';
				break;
		}
	}
	return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

INT APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszcmParam, int cmdShow)
{
	srand((unsigned int)time(NULL));

	GameApp.RegisterWndClass(hInstance, hPrevInstance, lpszcmParam, cmdShow);
	GameApp.CreateWndWindow();

	return GameApp.ShowWndWindow();
}