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
	PAINTSTRUCT ps; // 그리기 기본 구조체
	BITMAP bit; // 비트맵 이미지 구조체


	HDC hdc = BeginPaint(hWnd, &ps); // 그리기 위한 DC 발급
	HDC MemDC = CreateCompatibleDC(hdc); // 이미지 로딩을 위한 DC 발급
	HBITMAP MyBitMap = (HBITMAP)LoadImage(NULL, L"background.jpg", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION); //이미지 파일 로딩

	GetObject(MyBitMap, sizeof(bit), &bit); // 로딩한 파일 읽어와 bit에 저장
	HBITMAP OldBitMap = (HBITMAP)SelectObject(MemDC, MyBitMap); // 기존 배경화면 MyBitMap으로 변경
	BitBlt(hdc, 0, 0, 640, 640, MemDC, 0, 0, SRCCOPY); // 배경화면 교체
	SelectObject(MemDC, OldBitMap); // 배경 삭제를 위해 데이터 값 변경
	DeleteObject(MyBitMap); //배경 메모리 로딩 삭제


	DeleteDC(MemDC); // 메모리 로딩 DC 해제
	EndPaint(hWnd, &ps); // 그리기 DC 해제
}

VOID CreateSystemClasses(HWND hWnd)
{
	//Button
	CreateWindowEx(
		0,
		L"button",
		L"OK",
		WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, // TAB키 막기 | 자식 | 보이게 하기 | 단추 클릭 시 WM_COMMAND 소환 옵션 (https://learn.microsoft.com/ko-kr/windows/win32/controls/button-styles)
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
		WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, // 자식 | 보이게 하기 | 드롭다운-리스트 옵션 (https://learn.microsoft.com/ko-kr/windows/win32/controls/about-combo-boxes)
		5, // x
		15, // y 
		100, // width
		300, // height
		hWnd,
		(HMENU)IDC_COMBOBOX1,
		g_hInst,
		nullptr
	);

	//ComboBox - AddString, 유니코드 왜깨짐..?
	SendMessageA(hCombo, CB_ADDSTRING, 0, (LPARAM)"한글");
	SendMessageA(hCombo, CB_ADDSTRING, 0, (LPARAM)"Apple");
	SendMessageA(hCombo, CB_ADDSTRING, 0, (LPARAM)"테스트");
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
				MessageBox(hWnd, str, L"정보", MB_OK);
			}
			else
			{
				MessageBox(hWnd, L"대상을 선택해주세요.", L"오류", MB_OK);
			}
			break;
		case IDC_COMBOBOX1:
			LPWSTR str = new WCHAR[128];
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				bSelect = true;
			//	SendMessage(hCombo, CB_GETLBTEXT, SendMessage(hCombo, CB_GETCURSEL, 0, 0), (LPARAM)str);
			//	MessageBox(hWnd, str, L"정보", MB_OK);
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
		case WM_CREATE: // 프로그램 실행 시 도달하는 헤더
			CreateSystemClasses(hWnd);
			break;
		case WM_DESTROY: // 프로그램 종료 시 도달하는 헤더
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
	WNDCLASSEXW wnd_class; // 윈도우 클래스(창) 객체
	wnd_class.cbSize = sizeof(WNDCLASSEXW);
	wnd_class.cbClsExtra = 0;
	wnd_class.cbWndExtra = 0;
	wnd_class.hbrBackground = HBRUSH(0x10); // =int, RGB 값 전달하여 색깔 처리
	wnd_class.hCursor = LoadCursorW(hInstance, IDC_ARROW); // 마우스 커서 기본 값
	wnd_class.hIcon = LoadIconW(hInstance, IDI_APPLICATION); // 아이콘 기본 값
	wnd_class.hIconSm = LoadIconW(hInstance, IDI_APPLICATION);
	wnd_class.hInstance = hInstance;
	wnd_class.lpfnWndProc = WndProc;
	wnd_class.lpszClassName = name;
	wnd_class.lpszMenuName = NULL;
	wnd_class.style = CS_HREDRAW | CS_VREDRAW; // 클라이언트 창 크기 변경시 다시 그리는 옵션

	RegisterClassEx(&wnd_class); // 윈도우 클래스 등록(생성) 함수

	//RegisterClass 이후에 해야 잘 실행됨
	HWND hWnd = CreateWindowEx(
		0,
		name,
		name,
		WS_OVERLAPPEDWINDOW, // 다른 창과 겹칠 수 있는 옵션 (https://learn.microsoft.com/ko-kr/windows/win32/winmsg/window-styles)
		CW_USEDEFAULT, // 해당 변수에 기본 값 사용
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
		ShowWindow(hWnd, SW_SHOWDEFAULT); // Cmd창 Show Default값으로 설정
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
		MessageBox(nullptr, L"윈도우 창을 열지 못했습니다.", L"오류", MB_OK);
	}

	return 0;
}