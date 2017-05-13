//#pragma comment(lib,"comctl32")

#include "CMessageCrackerDlg.h"

CMessageCrackersDlg2* CMessageCrackersDlg2::ptr2 = NULL;

CMessageCrackersDlg2::CMessageCrackersDlg2(void)
{
	ptr2 = this;
}

void Cls_OnClose2(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL Cls_OnInitDialog2(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{
	hLogin = GetDlgItem(hWnd, IDC_LOGIN);
	hPassword = GetDlgItem(hWnd, IDC_PASSWORD);
	hOk = GetDlgItem(hWnd, IDOK);
	hCancel = GetDlgItem(hWnd, IDCANCEL);

	return TRUE;
}

void Cls_OnCommand2(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	TCHAR templogin[20] = L"",
		temppassword[20] = L"";

	if (id == IDCANCEL)	SendMessage(hWnd, WM_CLOSE, 0, 0);

	if (id == IDOK)
	{
		GetWindowText(hLogin, templogin, sizeof(templogin));
		GetWindowText(hPassword, temppassword, sizeof(temppassword));
		if (!lstrcmp(templogin, data::login) && !lstrcmp(temppassword, data::password))
		{
			EnableWindow(hOpen, TRUE);
			EnableWindow(hClear, TRUE);
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			EnableWindow(hAutoris, FALSE);
			SendMessage(hStatusBar, SB_SETTEXT, 0, (LPARAM)templogin);
		}
		else MessageBox(NULL, L"Логин и/или пароль не совпадает!", L"Внимание", MB_OK | MB_ICONINFORMATION);
	}
}

BOOL CALLBACK CMessageCrackersDlg2::DlgProc2(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr2->Cls_OnClose2);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr2->Cls_OnInitDialog2);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr2->Cls_OnCommand2);
	}
	return FALSE;
}

CMessageCrackersDlg* CMessageCrackersDlg::ptr = NULL;

CMessageCrackersDlg::CMessageCrackersDlg(void)
{
	ptr = this;
}

void CMessageCrackersDlg::Cls_OnClose(HWND hWnd)
{
	EndDialog(hWnd, 0);
}

BOOL CMessageCrackersDlg::Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{
	int arr[2] = { 170,-1 };
	UINT style;
	
	//static OPENFILENAME openFile; // объявляем переменные
	//wchar_t szFileName[256];
	//wchar_t szFileTitle[100];

	hOpen = GetDlgItem(hWnd, IDC_OPEN);
	hClear = GetDlgItem(hWnd, IDC_CLEAR);
	hClear2 = GetDlgItem(hWnd, IDC_CLEAR2);
	hRecord = GetDlgItem(hWnd, IDC_RECORD);
	hEdit1 = GetDlgItem(hWnd, IDC_EDIT1);
	hEdit2 = GetDlgItem(hWnd, IDC_EDIT2);
	hEdit3 = GetDlgItem(hWnd, IDC_EDIT3);
	hAutoris = GetDlgItem(hWnd, IDC_AUTORIZ);
	hCopy = GetDlgItem(hWnd, IDC_COPY);
	hCopyAll = GetDlgItem(hWnd, IDC_COPYALL);
	hCopyToDict = GetDlgItem(hWnd, IDC_COPYTODICT);
	hList = GetDlgItem(hWnd, IDC_LIST1);
	hDelRec = GetDlgItem(hWnd, IDC_DELREC);
	hClearDict = GetDlgItem(hWnd, IDC_CLEARDICT);
	hRecordDict = GetDlgItem(hWnd, IDC_RECORDDICT);
	hStaticCount = GetDlgItem(hWnd, IDC_STATICCOUNT);
	hCombo = GetDlgItem(hWnd, IDC_COMBO1);
	hSave = GetDlgItem(hWnd, IDC_SAVE);
	hRecord3 = GetDlgItem(hWnd, IDC_RECORD3);

	//ZeroMemory(&openFile, sizeof(OPENFILENAME)); // заполняем
	//openFile.lStructSize = sizeof(OPENFILENAME); // структуру
	//openFile.hInstance = hAutoriz;
	//openFile.hwndOwner = hWnd;
	//openFile.lpstrFilter = L"All Files(*.*)\0*.*\0\0";
	//openFile.nMaxFile = 256;
	//openFile.nMaxFileTitle = 30;
	//openFile.lpstrFileTitle = szFileTitle;
	//openFile.lpstrFile = szFileName;

	hStatusBar = CreateStatusWindow(WS_CHILD | WS_VISIBLE | CCS_BOTTOM, L"Неизвестный пользователь", hWnd, ID_STBAR);
	SendMessage(hStatusBar, SB_SETPARTS, 2, (LPARAM)arr);
	SendMessage(hStatusBar, SB_SETTEXT, 1, (LPARAM)L"Неизвестный текст");
	//SendMessage(hStatusBar, SB_SETTIPTEXT, 1, (LPARAM)L"Неизвестный текст");

	return TRUE;
}

void CMessageCrackersDlg::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	size_t length;

	if (id == IDC_AUTORIZ)
	{
		DialogBox(hAutoriz, MAKEINTRESOURCE(IDD_AUTORIZ), hWnd, CMessageCrackersDlg2::DlgProc2);
		//MessageBoxW(NULL, L"Это функция пока недоступна !", L"Внимание", MB_OK | MB_ICONINFORMATION);
	}
	if (id == IDC_OPEN)
	{

		//GetOpenFileName(&openFile);
		SetWindowText(hEdit1, L"Ну что же\r\nпожалуй\r\nможно и\r\nпоработать");
		SendMessage(hEdit1, EM_SETREADONLY, TRUE, 0);
		//SendMessage(hStatusBar, SB_SETTEXT, 1, (LPARAM)L"Неизвестный текст"); вывести первую строчку
	}
	if (id == IDC_CLEAR)
	{
		SendMessage(hEdit1, EM_SETREADONLY, FALSE, 0);
		length = SendMessage(hEdit1, WM_GETTEXTLENGTH, 0, 0);
		SendMessage(hEdit1, EM_SETSEL, 0, length);
		SendMessage(hEdit1, WM_CLEAR, 0, 0);
	}
	if (id == IDC_COPY)
	{
		SendMessage(hEdit1, WM_COPY, 0, 0);
		SendMessage(hEdit2, WM_PASTE, 0, 0);
	}
	if (id == IDC_COPYALL)
	{
		length = SendMessage(hEdit1, WM_GETTEXTLENGTH, 0, 0);
		TCHAR* buf = new TCHAR[length + 1];
		GetWindowText(hEdit1, buf, length + 1);
		SetWindowText(hEdit2, buf);
		delete[] buf;
	}
	if (id == IDC_CLEAR2)
	{
		/*SendMessage(hEdit1, EM_SETREADONLY, FALSE, 0);
		length = SendMessage(hEdit1, WM_GETTEXTLENGTH, 0, 0);
		SendMessage(hEdit1, EM_SETSEL, 0, length);
		SendMessage(hEdit1, WM_CLEAR, 0, 0);*/
		SetWindowText(hEdit2, NULL);
	}
	if (id == IDC_RECORD)
	{

	}
}

BOOL CALLBACK CMessageCrackersDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}

