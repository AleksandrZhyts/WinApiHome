#pragma once

#include "Header.h"
  
class CMessageCrackersDlg
{
public:
	CMessageCrackersDlg(void);

public:
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	
	static BOOL CALLBACK DlgProc2(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);

	static CMessageCrackersDlg *ptr;
	
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);

	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl,	UINT codeNotify);
	
	void Cls_OnClose(HWND hwnd);

	BOOL Cls_OnInitDialog2(HWND hwnd, HWND hwndFocus, LPARAM lParam);

	void Cls_OnCommand2(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);

	void Cls_OnClose2(HWND hwnd);
	
	HWND hDialog,
	     hOpen,
		 hClear,
		 hClear2,
		 hRecord,
		 hEdit1,
		 hEdit2,
		 hEdit3,
		 hAutoris,
		 hStatusBar,
		 hCopy,
		 hCopyToDict,
		 hCopyAll,
		 hList,
		 hDelRec,
		 hClearDict,
		 hRecordDict,
		 hCountNode,
		 hCombo,
		 hSaveRecordToFile,
		 hRecordToMap;

	HINSTANCE hAutoriz;
};