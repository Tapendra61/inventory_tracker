#include <inventory.h>

const char *ITEM_TYPE_FILE = "./res/ItemTypes.DAT";
const char *STOCKED_ITEMS_FILE = "./res/StockedItems.DAT";

void Inventory::ListItems()
{
	std::string line = "";

	std::ifstream stocked_items_file(STOCKED_ITEMS_FILE, std::ios::in);

	if (!stocked_items_file)
	{
		std::cout << "Error opening file StockedItems.DAT." << std::endl;
		std::cin.get();
		stocked_items_file.close();
		return;
	}

	int i = 0;
	int count = 0;
	while (std::getline(stocked_items_file, line))
	{
		count++;
		std::stringstream stream(line);
		std::string token;

		while (std::getline(stream, token, ','))
		{
			if (i % 3 == 0)
			{
				std::cout << count << "." << std::endl;
				std::cout << "  Item Name: " << token << std::endl;
				i++;
				continue;
			}
			else if (i % 3 == 1)
			{
				std::cout << "  Item Price: " << token << std::endl;
				i++;
				continue;
			}
			std::cout << "  Item Quantity: " << token << std::endl;
			i++;
			std::cout << std::endl;
		}
	}

	stocked_items_file.close();
}

void Inventory::AddItem(int option, int quantity)
{
	ItemType *type = TypeAtIndex(option);
	std::vector<StockedItem> items_in_stock;
	if (type == nullptr)
	{
		std::cout << "Could not add item type of position: " << option + 1 << ". Invalid option??" << std::endl;
		std::cin.get();
		delete type;
		return;
	}

	// Read Items from StockedItems file and store it as vector
	std::ifstream stocked_items_file_read(STOCKED_ITEMS_FILE, std::ios::in);
	if (!stocked_items_file_read)
	{
		std::cout << "Couldn't find file StockedItems.DAT. Item addition failed!!!" << std::endl;
		stocked_items_file_read.close();
		std::cin.get();
		delete type;
		return;
	}

	std::string line = "";

	int i = 0;
	int count = 0;
	while (std::getline(stocked_items_file_read, line))
	{
		count++;
		StockedItem read_stocked_item;
		std::stringstream stream(line);
		std::string token;

		while (std::getline(stream, token, ','))
		{
			if (i % 3 == 0)
			{
				read_stocked_item.name = token;
				i++;
				continue;
			}
			else if (i % 3 == 1)
			{
				read_stocked_item.price = std::stof(token);
			}
			read_stocked_item.quantity = std::stoi(token);
			i++;
		}
		items_in_stock.push_back(read_stocked_item);
	}

	stocked_items_file_read.close();

	std::ofstream stocked_items_file(STOCKED_ITEMS_FILE, std::ios::app);
	if (!stocked_items_file)
	{
		std::cout << "Couldn't find file StockedItems.DAT. Item addition failed!!!" << std::endl;
		stocked_items_file.close();
		std::cin.get();
		delete type;
		return;
	}

	int match_found = 0;
	for (StockedItem &item : items_in_stock)
	{
		if (item.name == type->GetName())
		{
			match_found = 1;
			item.quantity += quantity;
		}
	}

	// The item to be added was not found in inventory/stock
	if (!match_found)
	{
		StockedItem item;
		item.name = type->GetName();
		item.price = type->GetPrice();
		item.quantity = quantity;
		items_in_stock.push_back(item);
	}

	if (StockedItemsFileIsEmpty())
	{
		stocked_items_file << type->GetName() << "," << type->GetPrice() << "," << quantity << std::endl;
		std::cout << "Successfully added item to the inventory." << std::endl;
		delete type;
		stocked_items_file.close();
		return;
	}
	else
	{
		stocked_items_file.close();
		stocked_items_file.open(STOCKED_ITEMS_FILE, std::ios::trunc);
		for (StockedItem item : items_in_stock)
		{
			stocked_items_file << item.name << "," << item.price << "," << item.quantity << std::endl;
		}
	}

	if (stocked_items_file.fail())
	{
		std::cout << "Failed to write data to the file!!!" << std::endl;
		std::cin.get();
		delete type;
		stocked_items_file.close();
		return;
	}

	std::cout << "Successfully added item to the inventory." << std::endl;
	delete type;
	stocked_items_file.close();
	return;
}

void Inventory::RemoveItem(int option, int quantity_to_remove)
{
	if (StockedItemsFileIsEmpty())
	{
		std::cout << "The are currently no items in stock." << std::endl;
		std::cin.get();
		return;
	}
	ItemType *type = TypeAtIndex(option);
	std::vector<StockedItem> stocked_items;

	std::ifstream stocked_items_file(STOCKED_ITEMS_FILE, std::ios::in);
	if (!stocked_items_file)
	{
		std::cout << "Error opening file: StockedItems.DAT." << std::endl;
		std::cin.get();
		stocked_items_file.close();
		delete type;
		return;
	}

	std::string line = "";
	int i = 0;
	while (std::getline(stocked_items_file, line))
	{
		std::stringstream stream(line);
		std::string token;
		StockedItem read_item;

		while (std::getline(stream, token, ','))
		{
			if (i % 3 == 0)
			{
				read_item.name = token;
				i++;
				continue;
			}
			else if (i % 3 == 1)
			{
				read_item.price = std::stof(token);
				i++;
				continue;
			}
			read_item.quantity = std::stoi(token);
			i++;
		}
		stocked_items.push_back(read_item);
	}

	stocked_items_file.close();

	for (StockedItem &item : stocked_items)
	{
		if (item.name == type->GetName())
		{
			if (item.quantity >= quantity_to_remove)
			{
				item.quantity -= quantity_to_remove;
			}
			else
			{
				std::cout << "The item you are trying to remove has quantity of less than: " << quantity_to_remove << std::endl;
				std::cin.get();
				delete type;
				return;
			}
		}
	}

	std::ofstream stocked_items_file_write(STOCKED_ITEMS_FILE, std::ios::trunc);
	if (!stocked_items_file_write)
	{
		std::cout << "Error opening file: StockedItems.DAT" << std::endl;
		std::cin.get();
		stocked_items_file_write.close();
		delete type;
		return;
	}

	for (StockedItem &item : stocked_items)
	{
		if (item.quantity == 0)
		{
			continue;
		}
		stocked_items_file_write << item.name << "," << item.price << "," << item.quantity << std::endl;
	}

	stocked_items_file_write.close();
	std::cout << "Successfully removed " << quantity_to_remove << " " << type->GetName() << " from inventory." << std::endl;
	delete type;
	std::cin.get();
}

void Inventory::AddItemType(ItemType type)
{
	if (ItemTypeExists(type))
	{
		std::cout << "An item type with name: " << type.GetName() << " already exists!!!" << std::endl;
		return;
	}

	std::ofstream item_types_file(ITEM_TYPE_FILE, std::ios::app | std::ios::binary);

	if (!item_types_file)
	{
		std::cout << "Error opening file ItemType.DAT." << std::endl;
		std::cin.get();
		item_types_file.close();
		return;
	}
	item_types_file << type.GetName() << "," << type.GetPrice() << std::endl;

	if (item_types_file.fail())
	{
		std::cout << "Failed to write data to the file!!!" << std::endl;
		std::cin.get();
		item_types_file.close();
		return;
	}

	item_types_file.close();
}

void Inventory::RemoveItemType(int option)
{
	if (ItemTypesFileIsEmpty())
	{
		std::cout << "There are currently no item types to remove." << std::endl;
		std::cin.get();
		return;
	}
	ItemType *type = TypeAtIndex(option);

	// Read the stocked items file to see if an item the type being removed exists
	// If it does, we cant remove that type of item yet
	int flag = 0;
	std::string line = "";
	std::ifstream stocked_items_file(STOCKED_ITEMS_FILE, std::ios::in);
	if (!stocked_items_file)
	{
		std::cout << "Error opening file: SockedItems.DAT!!!" << std::endl;
		std::cin.get();
		delete type;
		stocked_items_file.close();
		return;
	}

	while (std::getline(stocked_items_file, line))
	{
		std::stringstream stream(line);
		std::string token;
		while (std::getline(stream, token, ','))
		{
			if (type->GetName() == token)
			{
				flag = 1;
			}
		}
	}

	stocked_items_file.close();
	if (flag)
	{
		std::cout << "This item type cannot be removed as it is currently stocked in inventory." << std::endl;
		std::cin.get();
		delete type;
		return;
	}

	// Remove the item type from ItemTypes.DAT
	std::vector<ItemType> item_types;
	std::ifstream item_type_file(ITEM_TYPE_FILE, std::ios::in);
	int i = 0;
	if (!item_type_file)
	{
		std::cout << "Error opening file: ItemTypes.DAT!!!" << std::endl;
		std::cin.get();
		delete type;
		item_type_file.close();
		return;
	}

	line = "";
	while (std::getline(item_type_file, line))
	{
		std::stringstream stream(line);
		std::string token;
		ItemType item_type;
		while (std::getline(stream, token, ','))
		{
			if (i % 2 == 0)
			{
				item_type.SetName(token);
				i++;
				continue;
			}
			item_type.SetPrice(std::stof(token));
			i++;
		}
		item_types.push_back(item_type);
	}

	item_type_file.close();

	// Re-write the ItemTypes.DAT file without the ItemType to be removed
	std::ofstream item_type_file_write(ITEM_TYPE_FILE, std::ios::trunc);
	if (!item_type_file_write)
	{
		std::cout << "Error opening file: ItemTypes.DAT!!!" << std::endl;
		std::cin.get();
		delete type;
		item_type_file_write.close();
		return;
	}

	for (ItemType &item : item_types)
	{
		if (item.GetName() == type->GetName())
		{
			continue;
		}
		item_type_file_write << item.GetName() << "," << item.GetPrice() << std::endl;
	}
	if (item_type_file_write.fail())
	{
		std::cout << "Failed to write ItemTypes to file: ItemTypes.DAT!!!" << std::endl;
		delete type;
		item_type_file_write.close();
		std::cin.get();
		return;
	}
	delete type;
	item_type_file_write.close();
	std::cout << "Succesfully removed ItemType." << std::endl;
	std::cin.get();
	return;
}

void Inventory::ListItemTypes()
{
	std::string line = "";

	std::ifstream item_types_file(ITEM_TYPE_FILE, std::ios::in);

	if (!item_types_file)
	{
		std::cout << "Error opening file ItemType.DAT." << std::endl;
		std::cin.get();
		item_types_file.close();
		return;
	}

	int i = 0;
	int count = 0;
	while (std::getline(item_types_file, line))
	{
		count++;
		std::stringstream stream(line);
		std::string token;

		while (std::getline(stream, token, ','))
		{
			if (i % 2 == 0)
			{
				std::cout << count << "." << std::endl;
				std::cout << "  Item Name: " << token << std::endl;
				i++;
				continue;
			}

			std::cout << "  Item Price: " << token << std::endl;
			i++;
			std::cout << std::endl;
		}
	}

	item_types_file.close();
}

int Inventory::ItemTypeExists(ItemType type)
{
	int flag = 0;
	std::string line = "";
	std::string input_item_name = type.GetName();

	std::ifstream item_types_file(ITEM_TYPE_FILE, std::ios::in);
	if (!item_types_file)
	{
		std::cout << "Error reading from file: ItemTypes.DAT" << std::endl;
		item_types_file.close();
		return 1;
	}

	int i = 0;

	while (std::getline(item_types_file, line))
	{
		std::stringstream stream(line);
		std::string token;

		while (std::getline(stream, token, ','))
		{
			if (i % 2 == 0)
			{
				if (NameMatches(&token, &input_item_name))
				{
					flag = 1;
				}
				i++;
				continue;
			}
			i++;
			std::cout << std::endl;
		}
	}

	item_types_file.close();
	return flag;
}

ItemType *Inventory::TypeAtIndex(int index)
{
	ItemType *type = new ItemType();
	std::ifstream item_type_file(ITEM_TYPE_FILE, std::ios::in);
	if (!item_type_file)
	{
		std::cout << "Error reading file: ItemTypes.DAT!!!" << std::endl;
		item_type_file.close();
		std::cin.get();
		type = nullptr;
		return type;
	}

	std::string line = "";
	int i = 0;
	int count = 0;
	while (std::getline(item_type_file, line))
	{
		if (count == index)
		{
			std::stringstream stream(line);
			std::string token;
			while (std::getline(stream, token, ','))
			{
				if (i % 2 == 0)
				{
					type->SetName(token);
					i++;
					continue;
				}
				type->SetPrice(std::stof(token));
				i++;
			}
			item_type_file.close();
			return type;
		}
		count++;
	}
	item_type_file.close();
	type = nullptr;
	return type;
}

int Inventory::StockedItemsFileIsEmpty()
{
	std::ifstream file(STOCKED_ITEMS_FILE, std::ios::in);
	if (!file)
	{
		std::cout << "Faile to open file StockedItems.DAT" << std::endl;
		std::cin.get();
		file.close();
		return -1;
	}
	file.seekg(0, std::ios::end);
	int final_pos = file.tellg();
	file.seekg(0, std::ios::beg);
	int init_pos = file.tellg();

	return (final_pos - init_pos) == 0;
}

int Inventory::ItemTypesFileIsEmpty()
{
	std::ifstream file(ITEM_TYPE_FILE, std::ios::in);
	if (!file)
	{
		std::cout << "Faile to open file ItemTypes.DAT" << std::endl;
		std::cin.get();
		file.close();
		return -1;
	}
	file.seekg(0, std::ios::end);
	int final_pos = file.tellg();
	file.seekg(0, std::ios::beg);
	int init_pos = file.tellg();

	return (final_pos - init_pos) == 0;
}