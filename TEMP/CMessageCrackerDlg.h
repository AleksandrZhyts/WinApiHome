#pragma once
#include "Header.h"

#define ID_STBAR 1

namespace data
{
	TCHAR login[] = L"admin";
	TCHAR password[] = L"123";
}

HINSTANCE hAutoriz = GetModuleHandle(NULL);

HWND hDialog;
HWND hOpen,
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
	hStaticCount,
	hCombo,
	hSave,
	hRecord3;

static HWND hLogin,
			hPassword,
			hOk,
			hCancel;

class CMessageCrackersDlg
{
public:
	CMessageCrackersDlg(void);

public:
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	static CMessageCrackersDlg *ptr;
	
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl,	UINT codeNotify);
	
	void Cls_OnClose(HWND hwnd);

};

class CMessageCrackersDlg2
{
public:
	CMessageCrackersDlg2(void);

public:
	
	static BOOL CALLBACK DlgProc2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	static CMessageCrackersDlg2 *ptr2;

	BOOL Cls_OnInitDialog2(HWND hwnd, HWND hwndFocus, LPARAM lParam);

	void Cls_OnCommand2(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);

	void Cls_OnClose2(HWND hwnd);

};