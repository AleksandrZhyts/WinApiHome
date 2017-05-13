#include <windows.h>
#include <string>
#include <algorithm>

#define ID_BUTTON 3000
#define ID_BUTTON2 3001
#define ID_BUTTON3 3002
#define ID_BUTTON4 3003
#define ID_EDIT 100
#define ID_EDIT2 101

LRESULT CALLBACK WindProc(HWND, UINT, WPARAM, LPARAM);

bool is_palindrom(std::wstring);

bool is_anagramma(std::wstring, std::wstring);

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance, LPSTR lpCmdLine, int nCmdShow)
{
	LPWSTR szClassName = L"My window";

	WNDCLASSEX wndclass;

	memset(&wndclass, 0, sizeof(wndclass));

	wndclass.cbSize = sizeof(wndclass);
	wndclass.lpszClassName = szClassName;
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wndclass.lpfnWndProc = WindProc;
	wndclass.hInstance = hinstance;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wndclass)) return false;

	HWND hWnd = CreateWindowEx(
		WS_EX_TOPMOST,
		szClassName,
		L"Text Application",
		WS_OVERLAPPEDWINDOW,
		500, 10, 500, 400,
		NULL,
		NULL,
		hinstance,
		NULL);
	
	if (!hWnd) return false;

	ShowWindow(hWnd, 1);
	UpdateWindow(hWnd);
	
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WindProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HWND hWndStat,
				hWndStat2,
				hWndStat3,
				hWndBut,
				hWndBut2,
				hWndBut3,
				hWndBut4,
				hEdit,
				hEdit2;
		    
	TCHAR buf[150], buf2[150];

	switch (iMsg)
	{
	case WM_CREATE:
		hWndStat = CreateWindowEx(
			NULL,      
			L"STATIC",
			TEXT("Первое слово"),
			WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
			10, 15, 95, 20,
			hwnd,
			(HMENU)NULL,
			GetModuleHandle(NULL),
			NULL);

		hWndStat2 = CreateWindowEx(
			NULL,
			L"STATIC",
			TEXT("Второе слово"),
			WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
			10, 50, 95, 20,
			hwnd,
			(HMENU)NULL,
			GetModuleHandle(NULL),
			NULL);

		hWndStat3 = CreateWindowEx(
			NULL,
			L"STATIC",
			TEXT(""),
			WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE,
			20, 260, 440, 60,
			hwnd,
			(HMENU)NULL,
			GetModuleHandle(NULL),
			NULL);

		hWndBut = CreateWindowEx(
			NULL,
			L"BUTTON",
			TEXT("анаграмма"),
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			10, 120, 100, 35,
			hwnd,
			(HMENU)ID_BUTTON,
			GetModuleHandle(NULL),
			NULL);

		hWndBut2 = CreateWindowEx(
			NULL,
			L"BUTTON",
			TEXT("палиндром"),
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			200, 120, 100, 35,
			hwnd,
			(HMENU)ID_BUTTON2,
			GetModuleHandle(NULL),
			NULL);

		hWndBut3 = CreateWindowEx(
			NULL,
			L"BUTTON",
			TEXT("Проверить"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON ,
			100, 200, 100, 30,
			hwnd,
			(HMENU)ID_BUTTON3,
			GetModuleHandle(NULL),
			NULL);

		hWndBut4 = CreateWindowEx(
			NULL,
			L"BUTTON",
			TEXT("Очистить"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			230, 200, 100, 30,
			hwnd,
			(HMENU)ID_BUTTON4,
			GetModuleHandle(NULL),
			NULL);

		hEdit = CreateWindowEx(
			WS_EX_TOPMOST,
			L"EDIT",
			L"",
			WS_CHILD | WS_VISIBLE,
			120, 10, 350, 30,
			hwnd,
			(HMENU)ID_EDIT,
			GetModuleHandle(NULL),
			NULL);

		hEdit2 = CreateWindowEx(
			WS_EX_TOPMOST,
			L"EDIT",
			L"",
			WS_CHILD | WS_VISIBLE,
			120, 45, 350, 30,
			hwnd,
			(HMENU)ID_EDIT2,
			GetModuleHandle(NULL),
			NULL);

	case WM_COMMAND:
		if (SendMessage(hWndBut2, BM_GETCHECK, 0, 0) == BST_CHECKED) EnableWindow(hEdit2, FALSE);
			else EnableWindow(hEdit2, TRUE);
		
		if (LOWORD(wParam) == ID_BUTTON4)
		{
			SetWindowText(hEdit, NULL);
			SetWindowText(hEdit2, NULL);
			SetWindowText(hWndStat3, NULL);
		}

		if (SendMessage(hWndBut2, BM_GETCHECK, 0, 0) == BST_CHECKED && LOWORD(wParam) == ID_BUTTON3)
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			SetWindowText(hEdit2, NULL);
			
			std::wstring temp(buf);
			if (temp == TEXT(""))
			{
				SetWindowText(hWndStat3, L"Для определения полиндрома заполните первое поле !");
				break;
			}

			if (is_palindrom(buf))	SetWindowText(hWndStat3, L"Это палиндром");
				else SetWindowText(hWndStat3, L"Это не палиндром");
		}

		if (SendMessage(hWndBut, BM_GETCHECK, 0, 0) == BST_CHECKED && LOWORD(wParam) == ID_BUTTON3)
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			GetWindowText(hEdit2, buf2, sizeof(buf2));
			
			std::wstring temp1(buf),
				         temp2(buf2);
			if (temp1 == TEXT("") || temp2 == TEXT(""))
			{
				SetWindowText(hWndStat3, L"Для определения анаграммы заполните два поля !");
				break;
			}
			
			if (is_anagramma(buf, buf2)) SetWindowText(hWndStat3, L"Эти слова - анаграммы");
				else SetWindowText(hWndStat3, L"Эти слова - не анаграммы");
		}
		break;

	case WM_DESTROY:
		if (!GetActiveWindow()) PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, iMsg, wParam, lParam);
	}
	return 0;
}

bool is_palindrom(std::wstring ws)
{
	std::transform(ws.begin(), ws.end(), ws.begin(), ::tolower);
	std::wstring temp(ws);
	std::reverse(std::begin(temp), std::end(temp));
	return !ws.compare(temp);
}

bool is_anagramma(std::wstring ws1, std::wstring ws2)
{
	setlocale(LC_ALL, ".1251");
	std::transform(ws1.begin(), ws1.end(), ws1.begin(), ::towlower);
	std::transform(ws2.begin(), ws2.end(), ws2.begin(), ::towlower);
	std::sort(std::begin(ws1), std::end(ws1));
	std::sort(std::begin(ws2), std::end(ws2));
	return !ws1.compare(ws2);
}