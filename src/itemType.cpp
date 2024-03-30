#include "itemType.h"

ItemType::ItemType() {
	memset(name, '\0', sizeof(name));
	price = 0.0;
}

char* ItemType::GetName() 
{
	return name;
}

void ItemType::SetName(char value[30]) 
{
	strcpy(name, value);
}