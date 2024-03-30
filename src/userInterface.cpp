#include"userInterface.h"

void MainMenu () 
{
	int option = 0;
	std::cout << "<----------------------------------->" << std::endl;
	std::cout << "1. List Items" << std::endl;
	std::cout << "2. Add Item" << std::endl;
	std::cout << "3. Remove Item" << std::endl;
	std::cout << "4. Add Item Type" << std::endl;
	std::cout << "5. Remove Item Type" << std::endl;

	std::cin >> option;

	switch (option)
	{
	case 1:
		ListItems();
		break;
	case 2:
		
		break;
	default:
		break;
	}
}

void ListItems() 
{
	return;
}