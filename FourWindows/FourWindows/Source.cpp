#include <windows.h>

LRESULT CALLBACK WindProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WindProc2(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WindProc3(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WindProc4(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance, LPSTR lpCmdLine, int nCmdShow)
{
	LPWSTR szClassName = L"WindowClass 1";
	LPWSTR szClassName2 = L"WindowClass 2";
	LPWSTR szClassName3 = L"WindowClass 3";
	LPWSTR szClassName4 = L"WindowClass 4";
	
	WNDCLASSEX wndclass1;
	WNDCLASSEX wndclass2;
	WNDCLASSEX wndclass3;
	WNDCLASSEX wndclass4;

	memset(&wndclass1, 0, sizeof(wndclass1));
	memset(&wndclass2, 0, sizeof(wndclass2));
	memset(&wndclass3, 0, sizeof(wndclass3));
	memset(&wndclass4, 0, sizeof(wndclass4));

	wndclass1.cbSize = sizeof(wndclass1);
	wndclass1.lpszClassName = szClassName;
	wndclass1.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wndclass1.lpfnWndProc = WindProc;
	wndclass1.hInstance = hinstance;
	wndclass1.hCursor = LoadCursor(NULL, IDC_WAIT);
	wndclass1.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass1.hbrBackground = CreateSolidBrush(RGB(50, 150, 250)); //(HBRUSH)GetStockObject(WHITE_BRUSH);
															  //wndclass1.lpszMenuName = NULL;
	wndclass1.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	wndclass2.cbSize = sizeof(wndclass2);
	wndclass2.lpszClassName = szClassName2;
	wndclass2.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wndclass2.lpfnWndProc = WindProc2;
	wndclass2.hInstance = hinstance;
	wndclass2.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass2.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass2.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass2.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	wndclass3.cbSize = sizeof(wndclass3);
	wndclass3.lpszClassName = szClassName3;
	wndclass3.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wndclass3.lpfnWndProc = WindProc3;
	wndclass3.hInstance = hinstance;
	wndclass3.hCursor = LoadCursor(NULL, IDC_SIZEALL);
	wndclass3.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass3.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass3.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	wndclass4.cbSize = sizeof(wndclass4);
	wndclass4.lpszClassName = szClassName4;
	wndclass4.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wndclass4.lpfnWndProc = WindProc4;
	wndclass4.hInstance = hinstance;
	wndclass4.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass4.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass4.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass4.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


	if (!RegisterClassEx(&wndclass1) || !RegisterClassEx(&wndclass2) || !RegisterClassEx(&wndclass3) || !RegisterClassEx(&wndclass4))
	{
		return false;
	}

	HWND hWnd = CreateWindowEx(
		WS_EX_TOPMOST,
		szClassName,
		L"Window",
		WS_OVERLAPPEDWINDOW | WS_HSCROLL,
		250, 0, 250, 250,
		NULL,
		NULL,
		hinstance,
		NULL);

	HWND hWnd2 = CreateWindowEx(
		WS_EX_TOPMOST,
		szClassName2,
		L"Window2",
		WS_OVERLAPPEDWINDOW | WS_VSCROLL,
		700, 0, 250, 250,
		NULL,
		NULL,
		hinstance,   
		NULL);

	HWND hWnd3 = CreateWindowEx(
		WS_EX_TOPMOST,
		szClassName3,
		L"Window3",
		WS_OVERLAPPEDWINDOW,
		250, 450, 250, 250,
		NULL,
		NULL,
		hinstance,
		NULL);

	HWND hWnd4 = CreateWindowEx(
		WS_EX_TOPMOST,
		szClassName4,
		L"Window4",
		WS_OVERLAPPEDWINDOW,
		700, 450, 250, 250,
		NULL,
		NULL,
		hinstance,
		NULL);

	if (!hWnd || !hWnd2 || !hWnd3 || !hWnd4)
	{
		return false;
	}

	ShowWindow(hWnd, 1);
	UpdateWindow(hWnd);

	ShowWindow(hWnd2, 1);
	UpdateWindow(hWnd2);

	ShowWindow(hWnd3, 1);
	UpdateWindow(hWnd3);

	ShowWindow(hWnd4, 1);
	UpdateWindow(hWnd4);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WindProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM iParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;

	switch (iMsg)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, L"Позвольте начать", -1, &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, iMsg, wParam, iParam);
	}

	return 0;
}

LRESULT CALLBACK WindProc2(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM iParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	static bool hide = false;

	switch (iMsg)
	{
	case WM_CREATE:
		SetTimer(hwnd, 1, 1000, NULL);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, L"Моё, второе окно", -1, &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		EndPaint(hwnd, &ps);
		break;

	case WM_TIMER:
		if (hide) ShowWindow(hwnd, SW_SHOW), hide = false;
		else ShowWindow(hwnd, SW_HIDE), hide = true;

		SetClassLong(hwnd, -10, (LONG)CreateSolidBrush(RGB(2*(rand() % 100), (2*rand() % 100), 2*(rand() % 100))));
		InvalidateRect(hwnd, NULL, true);
		break;

	case WM_DESTROY:
		KillTimer(hwnd, 1);
		break;
	default:
		return DefWindowProc(hwnd, iMsg, wParam, iParam);
	}

	return 0;
}

LRESULT CALLBACK WindProc3(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM iParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	static bool hide = false;

	switch (iMsg)
	{
	case WM_CREATE:
		SetTimer(hwnd, 1, 1500, NULL);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, L"Hello, Step", -1, &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		EndPaint(hwnd, &ps);
		break;

	case WM_TIMER:
		if (hide) ShowWindow(hwnd, SW_SHOW), hide = false;
		else ShowWindow(hwnd, SW_HIDE), hide = true;

		SetClassLong(hwnd, -10, (LONG)CreateSolidBrush(RGB(rand() % 90, rand() % 90, rand() % 90)));
		InvalidateRect(hwnd, NULL, true);
		break;

	case WM_DESTROY:
		KillTimer(hwnd, 1);
		break;
	default:
		return DefWindowProc(hwnd, iMsg, wParam, iParam);
	}

	return 0;
}

LRESULT CALLBACK WindProc4(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM iParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	static bool hide = false;

	switch (iMsg)
	{
	case WM_CREATE:
		SetTimer(hwnd, 1, 1800, NULL);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, L"Hello, my teacher", -1, &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		EndPaint(hwnd, &ps);
		break;

	case WM_TIMER:
		if (hide) ShowWindow(hwnd, SW_SHOW), hide = false;
		else ShowWindow(hwnd, SW_HIDE), hide = true;

		SetClassLong(hwnd, -10, (LONG)CreateSolidBrush(RGB(rand() % 150, rand() % 150, rand() % 150)));
		InvalidateRect(hwnd, NULL, true);
		break;

	case WM_DESTROY:
		KillTimer(hwnd, 1);
		break;
	default:
		return DefWindowProc(hwnd, iMsg, wParam, iParam);
	}

	return 0;
}
