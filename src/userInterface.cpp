#include "userInterface.h"

#define ITEM_NAME_LIMIT 30
void MainMenu()
{
	int option = 0;
	std::cout << "<----------------------------------->" << std::endl;
	std::cout << "1. List Items" << std::endl;
	std::cout << "2. Add Item" << std::endl;
	std::cout << "3. Remove Item" << std::endl;
	std::cout << "4. List Item Types" << std::endl;
	std::cout << "5. Add Item Type" << std::endl;
	std::cout << "6. Remove Item Type" << std::endl;
	std::cout << "7. Exit" << std::endl;

	std::cin >> option;
	ClearInputBuffer();

	switch (option)
	{
	case 1:
		ListItems();
		break;
	case 4:
		ListItemTypes();
		break;
	case 5:
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

	Inventory inv;
	ItemType item_type;
	std::string item_type_name;
	std::string item_type_price;
	float item_type_price_flt = 0.0;

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

	item_type.SetName(item_type_name);

	while (1)
	{
		std::cout << "Enter the price of item type: " << item_type_name << std::endl;
		std::getline(std::cin, item_type_price);

		try
		{
			std::size_t pos;

			item_type_price_flt = std::stof(item_type_price, &pos);
			if (pos < item_type_price.size())
			{
				throw std::invalid_argument("Extra characters found after the numeric value!");
			}
			break;
		}
		catch (const std::invalid_argument &e)
		{
			std::cout << "Only numeric values can be entered for item price. Please try again!" << std::endl;
			item_type_price = "";
			item_type_price_flt = 0;
			continue;
		}
	}

	item_type.SetPrice(item_type_price_flt);

	inv.AddItemType(item_type);

	std::cin.get();
}

void ListItemTypes() 
{
	ClearConsole();
	std::cout << "Item Type List" << std::endl << std::endl;
	Inventory inv;
	inv.ListItemTypes();
	std::cin.get();
}