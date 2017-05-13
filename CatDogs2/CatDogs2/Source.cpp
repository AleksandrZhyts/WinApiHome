#include <windows.h>
#include <tchar.h>
#include "resource.h"

#define LEFT_START 300
#define TOP_START 370
#define WIDTH_START 76
#define HEIGHT_START 30
#define LEFT_STOP 400
#define TOP_STOP 370
#define WIDTH_STOP 76
#define HEIGHT_STOP 30
#define LEFT_PICTURE 140
#define TOP_PICTURE 5
#define WIDTH_PICTURE 320
#define HEIGHT_PICTURE 320

HWND hStart,
	 hStop,
	 hPicture,
	 hCat,
	 hDog,
	 hQuick;

HBITMAP hBmp[10];
HINSTANCE hInst;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	hInst = hInstance;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}
BOOL CALLBACK DlgProc(HWND hWnd, UINT message,WPARAM wParam, LPARAM lParam)
{
	size_t left_value = 0,
		   right_value = 9,
	       speed = 1000;
		
	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;

	case WM_INITDIALOG:
		hCat = GetDlgItem(hWnd, IDC_CHECK1);
		hDog = GetDlgItem(hWnd, IDC_CHECK2);
		hQuick = GetDlgItem(hWnd, IDC_RADIO1);

		hStart = CreateWindowEx(WS_EX_DLGMODALFRAME,
								TEXT("BUTTON"), TEXT("Start"),
								WS_CHILD | WS_VISIBLE, 
								LEFT_START, TOP_START, WIDTH_START, HEIGHT_START,
								hWnd, 0, hInst, 0);
		hStop = CreateWindowEx(WS_EX_DLGMODALFRAME,
							   TEXT("BUTTON"), TEXT("Stop"),
							   WS_CHILD | WS_VISIBLE | WS_DISABLED,
							   LEFT_STOP, TOP_STOP, WIDTH_STOP, HEIGHT_STOP,
			                   hWnd, 0, hInst, 0);
		hPicture = CreateWindowEx(0, TEXT("BUTTON"), 0,
								  WS_CHILD | WS_VISIBLE | BS_BITMAP,
								  LEFT_PICTURE, TOP_PICTURE, WIDTH_PICTURE, HEIGHT_PICTURE,
								  hWnd, 0, hInst, 0);
		
		for (int i = 0; i < 10; i++)
			hBmp[i] = LoadBitmap(hInst,	MAKEINTRESOURCE(IDB_BITMAP1 + i));
		SendMessage(hPicture, BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[0]));

		return TRUE;
	
	case WM_COMMAND:
	{
		HWND h = GetFocus();
		TCHAR text[10];
		GetWindowText(h, text, 10);
		
		if (!lstrcmp(text, TEXT("Start")))
		{
			if (SendMessage(hQuick, BM_GETCHECK, 0, 0) == BST_CHECKED) speed = 500;
			
			SetTimer(hWnd, 1, speed, NULL);
			EnableWindow(hStart, FALSE);
			EnableWindow(hStop, TRUE);
			SetFocus(hStop);
		}
		else if (!lstrcmp(text, TEXT("Stop")))
		{
			KillTimer(hWnd, 1);
			EnableWindow(hStart, TRUE);
			EnableWindow(hStop, FALSE);
			SetFocus(hStart);
		}
	}
	return TRUE;
	
	case WM_TIMER:
		static int index = 0;
		LRESULT lResult1 = SendMessage(hCat, BM_GETCHECK, 0, 0),
		        lResult2 = SendMessage(hDog, BM_GETCHECK, 0, 0);

		if (lResult1 == BST_CHECKED && lResult2 != BST_CHECKED) right_value = 4;
		if (lResult1 != BST_CHECKED && lResult2 == BST_CHECKED) left_value = 5;
		if (++index > right_value) index = left_value;

		SendMessage(hPicture, BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[index]));
		return TRUE;
	}
	return FALSE;
}