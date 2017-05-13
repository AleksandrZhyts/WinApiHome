#include "CMessageCrackersDlg.h"

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpszCmdLine, int nCmdShow)
{
	CMessageCrackersDlg dlg;
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_MAINDLG), NULL, CMessageCrackersDlg::DlgProc);
}