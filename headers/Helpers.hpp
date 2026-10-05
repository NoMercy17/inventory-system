#pragma once
#include <vector>
#include <memory>
#include <string>


class Character;
class Item;

void dropItem(Character& character, std::vector<std::unique_ptr<Item>>& inventory, Item* itemToRemove);


template<typename TargetItem>
TargetItem* findItem(const std::vector<std::unique_ptr<Item>>& inventory, const std::string& name = "")
{
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