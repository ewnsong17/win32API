#include "GameApp.h"
#include "GameProc.h"

LPCWSTR class_name = L"단어맞추기";
HINSTANCE g_hInst;

INT CreateWndClass(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszcmParam, int cmdShow)
{
	g_hInst = hInstance;

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
	HWND hWnd = CreateWindow(
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
		MessageBox(nullptr, L"윈도우 창을 열지 못했습니다.", L"오류", MB_OK);
	}

	return 0;
}