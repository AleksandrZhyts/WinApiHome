#include <windows.h>
#include <iostream>
#include <codecvt>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>
#include <stdio.h> 
#include <time.h>

#define MAX_LEN_STR 1000
#define MIN_LEN_STR 500

void writeToFile(char* source, std::map<std::wstring, int>& freq_dict, std::wstring inf)
{
	std::wofstream ofs(source, std::ios::app);

	ofs << inf << std::endl;

	auto it = freq_dict.begin();

	for (; it != freq_dict.end(); it++)
	{
		ofs << it->first 
			<< L"\t" 
			<< it->second 
			<< std::endl;
	}
	ofs.close();
}

void findMaxMinWords(std::map<std::wstring, int>& freq_dict)
{
	std::map<std::wstring, int> max_words,
								min_words;

	auto it = freq_dict.begin();

	std::wstring temp_max(it->first),
				 temp_min(it->first);

	for (; it != freq_dict.end(); ++it)
	{
		if (temp_max.length() < it->first.length())
		{
			temp_max = it->first;
			max_words.erase(max_words.begin(), max_words.end());
			max_words.insert({ it->first ,it->second });
		}
		else if ((temp_max.length() == it->first.length()))
			max_words.insert({ it->first ,it->second });
		
		if (temp_min.length() > it->first.length())
		{
			temp_min = it->first;
			min_words.erase(min_words.begin(), min_words.end());
			min_words.insert({ it->first ,it->second });
		}
		else if ((temp_min.length() == it->first.length()))
			min_words.insert({ it->first ,it->second });
	}

	writeToFile("result.txt", max_words, L"\nMax words:\n");

	writeToFile("result.txt", min_words, L"\nMin words:\n");
}

bool createDictionary(char* source, std::map<std::wstring, int>& freq_dict)
{
	std::locale::global(std::locale(""));
	std::locale l_utf8(std::locale::classic(), new std::codecvt_utf8<wchar_t>);

	std::ifstream f_in(source, std::ifstream::in);
	f_in.imbue(l_utf8);

	std::wstring word;

	size_t count_words = 0;

	double sum_length_words = 0;

	char cb[MAX_LEN_STR];
	wchar_t wcb[MIN_LEN_STR];

	while (f_in.getline(cb, MAX_LEN_STR))
	{
		MultiByteToWideChar(CP_UTF8, 0, cb, MAX_LEN_STR, wcb, MIN_LEN_STR);

		std::wstring str(wcb);

		int i = -1,
			j = 0;

		while (++i < (str.size() - 1) && str != L"")
		{
			j = 0;
			word.erase();
			while (i < str.size() && ((int)str[i] == 39 || (int)str[i] == 45 || (int)str[i] > 127 || (int)str[i] < 0)
				&& str[i] != L'«' && str[i] != L'»' && (int)str[i] != 65279)
			{
				word += str[i++];
				j++;
			}

			if (j && (word != L"-"))
			{
				if (word[0] == L'-') word.erase(0, 1);
				count_words++;
				sum_length_words += word.length();
				freq_dict[word]++;
			}
		}
	}

	f_in.close();

	std::wofstream ofs("result.txt", std::ios::app);
	
	if (count_words)
		ofs << L"Average length words is: " 
			<< std::setiosflags(std::ios::fixed)
			<< std::setprecision(2) 
			<< sum_length_words / count_words 
		    << std::endl;
	ofs.close();

	writeToFile("dictionary.txt", freq_dict, L"");

	findMaxMinWords(freq_dict);

	return (count_words != 0);
}

void showDictionary(std::map<std::wstring, int>& freq_dict)
{
	auto it = freq_dict.begin();
	for (; it != freq_dict.end(); it++)
	{
		std::wcout << it->first
				   << L"\t"
				   << it->second
				   << std::endl;
	}
}

int main()
{
	clock_t start = clock();
	
	std::map<std::wstring, int> freq_dict;

	createDictionary("karatkevich.txt", freq_dict);
	
	clock_t end = clock();
	
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	
	printf("The time: %f seconds\n", seconds);
	
	//showDictionary(freq_dict);

	system("pause");

	return 0;
}
