#include "GameApp.h"
#include "GameProc.h"

LPCWSTR class_name = L"�ܾ���߱�";
HINSTANCE g_hInst;

INT CreateWndClass(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszcmParam, int cmdShow)
{
	g_hInst = hInstance;

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
	HWND hWnd = CreateWindow(
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

	if (hWnd)
	{
		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);
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