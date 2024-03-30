#pragma once
#include<cstring>

class ItemType {
	private:
		char name[30];
		float price;

	public:
		ItemType();
		char* GetName();
		void SetName(char value[30]);
		float GetPrice();
		void SetPrice(float value);
};