#include "userInterface.h"

#define ITEM_NAME_LIMIT 30
void MainMenu()
{
	int option = 0;
	std::cout << "<----------------------------------->" << std::endl;
	std::cout << "1. List Items" << std::endl;
	std::cout << "2. Add Item" << std::endl;
	std::cout << "3. Remove Item" << std::endl;
	std::cout << "4. Add Item Type" << std::endl;
	std::cout << "5. Remove Item Type" << std::endl;
	std::cout << "6. Exit" << std::endl;

	std::cin >> option;

	switch (option)
	{
	case 1:
		ListItems();
		break;
	case 4:
		ClearInputBuffer();
		AddItemType();
		break;
	default:
		break;
	}
}

void ListItems()
{
	return;
}

void AddItemType()
{
	ClearConsole();
	ItemType item_type;
	std::string item_type_name;

	while (1)
	{
		std::cout << "Enter the name of the item type you want to add:" << std::endl;
		std::getline(std::cin, item_type_name);

		if (item_type_name.length() > 30 || !IsAlphabetical(&item_type_name))
		{
			std::cout << "The name of item type must have only 30 characters or less and should contain only alphabets." << std::endl;
			ClearInputBuffer();
			continue;
		}
		else
			break;
	}

	std::cout << "Name is valid: " << item_type_name << std::endl;

	std::cin.get();
}