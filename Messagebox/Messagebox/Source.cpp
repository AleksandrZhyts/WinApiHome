#include "windows.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MessageBoxW(NULL, L"���� ����� �������������� !(�����)", L"FirstBox", MB_OKCANCEL | MB_ICONWARNING);
	MessageBoxW(NULL, L"��� ����� !", L"SecondBox", MB_YESNO | MB_ICONINFORMATION);
	MessageBoxW(NULL, L"������� ���� ?", L"ThirdBox", MB_YESNOCANCEL | MB_ICONQUESTION);
	MessageBoxW(NULL, L"Error !", L"ForthBox", MB_OK | MB_ICONERROR);

	return 0;
}