#include "GameApp.h"
#include "GameProc.h"

LPCWSTR class_name = L"�ܾ���߱�";
LPCWSTR word_list[] = {L"���", L"�ٳ���", L"��"};
UINT word_count = 0;
HINSTANCE g_hInst;
HWND g_h_wnd;
HHOOK _k_hook;

INT CreateWndClass(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszcmParam, int cmdShow)
{
	g_hInst = hInstance;
	_k_hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, nullptr, 0);

	//������ ���μ��� ���
	WNDCLASSEX wnd_class;
	wnd_class.cbSize = sizeof(WNDCLASSEXW);
	wnd_class.cbClsExtra = 0;
	wnd_class.cbWndExtra = 0;
	wnd_class.hbrBackground = HBRUSH(0x10); // =int, RGB �� �����Ͽ� ���� ó��
	wnd_class.hCursor = LoadCursorW(hInstance, IDC_ARROW); // ���콺 Ŀ�� �⺻ ��
	wnd_class.hIcon = LoadIconW(hInstance, IDI_APPLICATION); // ������ �⺻ ��
	wnd_class.hIconSm = LoadIconW(hInstance, IDI_APPLICATION);
	wnd_class.hInstance = hInstance;
	wnd_class.lpfnWndProc = WndProc;
	wnd_class.lpszClassName = class_name;
	wnd_class.lpszMenuName = NULL;
	wnd_class.style = CS_HREDRAW | CS_VREDRAW; // Ŭ���̾�Ʈ â ũ�� ����� �ٽ� �׸��� �ɼ�

	RegisterClassEx(&wnd_class);

	//������ â ����
	g_h_wnd = CreateWindow(
		class_name,
		class_name,
		WS_SYSMENU | WS_OVERLAPPED, // �ٸ� â�� ��ĥ �� �ִ� �ɼ�
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
		MessageBox(nullptr, L"������ â�� ���� ���߽��ϴ�.", L"����", MB_OK);
	}

	return 0;
}

VOID UpdateWordList()
{
	if (word_count < 3)
	{

	}
}

DWORD WINAPI WordThread(LPVOID lpParam)
{
	int timer = 60;
	while (timer >= 0)
	{
		timer--;
		UpdateWordList();
		Sleep(1000);
	}

	return 0;
}