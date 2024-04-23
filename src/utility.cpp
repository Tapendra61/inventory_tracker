#include "utility.h"

void ClearInputBuffer()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int NameMatches(std::string *name1, std::string *name2)
{
	std::string value1;
	std::string value2;
	
	for(char c : *name1) 
	{
		value1 += tolower(c);
	}

	for(char c : *name2) 
	{
		value2 += tolower(c);
	}

	return value1 == value2;
}

void ClearConsole()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

int IsAlphabetical(std::string *word)
{
	int flag = 1;
	for (char c : *word)
	{
		if (isalpha(c) || c == ' ')
			continue;
		else
			flag = 0;
	}

	return flag;
}