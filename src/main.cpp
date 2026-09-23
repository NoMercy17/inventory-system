#include <iostream>
#include <vector>
#include <utility>

#include "Item.hpp"
#include "Weapon.hpp"
#include "Armor.hpp"
#include "Potion.hpp"

int main() 
{
	std::vector<Item*> items;

	Item* sword = new Weapon("Iron Sword", Rarity::Common, 5.0, 100, 10.0);
	Item* shield = new Armor("Shield of Tinos", Rarity::Uncommon, 7.0, 150, 5.0);
	Item* enchantedBow = new Weapon("Sunpiercer", Rarity::Epic, 3.5, 350, 30.0, "Solar Flare");

	items.push_back(sword);
	items.push_back(shield);
	items.push_back(enchantedBow);
	items.push_back(new Potion("Potion of Rejuvenation", Rarity::Rare, 0.5, 50, 20.0));
	items.push_back(new Weapon("BattleCry Axe", Rarity::Epic, 6.0, 200, 15.0));

	for (const Item* item : items) 
	{
		std::cout << *item << std::endl;
	}

	Weapon originalSword("Flameblade", Rarity::Rare, 4.0, 250, 20.0, "Flame");
	Weapon copiedSword(originalSword);
	Weapon assignedSword("Old Dagger", Rarity::Common, 1.0, 10, 3.0);
	assignedSword = originalSword;

	Weapon movedSword(std::move(copiedSword));
	Weapon movedAssignedSword("Rusty Blade", Rarity::Common, 2.0, 15, 4.0);
	movedAssignedSword = std::move(assignedSword);

	originalSword.setEnchantment("Frost");
	std::cout << originalSword << std::endl;
	std::cout << movedSword << std::endl;
	std::cout << movedAssignedSword << std::endl;

	std::cout << "Items equal: " << std::boolalpha << (*sword == originalSword) << std::endl;

	Potion healPotionA("Healing Elixir", Rarity::Common, 0.5, 25, 15.0);
	Potion healPotionB("Healing Elixir", Rarity::Uncommon, 0.5, 40, 25.0);
	Potion mixedPotion = healPotionA + healPotionB;
	std::cout << mixedPotion << std::endl;

	for (const Item* item : items) 
	{
		delete item;
	}
	items.clear();

	return 0;
}

