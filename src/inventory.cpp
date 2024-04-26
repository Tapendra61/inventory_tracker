#include <inventory.h>

void Inventory::AddItemType(ItemType type)
{
	std::ofstream item_types_file(ITEM_TYPE_FILE, std::ios::app | std::ios::binary);
	
	if (!item_types_file)
	{
		std::cout << "Error opening file ItemType.DAT." << std::endl;
		std::cin.get();
		return;
	}
	item_types_file << type.GetName() << type.GetPrice();
	
	if(item_types_file.fail()) 
	{
		std::cout << "Failed to write data to the file!!!" << std::endl;
		std::cin.get();
		return;
	}

	item_types_file.close();
}