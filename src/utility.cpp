#include "utility.h"

void ClearInputBuffer()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int NameLengthLimitExceeded(char* name, int limit)
{
	int length = strlen(name);
	return length > limit;
}

int NameMatches(char name1[], char name2[])
{
	ToLower(name1);
	ToLower(name2);
	return !strcmp(name1, name2);
}

void ToLower(char *str)
{
	int i = 0;
	for (i = 0; i < strlen(str); i++)
	{
		str[i] = tolower(str[i]);
	}
}

void ClearConsole()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}