#include <windows.h>
#include <iostream>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	wchar_t d_str[100];
	int num,
		left = 1,
		right = 10,
		iMsg;

	iMsg = MessageBoxW(NULL, L"Хотите поиграть ?", L"Угадайка", MB_YESNO | MB_ICONQUESTION);

	if (iMsg == IDNO) return 0;

	MessageBoxW(NULL, L"Загадайте число от 1 до 10", L"Угадайка", MB_OK | MB_ICONWARNING);

	do
	{
		num = (right - left) / 2 + left;

		swprintf(d_str, 100, L"Вы загадали число %d ?", num);
		iMsg = MessageBoxW(NULL, d_str, L"Угадайка", MB_YESNO | MB_ICONQUESTION);
		if (iMsg == IDCANCEL) return 0;
		if (iMsg == IDYES)
		{
			iMsg = MessageBoxW(NULL, L"Я угадал!", L"Угадайка", MB_OK | MB_ICONWARNING);
			return 0;
		}
		if (iMsg == IDNO)
		{
			swprintf(d_str, 100, L"Вы загадали число больше чем %d ?", num);
			iMsg = MessageBoxW(NULL, d_str, L"Угадайка", MB_YESNO | MB_ICONQUESTION);
			if (iMsg == IDYES) left = num + (right - num == 1);
			else if (right - num > 1) right = num;
			else
			{
				iMsg = MessageBoxW(NULL, L"Вы соврали!", L"Угадайка", MB_OK | MB_ICONSTOP);
				return 0;
			}
		}
	} while (right - left > 1);

	swprintf(d_str, 100, L"Ваше число %d !", left);
	MessageBoxW(NULL, d_str, L"Угадайка", MB_OK | MB_ICONWARNING);

	return 0;
}