#include <Windows.h>


LRESULT CALLBACK wnd_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProcW(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszcmParam, int cmdShow)
{
	LPCWSTR name = L"test";

	WNDCLASSEXW wnd_class; // ������ Ŭ����(â) ��ü
	wnd_class.cbSize = sizeof(WNDCLASSEXW);
	wnd_class.cbClsExtra = 0;
	wnd_class.cbWndExtra = 0;
	wnd_class.hbrBackground = HBRUSH(0x10); // =int, RGB �� �����Ͽ� ���� ó��
	wnd_class.hCursor = LoadCursorW(hInstance, IDC_ARROW); // ���콺 Ŀ�� �⺻ ��
	wnd_class.hIcon = LoadIconW(hInstance, IDI_APPLICATION); // ������ �⺻ ��
	wnd_class.hIconSm = LoadIconW(hInstance, IDI_APPLICATION);
	wnd_class.hInstance = hInstance;
	wnd_class.lpfnWndProc = wnd_proc;
	wnd_class.lpszClassName = name;
	wnd_class.lpszMenuName = NULL;
	wnd_class.style = CS_HREDRAW | CS_VREDRAW; // Ŭ���̾�Ʈ â ����� �ٽ� �׸��� �ɼ�

	RegisterClassExW(&wnd_class); // ������ Ŭ���� ���(����) �Լ�

	//RegisterClass ���Ŀ� �ؾ� �� �����
	HWND hWnd = CreateWindowExW(
		0,
		name,
		name,
		WS_OVERLAPPEDWINDOW, // �ٸ� â�� ��ĥ �� �ִ� �ɼ� (https://learn.microsoft.com/ko-kr/windows/win32/winmsg/window-styles)
		CW_USEDEFAULT, // �ش� ������ �⺻ �� ���
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,//HWND(0),
		NULL,//HMENU(0),
		hInstance,
		NULL
	);

	if (hWnd != NULL)
	{
		ShowWindow(hWnd, SW_SHOWDEFAULT); // Cmdâ Show Default������ ����
		UpdateWindow(hWnd);
		MSG msg;

		while (GetMessageW(&msg, NULL, 0, 0) != 0)
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		return (int)msg.wParam;
	}
	else
	{
		MessageBoxW(NULL, L"������ â�� ���� ���߽��ϴ�.", L"����", 0);
	}

	return 0;
}