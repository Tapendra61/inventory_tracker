#pragma once
#include <iostream>
#include <fstream>
#include<sstream>
#include "itemType.h"

extern const char* ITEM_TYPE_FILE;

class Inventory
{
	public:
		void AddItemType(ItemType type);
		void ListItemTypes();
};