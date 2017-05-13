#include "CMessageCrackersDlg.h"

CMessageCrackersDlg* CMessageCrackersDlg::ptr = NULL;

CMessageCrackersDlg::CMessageCrackersDlg(void)
{
	ptr = this;
}

void CMessageCrackersDlg::Cls_OnClose(HWND hwnd)
{
	DestroyWindow(hwnd);
	PostQuitMessage(0);
}

BOOL CMessageCrackersDlg::Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{
	hDialog = hWnd;
	hStart = GetDlgItem(hDialog, IDC_START);
	hStop = GetDlgItem(hDialog, IDC_STOP);
	hPicture = GetDlgItem(hDialog, IDC_PICTURE);
	hCat = GetDlgItem(hWnd, IDC_CHECK1);
	hDog = GetDlgItem(hWnd, IDC_CHECK2);
	hQuick = GetDlgItem(hWnd, IDC_RADIO1);

	for (int i = 0; i < 10; i++)
		hBmp[i] = LoadBitmap(GetModuleHandle(NULL),	MAKEINTRESOURCE(IDB_BITMAP1 + i));
	return TRUE;
}

void CMessageCrackersDlg::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_START)
	{
		if (SendMessage(hCat, BM_GETCHECK, 0, 0) == BST_UNCHECKED && SendMessage(hDog, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
		{
			MessageBoxW(NULL, L"Выберите тип картинок и скорость показа !", L"Котики или  Собачки ? :)", MB_OK | MB_ICONWARNING);
			return;
		}
		size_t speed = 1000;
		if (SendMessage(hQuick, BM_GETCHECK, 0, 0) == BST_CHECKED) speed = 500;

		SetTimer(hWnd, 1, speed, NULL);
		EnableWindow(hStart, FALSE);
		EnableWindow(hStop, TRUE);
		SetFocus(hStop);
	}
	else if (id == IDC_STOP)
	{
		KillTimer(hWnd, 1);
		EnableWindow(hStart, TRUE);
		EnableWindow(hStop, FALSE);
		SetFocus(hStart);
	}
}

void CMessageCrackersDlg::Cls_OnTimer(HWND hwnd, UINT id)
{
	static int index = 0;
	size_t left_value = 0,
		   right_value = 9;

	LRESULT lResult1 = SendMessage(hCat, BM_GETCHECK, 0, 0),
		    lResult2 = SendMessage(hDog, BM_GETCHECK, 0, 0);

	if (lResult1 == BST_CHECKED && lResult2 != BST_CHECKED) right_value = 4;
	if (lResult1 != BST_CHECKED && lResult2 == BST_CHECKED) left_value = 5;
	if (++index > right_value) index = left_value;

	SendMessage(hPicture, STM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[index]));
}

BOOL CALLBACK CMessageCrackersDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_TIMER, ptr->Cls_OnTimer);
	}
	return FALSE;
}