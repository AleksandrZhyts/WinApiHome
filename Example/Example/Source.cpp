#include <windows.h>
#include <tchar.h>
#include "resource.h"

#define hBottom 20
#define wBottom 75
#define hWindow 270
#define wWindow 450
#define xLeftWindow 85
#define yTopWindow 295
#define SHIFT 50
#define DELTA 25

HWND hOk;
HMENU hMenu;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE	hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message,	WPARAM wp, LPARAM lp)
{
	TCHAR szCoordinates[50];
	RECT rect;
	int step = 0;
	static int xMouse = 0, 
			   yMouse = 0;

	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;

	case WM_INITDIALOG:
		hOk = GetDlgItem(hWnd, IDOK);
		hMenu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU1));
		SetMenu(hWnd, hMenu);
		return TRUE;

	case WM_MOUSEMOVE:
		xMouse = LOWORD(lp);
		yMouse = HIWORD(lp);
		GetWindowRect(hOk, &rect);

		if ((xMouse + DELTA + xLeftWindow >= rect.left) && (xMouse - DELTA + xLeftWindow <= rect.right) ||
			(yMouse + DELTA + yTopWindow >= rect.top) && (yMouse - DELTA + yTopWindow <= rect.bottom))
		{
			if ((yMouse + yTopWindow < rect.top) && (rect.top - yTopWindow - yMouse < DELTA))
			{
				if (yMouse + SHIFT + hBottom > hWindow) step = -2;
				else step = 1;
				MoveWindow(hOk, rect.left - xLeftWindow - (rect.right + DELTA >= xLeftWindow + wWindow)*SHIFT, yMouse + step * SHIFT, wBottom, hBottom, TRUE);
			}

			if ((yMouse + yTopWindow > rect.bottom) && (yTopWindow + yMouse < rect.bottom + DELTA))
			{
				if (yMouse - SHIFT - hBottom < 10) step = 2;
				else step = -1;
				MoveWindow(hOk, rect.left - xLeftWindow - (rect.right + DELTA >= xLeftWindow + wWindow)*SHIFT, yMouse + step*SHIFT, wBottom, hBottom, TRUE);
			}

			if ((rect.left > xMouse + xLeftWindow) && (xMouse + xLeftWindow > rect.left - DELTA))
			{
				if (xMouse + DELTA + wBottom + SHIFT < wWindow) step = 1;
				else step = -2;
				MoveWindow(hOk, xMouse + step * SHIFT, rect.top - yTopWindow, wBottom, hBottom, TRUE);
			}

			if ((rect.right < xMouse + xLeftWindow) && (xMouse + xLeftWindow < rect.right + DELTA))
			{
				if (xMouse - wBottom - SHIFT < 10) step = 2;
				else step = -1;
				MoveWindow(hOk, xMouse + step * SHIFT, rect.top - yTopWindow, wBottom, hBottom, TRUE);
			}
		}

		wsprintf(szCoordinates, TEXT("Xmouse = %d Ymouse = %d"), xMouse, yMouse);
		SetWindowText(hWnd, szCoordinates);

		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wp) == ID_40003)
		{
			MessageBox(hWnd, L"Данное приложение не предназначено \n для коммерческого использования =) ", L"Сообщение", MB_OK);
		}
		
		return TRUE;
	}
	return FALSE;
}


