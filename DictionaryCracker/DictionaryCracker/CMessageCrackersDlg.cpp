#include "CMessageCrackersDlg.h"

#define ID_STBAR 1
#define MAXSIZESTRING 256

namespace data
{
	TCHAR login[] = L"admin";
	TCHAR password[] = L"123";

	std::map<std::wstring, std::wstring> dictValue,
										 dictTranslate,
										 dictSynonym,
										 dictAntonym;

	std::wstring readFileToWstring(wchar_t* nameFile);
	void writeToFile(wchar_t* nameFile, wchar_t* str);
	void writeToFileMap(wchar_t* nameFile, std::map<std::wstring, std::wstring> dict);
}

CMessageCrackersDlg* CMessageCrackersDlg::ptr = NULL;

CMessageCrackersDlg::CMessageCrackersDlg(void)
{
	ptr = this;
}

void CMessageCrackersDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

static OPENFILENAME openFile,
					saveFile;

BOOL CMessageCrackersDlg::Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{
	hDialog = hWnd;
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
	hCountNode = GetDlgItem(hWnd, IDC_STATICCOUNT);
	hSaveRecordToFile = GetDlgItem(hWnd, IDC_SAVE);
	hRecordToMap = GetDlgItem(hWnd, IDC_RECORD3);

	hCombo = GetDlgItem(hWnd, IDC_COMBO1);
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"значение");
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"перевод");
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"синоним");
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"антоним");

	int arr[2] = { 170, -1 };
	hStatusBar = CreateStatusWindow(WS_CHILD | WS_VISIBLE | CCS_BOTTOM, L"Неизвестный пользователь", hWnd, ID_STBAR);
	SendMessage(hStatusBar, SB_SETPARTS, 2, (LPARAM)arr);
	SendMessage(hStatusBar, SB_SETTEXT, 1, (LPARAM)L"Неизвестный текст");
	
	static wchar_t szFileName[256],
				   szFileTitle[100];
	
	ZeroMemory(&openFile, sizeof(OPENFILENAME)); 
	openFile.lStructSize = sizeof(OPENFILENAME); 
	openFile.hInstance = hAutoriz;
	openFile.hwndOwner = hWnd;
	openFile.lpstrFilter = L"All Files(*.*)\0*.*\0\0";
	openFile.nMaxFile = 256;
	openFile.nMaxFileTitle = 30;
	openFile.lpstrFileTitle = szFileTitle;
	openFile.lpstrFile = szFileName;
	
	ZeroMemory(&saveFile, sizeof(OPENFILENAME));
	saveFile.lStructSize = sizeof(OPENFILENAME);
	saveFile.hInstance = hAutoriz;
	saveFile.hwndOwner = hWnd;
	saveFile.lpstrFilter = L"All Files(*.*)\0*.*\0\0";
	saveFile.nMaxFile = 256;
	saveFile.nMaxFileTitle = 30;
	saveFile.lpstrFileTitle = szFileTitle;
	saveFile.lpstrFile = szFileName;
	saveFile.lpstrTitle = L"Сохранить файл?";

	return TRUE;
}

void CMessageCrackersDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	static WORD wBeginPosition, 
		        wEndPosition;
	static size_t countNodeList = 0;
	size_t length, 
		   row, 
		   col;
	TCHAR* buf, 
		   dst[MAXSIZESTRING], 
		   buf2[MAXSIZESTRING];
	int index;
	
	switch (id)
	{
	case IDC_AUTORIZ:
			DialogBox(hAutoriz, MAKEINTRESOURCE(IDD_AUTORIZ), hwnd, DlgProc2);
			break;

	case IDC_OPEN:
			GetOpenFileName(&openFile);
			SetWindowText(hEdit1, data::readFileToWstring(openFile.lpstrFileTitle).c_str());
			SendMessage(hEdit1, EM_SETREADONLY, TRUE, 0);

			length = SendMessage(hEdit1, EM_LINELENGTH, 0, 0);
			buf = new TCHAR[length + 1];
			SendMessage(hEdit1, WM_GETTEXT, length + 1, (LPARAM)buf);
			SendMessage(hStatusBar, SB_SETTEXT, 1, (LPARAM)buf);
			delete[] buf;
			break;

	case IDC_CLEAR:
			SendMessage(hEdit1, EM_SETREADONLY, FALSE, 0);
			length = SendMessage(hEdit1, WM_GETTEXTLENGTH, 0, 0);
			SendMessage(hEdit1, EM_SETSEL, 0, length);
			SendMessage(hEdit1, WM_CLEAR, 0, 0);
			break;
		
	case IDC_COPY:
			SendMessage(hEdit1, WM_COPY, 0, 0);
			SendMessage(hEdit2, WM_PASTE, 0, 0);
			break;

	case IDC_COPYALL:
			length = SendMessage(hEdit1, WM_GETTEXTLENGTH, 0, 0);
			buf = new TCHAR[length + 1];
			GetWindowText(hEdit1, buf, length + 1);
			SetWindowText(hEdit2, buf);
			delete[] buf;
			break;

	case IDC_CLEAR2:
			SetWindowText(hEdit2, NULL);
			break;

	case IDC_RECORD:
		{
			length = SendMessage(hEdit2, WM_GETTEXTLENGTH, 0, 0);
			buf = new TCHAR[length + 1];
			GetWindowText(hEdit2, buf, length + 1);

			GetSaveFileName(&openFile);
			data::writeToFile(saveFile.lpstrFileTitle, buf);  

			delete[] buf;
			break;
		}
	case IDC_COPYTODICT:
			SendMessage(hEdit2, EM_GETSEL, (WPARAM)&wBeginPosition, (LPARAM)&wEndPosition);

			if (wEndPosition != wBeginPosition) // Выделен ли текст?
			{
				row = SendMessage(hEdit2, EM_LINEFROMCHAR, -1, 0);
				col = wBeginPosition - SendMessage(hEdit2, EM_LINEINDEX, row, 0);
				SendMessage(hEdit2, EM_GETLINE, row, (LPARAM)buf2);
				wcsncpy_s(dst, buf2 + col, wEndPosition - wBeginPosition);
				
				TCHAR seps[] = _TEXT(" ,\t\r~&^?!$\n/%*';+=()<>[]{}:\".\\_#"),
					  *next_token = NULL,
					  *token = _tcstok_s(dst, seps, &next_token);
				
				length = SendMessage(hList, LB_SELECTSTRING, -1, LPARAM(token));
				if (length == LB_ERR)
				{
					SendMessage(hList, LB_ADDSTRING, 0, LPARAM(token));
					wsprintf(buf2, L"%d", ++countNodeList);
					SetWindowText(hCountNode, buf2);
				}
			}
			break;

	case IDC_DELREC:
			index = SendMessage(hList, LB_GETCURSEL, 0, 0);

			if (index != LB_ERR) // выбран ли элемент списка?
			{
				SendMessage(hList, LB_DELETESTRING, index, 0);
				wsprintf(buf2, L"%d", --countNodeList);
				SetWindowText(hCountNode, buf2);
			}
			break;

	case IDC_CLEARDICT:
			SendMessage(hList, LB_RESETCONTENT, 0, 0);
			countNodeList = 0;
			SetWindowText(hCountNode, L"0");
			break;

	case IDC_RECORDDICT:
			if (countNodeList)
			{
				GetSaveFileName(&openFile);
				for (int i = 0; i < countNodeList; ++i)
				{
					SendMessage(hList, LB_GETTEXT, i, (LPARAM)buf2);
					data::writeToFile(saveFile.lpstrFileTitle, buf2);
				}
			}
			break;
	
	case IDC_SAVE:
			index = SendMessage(hList, LB_GETCURSEL, 0, 0);
			if (index != LB_ERR) // выбран ли элемент списка?
			{
				SendMessage(hList, LB_GETTEXT, index, LPARAM(buf2));
				length = SendMessage(hEdit3, WM_GETTEXTLENGTH, 0, 0);
				if (length)
				{
					buf = new TCHAR[length + 1];
					GetWindowText(hEdit3, buf, length + 1);
					index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
					switch (index)
					{
					case 0:
						data::dictValue.insert({ buf2 ,buf });
						break;
					case 1:
						data::dictTranslate.insert({ buf2 ,buf }); 
						break;
					case 2:
						data::dictSynonym.insert({ buf2 ,buf });
						break;
					case 3:
						data::dictAntonym.insert({ buf2 ,buf });
						break;
					}
				}
			}
		break;

	case IDC_RECORD3:
		index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
		switch (index)
		{
		case 0:
			GetSaveFileName(&openFile);
			data::writeToFileMap(saveFile.lpstrFileTitle, data::dictValue);
			break;
		case 1:
			GetSaveFileName(&openFile);
			data::writeToFileMap(saveFile.lpstrFileTitle, data::dictTranslate); 
			break;
		case 2:
			GetSaveFileName(&openFile);
			data::writeToFileMap(saveFile.lpstrFileTitle, data::dictSynonym);
			break;
		case 3:
			GetSaveFileName(&openFile);
			data::writeToFileMap(saveFile.lpstrFileTitle, data::dictAntonym);
			break;
		}			
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

static HWND hLogin,
			hPassword,
			hOk,
			hCancel;

void CMessageCrackersDlg::Cls_OnClose2(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL CMessageCrackersDlg::Cls_OnInitDialog2(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{
	hLogin = GetDlgItem(hWnd, IDC_LOGIN);
	hPassword = GetDlgItem(hWnd, IDC_PASSWORD);
	hOk = GetDlgItem(hWnd, IDOK);
	hCancel = GetDlgItem(hWnd, IDCANCEL);
	return TRUE;
}

void CMessageCrackersDlg::Cls_OnCommand2(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	TCHAR templogin[20] = L"",
		  temppassword[20] = L"";
	switch (id)
	{
	case IDCANCEL:
		SendMessage(hWnd, WM_CLOSE, 0, 0);
		break;

	case IDOK:
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
		break;
	}
}

BOOL CALLBACK CMessageCrackersDlg::DlgProc2(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose2);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog2);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand2);
	}
	return FALSE;
}

std::wstring data::readFileToWstring(wchar_t* nameFile)
{
	std::ifstream f_in(nameFile);
	std::wstring str = L"";
	char cb[MAXSIZESTRING];
	wchar_t wcb[MAXSIZESTRING];

	while (f_in.getline(cb, MAXSIZESTRING))
	{
		MultiByteToWideChar(CP_UTF8, 0, cb, MAXSIZESTRING, wcb, MAXSIZESTRING);
		str += wcb;
		str += L"\r\n";
	}
	f_in.close();
	return str;
}

void data::writeToFile(wchar_t* nameFile, wchar_t* str)
{
	std::wofstream ofs(nameFile, std::ios::app);
	std::locale loc(std::locale::classic(), new	std::codecvt_utf8<wchar_t>);
	ofs.imbue(loc);
	ofs << str << std::endl;
	ofs.close();
}

void data::writeToFileMap(wchar_t* nameFile, std::map<std::wstring, std::wstring> dict)
{
	std::wofstream ofs(nameFile);
	std::locale loc(std::locale::classic(), new	std::codecvt_utf8<wchar_t>);
	ofs.imbue(loc);
	
	auto it = dict.begin();
	for (; it != dict.end(); ++it)
	{
		ofs << it->first
			<< L"\t"
			<< it->second
			<< std::endl;
	}
	ofs.close();
}
