#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <time.h>

TCHAR szClassWindow[] = _TEXT("Window");

VOID CALLBACK TimerProc(HWND, UINT, UINT_PTR, DWORD);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wnd;
	
	memset(&wnd, 0, sizeof(wnd));

	wnd.cbSize = sizeof(wnd);
	wnd.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wnd.lpfnWndProc = WndProc;
	wnd.hInstance = hInstance;
	wnd.hCursor = LoadCursor(hInstance,MAKEINTRESOURCE(IDC_CURSOR1));
	wnd.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wnd.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wnd.lpszClassName = szClassWindow;
	wnd.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));

	if (!RegisterClassEx(&wnd))
	{
		return 0;
	}
	size_t x = 200,
		   y = 100;

	hWnd = CreateWindowEx(
		   WS_EX_WINDOWEDGE, 
		   szClassWindow,
		   _TEXT("Windоw"),
		   WS_OVERLAPPEDWINDOW ^ WS_MINIMIZEBOX ^ WS_MAXIMIZEBOX,
		   CW_USEDEFAULT, CW_USEDEFAULT, x, y,
		   HWND_DESKTOP,
		   NULL, hInstance, NULL);

	if (!hWnd) 
	{
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	static int step = 3;
	int horis = 0,
		vert = 0;

	switch (uMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 100000, NULL);
		break;

	case WM_TIMER:
		if (MessageBox(hWnd, _TEXT("Вы ещё будете работать с приложением ?"), _TEXT("Информация"), MB_YESNO) == IDNO)
			{
				KillTimer(hWnd, 1);
				DestroyWindow(hWnd);
			}
		break;

	case WM_LBUTTONDOWN:
		SetClassLong(hWnd, GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_ARROW));
		break;

	case WM_LBUTTONDBLCLK:
		SetClassLong(hWnd, GCL_HCURSOR, (LONG)LoadCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_CURSOR1)));
		break;

	case WM_RBUTTONDOWN:
		step = rand() % 100 + 10;
		SetClassLong(hWnd, -10, (LONG)CreateSolidBrush(RGB(step + rand() % 100,step + rand() % 100, step + rand() % 100)));
		InvalidateRect(hWnd, NULL, true);
		break;

	case WM_RBUTTONDBLCLK:
		SetClassLong(hWnd, -10, (LONG)(HBRUSH)GetStockObject(WHITE_BRUSH));
		InvalidateRect(hWnd, NULL, true); 
		break;

	case WM_SYSKEYDOWN:
		if (wParam == VK_DOWN)
		{
			ShowWindow(hWnd, SW_SHOWMINIMIZED);
			//SendMessage(hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
		}
		if (wParam == VK_UP)
		{
			//BringWindowToTop(hWnd);
			ShowWindow(hWnd, SW_SHOWMAXIMIZED);
			//SendMessage(hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
		}
		if (wParam == VK_LEFT || wParam == VK_RIGHT) SendMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);
		if (wParam == VK_F4 && MessageBox(hWnd, _TEXT("Вы ещё будете работать с приложением ?"), _TEXT("Информация"), MB_YESNO) == IDNO)
		{
			DestroyWindow(hWnd);
		}
		break;
	
	case WM_KEYDOWN:
		if (wParam == VK_RETURN)
		{
			SetTimer(hWnd, 1, 10, TimerProc);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		
		if (wParam == VK_ESCAPE)
		{
			KillTimer(hWnd, 1);
		}
		break;

	case WM_CLOSE:
		if (MessageBox(hWnd, _TEXT("Вы действительно хотите завершить работу приложения?"), _TEXT("Информация"), MB_YESNO) == IDYES) 
		{
			DestroyWindow(hWnd);
		}
		break;
	
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;
	
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	
	return 0;
}

VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	static int cycle = 0;
	HDC hdc;
	PAINTSTRUCT ps;
	wchar_t str1[100];

	RECT rect_desktop, rect;
	GetClientRect(GetDesktopWindow(), &rect_desktop);
	
	static int  horis = rect_desktop.right - 200,
				vert = 0;

	if (vert == rect_desktop.top && horis < rect_desktop.right - 200)
	{
		horis += 1;
		MoveWindow(hwnd, horis, vert, 200, 100, TRUE);
	}
	if (horis == rect_desktop.right - 200 && vert < rect_desktop.bottom - 138)
	{
		vert += 1;
		MoveWindow(hwnd, horis, vert, 200, 100, TRUE);
	}
	if (vert == rect_desktop.bottom - 138 && horis > rect_desktop.left)
	{
		horis -= 1;
		MoveWindow(hwnd, horis, vert, 200, 100, TRUE);
	}
	if (horis == rect_desktop.left && vert > rect_desktop.top)
	{
		vert -= 1;
		MoveWindow(hwnd, horis, vert, 200, 100, TRUE);
	}
	
	if (cycle % 10 == 0)
	{
		time_t t = time(NULL);

		lstrcpy(str1, _tctime(&t));
		str1[lstrlen(str1) - 1] = '\0';

		hdc = GetDC(hwnd);
		GetClientRect(hwnd, &rect);		
		DrawText(hdc, str1, -1, &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);	
		EndPaint(hwnd, &ps);
		ReleaseDC(hwnd, hdc);
	}

	cycle++;

	//static HANDLE hThread = NULL;
	//if(hThread == NULL) hThread = CreateThread(NULL, 0, ThreadProc, hwnd, 0, NULL);
}

//DWORD WINAPI ThreadProc(LPVOID lpv)
//{
//	HWND hwnd = (HWND)lpv;
//
//	int horis = 0;
//	int vert = 0;
//
//	RECT rect;
//	GetClientRect(GetDesktopWindow(), &rect);
//
//	while (horis++<rect.right - 300) { MoveWindow(hwnd, horis, vert, 300, 300, TRUE); Sleep(30); }
//	while (vert++<rect.bottom - 300) { MoveWindow(hwnd, horis, vert, 300, 300, TRUE); Sleep(30); }
//	while (horis-->0) { MoveWindow(hwnd, horis, vert, 300, 300, TRUE); Sleep(30); }
//	while (vert-->0) { MoveWindow(hwnd, horis, vert, 300, 300, TRUE); Sleep(30); }
//
//	//if (MessageBox(hwnd, _TEXT("Вы действительно хотите завершить работу приложения?"), _TEXT("Информация"), MB_YESNO) == IDYES) {
//	//	DestroyWindow(hwnd);
//	//}
//
//	return 0;
//}