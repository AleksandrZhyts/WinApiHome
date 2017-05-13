#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
TCHAR szClassWindow[] = TEXT("Каркасное приложение");

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG Msg;
	WNDCLASSEX wcl;
	wcl.cbSize = sizeof(wcl);
	wcl.style = CS_HREDRAW | CS_VREDRAW;
	wcl.lpfnWndProc = WindowProc;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hInstance = hInst;
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcl.lpszMenuName = NULL;
	wcl.lpszClassName = szClassWindow;
	wcl.hIconSm = NULL;
	if (!RegisterClassEx(&wcl))
	{
		return 0;
	}
	hWnd = CreateWindowEx(0, szClassWindow,
						  TEXT("Перечисление дочерних окон"),
						  WS_OVERLAPPEDWINDOW, 
		                  CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
						  NULL, NULL, hInst, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	MessageBox(hWnd,
		       TEXT("Откройте, пожалуйста,\"Калькулятор\", и нажмите <CTRL>"),
		       TEXT("Перечисление дочерних окон"),
		       MB_OK | MB_ICONINFORMATION);
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}
BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam)
{
	HWND hWindow = (HWND)lParam; 
								
	TCHAR caption[MAX_PATH] = { 0 },
		  classname[100] = { 0 }, 
		  text[500] = { 0 };
	//получаем текст заголовка текущего дочернего окна
	GetWindowText(hWnd, caption, 100);
	//получаем имя класса текущего дочернего окна
	GetClassName(hWnd, classname, 100);
	if (lstrlen(caption))
	{
		lstrcat(text, TEXT("Заголовок окна : "));
		lstrcat(text, caption);
		lstrcat(text, TEXT("\n"));
	}
	lstrcat(text, TEXT("Класс окна : "));
	lstrcat(text, classname);
	MessageBox(hWindow, text, TEXT("Перечисление дочерних окон"), MB_OK | MB_ICONINFORMATION);
	return TRUE; // продолжаем перечисление дочерних окон
}
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_CONTROL)
		{
			HWND h = FindWindow(TEXT("CalcFrame"), TEXT("Калькулятор"));
			if (!h)
				MessageBox(hWnd,
					TEXT("Необходимо открыть \"Калькулятор\""),
					TEXT("Ошибка!!!"), MB_OK | MB_ICONSTOP);
			else
				EnumChildWindows(h, EnumChildProc, (LPARAM)hWnd);
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

//#include <windows.h>
//#include <tchar.h>
//
//LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
//TCHAR szClassWindow[] = TEXT("Каркасное приложение");
//
//int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
//{
//	HWND hWnd;
//	MSG Msg;
//	WNDCLASSEX wcl;
//	wcl.cbSize = sizeof(wcl);
//	wcl.style = CS_HREDRAW | CS_VREDRAW;
//	wcl.lpfnWndProc = WindowProc;
//	wcl.cbClsExtra = 0;
//	wcl.cbWndExtra = 0;
//	wcl.hInstance = hInst;
//	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
//	wcl.lpszMenuName = NULL;
//	wcl.lpszClassName = szClassWindow;
//	wcl.hIconSm = NULL;
//	if (!RegisterClassEx(&wcl))
//		return 0;
//	hWnd = CreateWindowEx(0, szClassWindow,
//		                  TEXT("Перечисление окон верхнего уровня"),
//		                  WS_OVERLAPPEDWINDOW, 
//                        CW_USEDEFAULT, CW_USEDEFAULT,	CW_USEDEFAULT, CW_USEDEFAULT, 
//                        NULL, NULL, hInst, NULL);
//	ShowWindow(hWnd, nCmdShow);
//	UpdateWindow(hWnd);
//	while (GetMessage(&Msg, NULL, 0, 0))
//	{
//		TranslateMessage(&Msg);
//		DispatchMessage(&Msg);
//	}
//	return Msg.wParam;
//}
//BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
//{
//	HWND hWindow = (HWND)lParam; 
//	TCHAR caption[MAX_PATH] = { 0 }, 
//		  classname[100] = { 0 },
//		  text[500] = { 0 };
//	//получаем текст заголовка текущего окна верхнего уровня
//	GetWindowText(hWnd, caption, 100);
//	//получаем имя класса текущего окна верхнего уровня
//	GetClassName(hWnd, classname, 100);
//	if (lstrlen(caption))
//	{
//		lstrcat(text, TEXT("Заголовок окна : "));
//		lstrcat(text, caption);
//		lstrcat(text, TEXT("\n"));
//		lstrcat(text, TEXT("Класс окна : "));
//		lstrcat(text, classname);
//		MessageBox(hWindow, text,
//			       TEXT("Перечисление окон верхнего уровня"),
//			       MB_OK | MB_ICONINFORMATION);
//	}
//	return TRUE; //продолжаем перечисление окон верхнего уровня
//}
//LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	switch (message)
//	{
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	case WM_KEYDOWN:
//		if (wParam == VK_CONTROL)
//			EnumWindows(EnumWindowsProc, (LPARAM)hWnd);
//		break;
//	default:
//		return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//	return 0;
//}