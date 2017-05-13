#pragma once
#include "header.h"

class CMessageCrackersDlg
{
public:
	CMessageCrackersDlg(void);
public:
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	
	static CMessageCrackersDlg *ptr;
	
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	
	void Cls_OnClose(HWND hwnd);
	
	void Cls_OnTimer(HWND hwnd, UINT id);
	
	HWND hDialog,
	     hStart,
		 hStop,
		 hPicture,
		 hCat,
		 hDog,
		 hQuick;
	HBITMAP hBmp[10];

};
