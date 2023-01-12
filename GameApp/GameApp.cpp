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

	WNDCLASSEXW wnd_class; // 윈도우 클래스(창) 객체
	wnd_class.cbSize = sizeof(WNDCLASSEXW);
	wnd_class.cbClsExtra = 0;
	wnd_class.cbWndExtra = 0;
	wnd_class.hbrBackground = HBRUSH(0x10); // =int, RGB 값 전달하여 색깔 처리
	wnd_class.hCursor = LoadCursorW(hInstance, IDC_ARROW); // 마우스 커서 기본 값
	wnd_class.hIcon = LoadIconW(hInstance, IDI_APPLICATION); // 아이콘 기본 값
	wnd_class.hIconSm = LoadIconW(hInstance, IDI_APPLICATION);
	wnd_class.hInstance = hInstance;
	wnd_class.lpfnWndProc = wnd_proc;
	wnd_class.lpszClassName = name;
	wnd_class.lpszMenuName = NULL;
	wnd_class.style = CS_HREDRAW | CS_VREDRAW; // 클라이언트 창 변경시 다시 그리는 옵션

	RegisterClassExW(&wnd_class); // 윈도우 클래스 등록(생성) 함수

	//RegisterClass 이후에 해야 잘 실행됨
	HWND hWnd = CreateWindowExW(
		0,
		name,
		name,
		WS_OVERLAPPEDWINDOW, // 다른 창과 겹칠 수 있는 옵션 (https://learn.microsoft.com/ko-kr/windows/win32/winmsg/window-styles)
		CW_USEDEFAULT, // 해당 변수에 기본 값 사용
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
		ShowWindow(hWnd, SW_SHOWDEFAULT); // Cmd창 Show Default값으로 설정
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
		MessageBoxW(NULL, L"윈도우 창을 열지 못했습니다.", L"오류", 0);
	}

	return 0;
}