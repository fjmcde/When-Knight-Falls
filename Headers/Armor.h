#pragma once

#include "item.h"

class Armor : public Item
{
	private:
		int defense;
		std::string rarity;
		
	public:
		Armor();
		~Armor();
};



