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

float ItemType::GetPrice() 
{
	return price;
}

void ItemType::SetPrice(float value) 
{
	price = value;
}