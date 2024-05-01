#pragma once
#include <iostream>
#include <fstream>
#include<sstream>
#include "itemType.h"
#include"stockedItem.h"
#include"utility.h"
#include<vector>

extern const char* ITEM_TYPE_FILE;
extern const char* STOCKED_ITEMS_FILE;

class Inventory
{
	public:
		void ListItems();
		void AddItem(int option, int quantity);
		void AddItemType(ItemType type);
		void ListItemTypes();
		int ItemTypeExists(ItemType type);
		ItemType* TypeAtIndex(int index);
		void RemoveItem(int option, int quantity_to_remove);
		void RemoveItemType(int option);
		int ItemTypesFileIsEmpty();
		int StockedItemsFileIsEmpty();
};