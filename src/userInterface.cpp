#include "userInterface.h"

#define ITEM_NAME_LIMIT 30
void MainMenu()
{
	ClearConsole();
	int option = 0;
	std::cout << "Inventory Management System" << std::endl;
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
	case 2:
		AddItem();
		break;
	case 3:
		RemoveItem();
		break;
	case 4:
		ListItemTypes();
		break;
	case 5:
		AddItemType();
		break;
	case 6:
		RemoveItemType();
		break;
	case 7:
		Exit();
		break;
	default:
		break;
	}
}

void ListItems()
{
	ClearConsole();
	std::cout << "Inventory Item List" << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	Inventory inv;
	inv.ListItems();
	std::cin.get();
	return;
}

void AddItem()
{
	ClearConsole();
	Inventory inv;
	int option = 0;
	int quantity = 0;
	std::cout << "Add Item Menu" << std::endl;
	std::cout << "-----------------------" << std::endl;
	std::cout << "Which type of item would you like to add to the inventory?" << std::endl;
	inv.ListItemTypes();
	while (1)
	{
		std::cin >> option;
		ClearInputBuffer();
		if (!(option > 0))
		{
			std::cout << "Not a valid option type. Please try again!!!" << std::endl;
			continue;
		}
		break;
	}

	std::cout << "Enter the quantity of item no: " << option << " that you want to add to the inventory." << std::endl;
	while (1)
	{
		std::cin >> quantity;
		ClearInputBuffer();
		if (!(option > -1))
		{
			std::cout << "Not a valid amount of quantity. Please try again!!!" << std::endl;
			continue;
		}
		break;
	}
	inv.AddItem(option - 1, quantity);
	std::cin.get();
}

void RemoveItem()
{
	Inventory inv;
	ClearConsole();
	int option = 0;
	int quantity_to_remove = 0;
	std::cout << "Remove Item Menu" << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::cout << "Which item would you like to remove?" << std::endl;

	// Print item types
	inv.ListItemTypes();

	while (1)
	{
		std::cin >> option;
		ClearInputBuffer();
		if (!(option > 0))
		{
			std::cout << "Invalid option. Please try again!!!";
			std::cin.get();
			continue;
		}
		break;
	}

	std::cout << "How many of this item would you like to remove?" << std::endl;
	std::cin >> quantity_to_remove;
	ClearInputBuffer();
	if (quantity_to_remove < 0)
	{
		std::cout << "Invalid quantity amount!!!" << std::endl;
		return;
	}
	inv.RemoveItem(option - 1, quantity_to_remove);
}

void AddItemType()
{
	ClearConsole();
	std::cout << "Add Item Type" << std::endl;
	std::cout << "------------------" << std::endl;
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
	std::cout << "Item Type List" << std::endl
			  << std::endl;
	Inventory inv;
	inv.ListItemTypes();
	std::cin.get();
}

void RemoveItemType() 
{
	ClearConsole();
	Inventory inv;
	int option = 0;
	std::cout << "Remove Item Type Menu" << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::cout << "Which item would you like to remove?" << std::endl;

	// Print item types
	inv.ListItemTypes();

	while (1)
	{
		std::cin >> option;
		ClearInputBuffer();
		if (!(option > 0))
		{
			std::cout << "Invalid option. Please try again!!!";
			std::cin.get();
			continue;
		}
		break;
	}
	
	inv.RemoveItemType(option - 1);
}

void Exit()
{
	ClearConsole();
	while (1)
	{
		char option = ' ';
		std::cout << "Are you sure you want to exit the program?Y/N" << std::endl;
		std::cin.get(option);
		option = tolower(option);
		if (option == 'y')
		{
			exit(0);
		}
		else if (option == 'n')
		{
			return;
		}
		std::cout << "Invalid Choice. Try again!!" << std::endl;
		std::cin.get();
		ClearInputBuffer();
		continue;
	}
}