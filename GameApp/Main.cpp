#include "GameApp.h"

INT APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszcmParam, int cmdShow)
{
	return CreateWndClass(hInstance, hPrevInstance, lpszcmParam, cmdShow);
}