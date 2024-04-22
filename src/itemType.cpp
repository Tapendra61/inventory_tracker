#include "itemType.h"

ItemType::ItemType() {
	name = "";
	price = 0.0;
}

std::string ItemType::GetName() 
{
	return name;
}

void ItemType::SetName(std::string value)
{
	name = value;
}