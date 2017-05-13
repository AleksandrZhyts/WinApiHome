#include <windows.h>
#include <iostream>
#include <codecvt>
#include <fstream>

#define MAX_LEN_STR 200
#define MIN_LEN_STR 100

void mbToWcsUse_getline()
{
	setlocale(LC_ALL, ".1251");

	std::ifstream srcfile("text.txt");

	if (!srcfile)
	{
		std::cerr << "don't open file\n";
		exit(1);
	}

	std::wofstream fout("text1.txt");
	std::locale loc(std::locale::classic(), new	std::codecvt_utf8<wchar_t>);
	fout.imbue(loc);

	std::string buffer;
	size_t length;

	while (!srcfile.eof())
	{
		getline(srcfile, buffer);

		length = std::mbstowcs(NULL, buffer.c_str(), 0) + 1;

		wchar_t *ptr = new wchar_t[length];

		std::mbstowcs(ptr, buffer.c_str(), length);

		fout << ptr << std::endl;

		delete[] ptr;
	}

	fout.close();
	srcfile.close();
}

/*
void copy() {
	std::wstreambuf *psbuf, *backup;
	std::wifstream filestr;
	filestr.open("d:\\text.txt");

	backup = std::wcin.rdbuf();     // back up cout's streambuf

	psbuf = filestr.rdbuf();        // get file's streambuf
	std::wcin.rdbuf(psbuf);         // assign streambuf to cout

	std::cout << "This is written to the file";

	std::wcin.rdbuf(backup);        // restore cout's original streambuf

	filestr.close();
}
*/
void mbToWcsUse_fgets()
{
	FILE *srcfile;
	if (fopen_s(&srcfile, "text.txt", "r"))
	{
		std::cerr << "don't open file\n";
		exit(1);
	}

	std::wofstream fout("text2.txt");
	std::locale loc(std::locale::classic(), new	std::codecvt_utf8<wchar_t>);
	fout.imbue(loc);

	char buffer[MAX_LEN_STR];
	int length;

	while (!feof(srcfile))
	{
		fgets(buffer, MAX_LEN_STR, srcfile);

		length = MultiByteToWideChar(CP_ACP, 0, buffer, -1, NULL, 0);

		wchar_t *ptr = new wchar_t[length];

		MultiByteToWideChar(CP_ACP, 0, buffer, -1, ptr, length);

		fout << ptr;

		delete[] ptr;
	}

	fout.close();
	fclose(srcfile);
}

void mbToWcsUse_read()
{
	setlocale(LC_ALL, ".1251");

	std::ifstream srcfile;

	srcfile.open("text.txt", std::ios::binary);

	srcfile.seekg(0, std::ios::end);

	size_t length = srcfile.tellg();

	srcfile.seekg(0, std::ios::beg);
	char* buf = new char[length + 1];

	srcfile.read(buf, length);
	buf[length] = '\0';

	length = std::mbstowcs(NULL, buf, 0) + 1;

	wchar_t *ptr = new wchar_t[length];

	std::mbstowcs(ptr, buf, length);

	std::wofstream fout("text3.txt");
	std::locale loc(std::locale::classic(), new	std::codecvt_utf8<wchar_t>);
	fout.imbue(loc);

	fout << ptr << std::endl;

	fout.close();
	srcfile.close();

	delete[] buf;
	delete[] ptr;
}

void clean_input()
{
	std::cin.clear();
	if (std::cin.rdbuf()->in_avail() != 0)
		while (std::cin.get() != '\n');
}

void menu()
{
	int userChoise = 0;

	do
	{
		clean_input();

		switch (userChoise)
		{
		case 1: mbToWcsUse_getline();
				system("pause");
			break;

		case 2:	mbToWcsUse_fgets();
				system("pause");
			break;

		case 3:	mbToWcsUse_read();
				system("pause");
			break;

		default: break;
		}

		system("cls");

		std::cout << "\t1 - use getline\n"
				  << "\t2 - use fgets\n"
				  << "\t3 - use read\n"
				  << "\tq - exit\n"
				  << ">> ";

	} while (std::cin >> userChoise);

	clean_input();
}

void show_file(char* fileName)
{
	std::locale::global(std::locale(""));
	std::locale l_utf8(std::locale::classic(), new std::codecvt_utf8<wchar_t>);

	std::ifstream f_in(fileName, std::ifstream::in);
	f_in.imbue(l_utf8);

	char cb[MAX_LEN_STR];
	wchar_t wcb[MIN_LEN_STR];

	while (f_in.getline(cb, MAX_LEN_STR))
	{
		MultiByteToWideChar(CP_UTF8, 0, cb, MAX_LEN_STR, wcb, MIN_LEN_STR);
		std::wcout << wcb << std::endl;
	}

	f_in.close();
}

int main()
{
	//using namespace std;
	//wcin.peek();

	//cout << wcin.rdbuf()->in_avail() << endl;
	//cout << cin.rdbuf()->in_avail() << endl;

	menu();
	//copy();
	//show_file("text1.txt");
	//show_file("text2.txt");
	//show_file("text3.txt");
	system("pause");

	return 0;
}