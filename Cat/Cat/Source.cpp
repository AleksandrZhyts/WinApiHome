#include <windows.h>
#include <tchar.h>
#include "resource.h"

HWND hStart, 
     hStop, 
	 hPicture,
	 hCat,
	 hDog,
	 hQuick;

HBITMAP hBmp[10];

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev,LPTSTR lpszCmdLine, int nCmdShow)
{
	MSG msg;
	//создаём главное окно приложения на основе немодального диалога
	HWND hDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);

	ShowWindow(hDialog, nCmdShow);
	
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp)
{
	size_t left_value = 0,
		   right_value = 9,
		   speed = 1000;

	static int index = 0;
	LRESULT lResult1 = SendMessage(hCat, BM_GETCHECK, 0, 0),
			lResult2 = SendMessage(hDog, BM_GETCHECK, 0, 0);

	switch (mes)
	{
	case WM_INITDIALOG:
		hStart = GetDlgItem(hWnd, IDC_BUTTON1);
		hStop = GetDlgItem(hWnd, IDC_BUTTON2);
		hPicture = GetDlgItem(hWnd, IDC_PICTURE5);
		hCat = GetDlgItem(hWnd, IDC_CHECK1);
		hDog = GetDlgItem(hWnd, IDC_CHECK2);
		hQuick = GetDlgItem(hWnd, IDC_RADIO1);

		for (int i = 0; i < 10; i++)
			hBmp[i] = LoadBitmap(GetModuleHandle(NULL),	MAKEINTRESOURCE(IDB_BITMAP1 + i));
		break;

	case WM_COMMAND:
		if (wp == IDC_BUTTON1)
		{
			if (SendMessage(hCat, BM_GETCHECK, 0, 0) == BST_UNCHECKED && SendMessage(hDog, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
			{
				MessageBoxW(NULL, L"Выберите тип картинок и скорость показа !", L"Котики или  Собачки ? :)", MB_OK | MB_ICONWARNING);
				break;
			}
			if (SendMessage(hQuick, BM_GETCHECK, 0, 0) == BST_CHECKED) speed = 500;

			SetTimer(hWnd, 1, speed, NULL);
			EnableWindow(hStart, FALSE);
			EnableWindow(hStop, TRUE);
			SetFocus(hStop);
		}
		else if (wp == IDC_BUTTON2)
		{
			KillTimer(hWnd, 1);
			EnableWindow(hStart, TRUE);
			EnableWindow(hStop, FALSE);
			SetFocus(hStart);
		}
		break;
	
	case WM_TIMER:
		

		if (lResult1 == BST_CHECKED && lResult2 != BST_CHECKED) right_value = 4;
		if (lResult1 != BST_CHECKED && lResult2 == BST_CHECKED) left_value = 5;
		if (++index > right_value) index = left_value;
		
		SendMessage(hPicture, STM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[index]));
		break;

	case WM_CLOSE:
		DestroyWindow(hWnd); 
		PostQuitMessage(0);
		return TRUE;
	}
		return FALSE;
}