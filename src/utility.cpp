#include"utility.h"

void ClearInputBuffer() 
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int NameLengthLimitExceeded(char name[], int limit) 
{
	int length = strlen(name);
	return length > limit;
}