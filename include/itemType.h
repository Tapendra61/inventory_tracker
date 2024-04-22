#pragma once
#include<string>

class ItemType {
	private:
		std::string name;
		float price;

	public:
		ItemType();
		std::string GetName();
		void SetName(std::string name);
		float GetPrice();
		void SetPrice(float value);
};