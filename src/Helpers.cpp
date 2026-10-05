#include <Helpers.hpp>
#include <Character.hpp>
#include <Weapon.hpp>
#include <Armor.hpp>
#include <algorithm>



// Drops an item from inventory; if equipped, automatically unequips it first
void dropItem(Character& character, std::vector<std::unique_ptr<Item>>& inventory, Item* itemToRemove)
{
	if (auto* weapon = dynamic_cast<Weapon*>(itemToRemove))
	{
		character.unequipWeapon(weapon);
	}
	if (auto* armor = dynamic_cast<Armor*>(itemToRemove))
	{
		if (character.getEquippedArmor() == armor)
			character.unequipArmor();
	}

	inventory.erase(
		std::remove_if(inventory.begin(), inventory.end(),
			[itemToRemove](const std::unique_ptr<Item>& ptr) { return ptr.get() == itemToRemove; }),
		inventory.end());
}