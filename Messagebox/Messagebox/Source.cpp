#include "windows.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MessageBoxW(NULL, L"Диск будет отформатирован !(Шутка)", L"FirstBox", MB_OKCANCEL | MB_ICONWARNING);
	MessageBoxW(NULL, L"Это важно !", L"SecondBox", MB_YESNO | MB_ICONINFORMATION);
	MessageBoxW(NULL, L"Удалить файл ?", L"ThirdBox", MB_YESNOCANCEL | MB_ICONQUESTION);
	MessageBoxW(NULL, L"Error !", L"ForthBox", MB_OK | MB_ICONERROR);

	return 0;
}