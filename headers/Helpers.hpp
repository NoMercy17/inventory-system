#pragma once
#include <vector>
#include <memory>
#include <string>
#include <type_traits>
#include <cassert>

class Item;
class Character;


void dropItem(Character& character, std::vector<std::unique_ptr<Item>>& inventory, Item* itemToRemove);


template<typename TargetItem>
TargetItem* findItem(const std::vector<std::unique_ptr<Item>>& inventory, const std::string& name = "")
{
	// guard for incorrect use of the findItem function
	static_assert(std::is_base_of<Item, TargetItem>::value, "The items from the vector must be derived from Item (Weapon, Armor, Potion)");
	
	// for c++17
	//static_assert(std::is_base_of_v<Item, TargetItem>, "The items from the vector must be derived from Item (Weapon, Armor, Potion)");;

	for(const auto& item: inventory)
	{
		if(auto* casted = dynamic_cast<TargetItem*>(item.get()))
		{
			if(name.empty() || casted->getName() == name)
				return casted;
		}
	}
	return nullptr;
}