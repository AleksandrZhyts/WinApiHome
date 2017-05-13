#pragma comment (lib,"comctl32")
#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include "commctrl.h"

HWND hProgressBar,
	 hOk,
	 hCansel,
	 hSlider,
	 hDial,
	 hSpin;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HMENU hMenu;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	INITCOMMONCONTROLSEX cc;
	cc.dwSize = sizeof(cc);
	cc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&cc);
	
	HWND hW;
	hW = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	ShowWindow(hW, 1);

	HACCEL hA;
	hA = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));
	
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		if (!TranslateAccelerator(hW, hA, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static RECT rect;
	int curPos;
	switch (message)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd); 
		PostQuitMessage(0);
		return TRUE;

	case WM_INITDIALOG:
		hOk = GetDlgItem(hWnd, IDOK);
		hCansel = GetDlgItem(hWnd, IDCANCEL);
		hProgressBar = GetDlgItem(hWnd, IDC_PROGRESS1);
		hDial  = GetDlgItem(hWnd, IDD_DIALOG1);
		
		SendMessage(hProgressBar, PBM_SETBKCOLOR, 0, LPARAM(RGB(250, 190, 195)));
		SendMessage(hProgressBar, PBM_SETBARCOLOR,0, LPARAM(RGB(150, 100, 250)));
		SendMessage(hProgressBar, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
		SendMessage(hProgressBar, PBM_SETSTEP, 5, 0);
		
		hSlider = GetDlgItem(hWnd, IDC_SLIDER1);
		SendMessage(hSlider, TBM_SETRANGE, TRUE, MAKELPARAM(0,200));
		SendMessage(hSlider, TBM_SETPOS, TRUE, 50);
		SendMessage(hSlider, TBM_SETLINESIZE, 0, 15);

		hSpin = GetDlgItem(hWnd, IDC_SPIN1);
		SendMessage(hSpin, UDM_SETRANGE32, 0, 200);
		SendMessage(hSpin, UDM_SETPOS32, 0, 10);
		//SendMessage(hSpin, UDM_GETPOS32, 0, 10);
		
		hMenu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU1));
		SetMenu(hWnd, hMenu);
		return TRUE;

	case WM_COMMAND:
		if (wParam == IDOK)
		{
			SetTimer(hWnd, 1, 1000, NULL);
		}
		if (wParam == IDCANCEL)
		{
			KillTimer(hWnd, 1);
		}
		if (HIWORD(wParam) == EN_CHANGE)
		{
			SendMessage(hWnd, WM_VSCROLL, 0, 0);
		}
		return TRUE;
	
	case WM_VSCROLL:         //WM_VSCROLL
		if (LOWORD(wParam) == TB_LINEUP)
		{
			//MessageBox(hWnd, L"Словили", L"Сообщение", MB_OK);
			GetWindowRect(hWnd, &rect);
			MoveWindow(hWnd, rect.left, rect.top, rect.right + 10, rect.bottom + 20, TRUE);	
		}
		curPos = SendMessage(hSpin, UDM_GETPOS32, 0, 0);
		MoveWindow(hWnd, curPos, curPos, rect.right, rect.bottom, TRUE);
		return TRUE;

	case WM_LBUTTONDOWN:
		CheckMenuItem(hMenu, ID_40001, MF_BYCOMMAND | MF_UNCHECKED);
		return TRUE;
	
	case WM_INITMENUPOPUP:
		//MessageBox(hWnd, L"Словили 1", L"Сообщение", MB_OK);
		
		return TRUE;
	
	case WM_TIMER:
		//SendMessage(hProgressBar, PBM_DELTAPOS, 5, 0);
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		return TRUE;
	}

	return FALSE;
}