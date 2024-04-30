#include <inventory.h>

const char *ITEM_TYPE_FILE = "./res/ItemTypes.DAT";
const char *STOCKED_ITEMS_FILE = "./res/StockedItems.DAT";

void Inventory::AddItem(int option, int quantity)
{

	ItemType* type = TypeAtIndex(option);
	if(type == nullptr) 
	{
		std::cout << "Could not add item type of position: " << option + 1 << ". Invalid option??" << std::endl;
		std::cin.get();
		delete type;
		return;
	}

	std::ofstream stocked_items_file(STOCKED_ITEMS_FILE, std::ios::app);
	if(!stocked_items_file) 
	{
		std::cout << "Couldn't find file StockedItems.DAT. Item addition failed!!!" << std::endl;
		stocked_items_file.close();
		std::cin.get();
		delete type;
		return;
	}

	stocked_items_file << type->GetName() << "," << type->GetPrice() << "," << quantity << std::endl;

	if(stocked_items_file.fail()) 
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
				if(i % 2 == 0) 
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