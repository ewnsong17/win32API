#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#include "GameApp.h"

INT APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszcmParam, int cmdShow)
{
	return CreateWndClass(hInstance, hPrevInstance, lpszcmParam, cmdShow);
}