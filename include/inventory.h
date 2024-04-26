#pragma once
#include <iostream>
#include <fstream>
#include "itemType.h"

const char* ITEM_TYPE_FILE = "./res/ItemTypes.DAT";

class Inventory
{
	public:
		void AddItemType(ItemType type);
};