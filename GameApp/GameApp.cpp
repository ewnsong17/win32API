#include <Windows.h>
#include <tchar.h>

constexpr auto IDC_BUTTON1 = 1003;
constexpr auto IDC_COMBOBOX1 = 1004;
constexpr auto IDC_COMBOSTRING1 = 1005;
constexpr auto IDC_COMBOSTRING2 = 1006;
constexpr auto IDC_COMBOSTRING3 = 1007;

HINSTANCE g_hInst;
HWND hCombo;
bool bSelect = false;

VOID CreateBackGround(HWND hWnd)
{
	PAINTSTRUCT ps; // �׸��� �⺻ ����ü
	BITMAP bit; // ��Ʈ�� �̹��� ����ü


	HDC hdc = BeginPaint(hWnd, &ps); // �׸��� ���� DC �߱�
	HDC MemDC = CreateCompatibleDC(hdc); // �̹��� �ε��� ���� DC �߱�
	HBITMAP MyBitMap = (HBITMAP)LoadImage(NULL, L"background.jpg", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION); //�̹��� ���� �ε�

	GetObject(MyBitMap, sizeof(bit), &bit); // �ε��� ���� �о�� bit�� ����
	HBITMAP OldBitMap = (HBITMAP)SelectObject(MemDC, MyBitMap); // ���� ���ȭ�� MyBitMap���� ����
	BitBlt(hdc, 0, 0, 640, 640, MemDC, 0, 0, SRCCOPY); // ���ȭ�� ��ü
	SelectObject(MemDC, OldBitMap); // ��� ������ ���� ������ �� ����
	DeleteObject(MyBitMap); //��� �޸� �ε� ����


	DeleteDC(MemDC); // �޸� �ε� DC ����
	EndPaint(hWnd, &ps); // �׸��� DC ����
}

VOID CreateSystemClasses(HWND hWnd)
{
	//Button
	CreateWindowEx(
		0,
		L"button",
		L"OK",
		WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, // TABŰ ���� | �ڽ� | ���̰� �ϱ� | ���� Ŭ�� �� WM_COMMAND ��ȯ �ɼ� (https://learn.microsoft.com/ko-kr/windows/win32/controls/button-styles)
		125, // x
		10, // y 
		100, // width
		30, // height
		hWnd,
		(HMENU)IDC_BUTTON1,
		g_hInst,
		nullptr
	);

	//ComboBox
	hCombo = CreateWindowEx(
		0,
		L"combobox",
		L"combo",
		WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, // �ڽ� | ���̰� �ϱ� | ��Ӵٿ�-����Ʈ �ɼ� (https://learn.microsoft.com/ko-kr/windows/win32/controls/about-combo-boxes)
		5, // x
		15, // y 
		100, // width
		300, // height
		hWnd,
		(HMENU)IDC_COMBOBOX1,
		g_hInst,
		nullptr
	);

	//ComboBox - AddString, �����ڵ� �ֱ���..?
	SendMessageA(hCombo, CB_ADDSTRING, 0, (LPARAM)"�ѱ�");
	SendMessageA(hCombo, CB_ADDSTRING, 0, (LPARAM)"Apple");
	SendMessageA(hCombo, CB_ADDSTRING, 0, (LPARAM)"�׽�Ʈ");
}

VOID CommandProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
		case IDC_BUTTON1:
			if (bSelect)
			{
				LPWSTR str = new WCHAR[128];
				SendMessage(hCombo, CB_GETLBTEXT, SendMessage(hCombo, CB_GETCURSEL, 0, 0), (LPARAM)str);
				MessageBox(hWnd, str, L"����", MB_OK);
			}
			else
			{
				MessageBox(hWnd, L"����� �������ּ���.", L"����", MB_OK);
			}
			break;
		case IDC_COMBOBOX1:
			LPWSTR str = new WCHAR[128];
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				bSelect = true;
			//	SendMessage(hCombo, CB_GETLBTEXT, SendMessage(hCombo, CB_GETCURSEL, 0, 0), (LPARAM)str);
			//	MessageBox(hWnd, str, L"����", MB_OK);
			//	SetWindowText(hWnd, str);
			}
			//else if (HIWORD(wParam) == CBN_EDITCHANGE)
			//{
			//	GetWindowText(hCombo, str, 128);
			//	SetWindowText(hWnd, str);
			//}
			break;
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
		case WM_CREATE: // ���α׷� ���� �� �����ϴ� ���
			CreateSystemClasses(hWnd);
			break;
		case WM_DESTROY: // ���α׷� ���� �� �����ϴ� ���
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

INT APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszcmParam, int cmdShow)
{
	LPCWSTR name = L"test";
	g_hInst = hInstance;
	WNDCLASSEXW wnd_class; // ������ Ŭ����(â) ��ü
	wnd_class.cbSize = sizeof(WNDCLASSEXW);
	wnd_class.cbClsExtra = 0;
	wnd_class.cbWndExtra = 0;
	wnd_class.hbrBackground = HBRUSH(0x10); // =int, RGB �� �����Ͽ� ���� ó��
	wnd_class.hCursor = LoadCursorW(hInstance, IDC_ARROW); // ���콺 Ŀ�� �⺻ ��
	wnd_class.hIcon = LoadIconW(hInstance, IDI_APPLICATION); // ������ �⺻ ��
	wnd_class.hIconSm = LoadIconW(hInstance, IDI_APPLICATION);
	wnd_class.hInstance = hInstance;
	wnd_class.lpfnWndProc = WndProc;
	wnd_class.lpszClassName = name;
	wnd_class.lpszMenuName = NULL;
	wnd_class.style = CS_HREDRAW | CS_VREDRAW; // Ŭ���̾�Ʈ â ũ�� ����� �ٽ� �׸��� �ɼ�

	RegisterClassEx(&wnd_class); // ������ Ŭ���� ���(����) �Լ�

	//RegisterClass ���Ŀ� �ؾ� �� �����
	HWND hWnd = CreateWindowEx(
		0,
		name,
		name,
		WS_OVERLAPPEDWINDOW, // �ٸ� â�� ��ĥ �� �ִ� �ɼ� (https://learn.microsoft.com/ko-kr/windows/win32/winmsg/window-styles)
		CW_USEDEFAULT, // �ش� ������ �⺻ �� ���
		CW_USEDEFAULT,
		640,//CW_USEDEFAULT,
		640,//CW_USEDEFAULT,
		nullptr,//HWND(0),
		nullptr,//HMENU(0),
		hInstance,
		nullptr
	);

	if (hWnd)
	{
		ShowWindow(hWnd, SW_SHOWDEFAULT); // Cmdâ Show Default������ ����
		UpdateWindow(hWnd);
		MSG msg;

		while (GetMessage(&msg, nullptr, 0, 0) != 0)
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