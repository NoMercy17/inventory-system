#include <iostream>
#include <vector>
#include <utility>

#include "Item.hpp"
#include "Weapon.hpp"
#include "Armor.hpp"
#include "Potion.hpp"
#include "Character.hpp"

int main() 
{
	Character hero("Aldric", 25, 100.0, 10.0, 5.0);
	std::cout << "=== Initial Stats ===" << std::endl;
	hero.printStats();
	std::cout << std::endl;

	// --- Items ---
	std::vector<Item*> items;

	Item* sword = new Weapon("Iron Sword", Rarity::Common, 5.0, 100, 10.0);
	Item* shield = new Armor("Shield of Tinos", Rarity::Uncommon, 7.0, 150, 5.0, Enchantment::Holy);
	Item* enchantedBow = new Weapon("Sunpiercer", Rarity::Epic, 3.5, 350, 30.0, Enchantment::Fire);

	items.push_back(sword);
	items.push_back(shield);
	items.push_back(enchantedBow);
	items.push_back(new Potion("Potion of Rejuvenation", Rarity::Rare, 0.5, 50, 20.0, Enchantment::Holy));
	items.push_back(new Weapon("BattleCry Axe", Rarity::Epic, 6.0, 200, 15.0, Enchantment::Lightning));

	// --- Print all items ---
	std::cout << "=== Inventory ===" << std::endl;
	for (const Item* item : items) 
	{
		std::cout << *item << std::endl;
	}
	std::cout << std::endl;

	// --- Use items on hero ---
	std::cout << "=== Using Items ===" << std::endl;
	for (Item* item : items)
	{
		item->use(hero);
	}
	std::cout << std::endl;

	std::cout << "=== Stats After Items ===" << std::endl;
	hero.printStats();
	std::cout << std::endl;

	// --- Equality check ---
	Weapon flameblade("Flameblade", Rarity::Rare, 4.0, 250, 20.0, Enchantment::Fire);
	Weapon flameblade2("Flameblade", Rarity::Rare, 4.0, 250, 20.0, Enchantment::Fire);
	Weapon frostblade("Flameblade", Rarity::Rare, 4.0, 250, 20.0, Enchantment::Frost);
	std::cout << "=== Equality ===" << std::endl;
	std::cout << "Same enchantment: " << std::boolalpha << (flameblade == flameblade2) << std::endl;
	std::cout << "Diff enchantment: " << std::boolalpha << (flameblade == frostblade) << std::endl;
	std::cout << std::endl;

	// --- Potion mixing ---
	Potion healA("Healing Elixir", Rarity::Common, 0.5, 25, 15.0, Enchantment::Holy);
	Potion healB("Healing Elixir", Rarity::Uncommon, 0.5, 40, 25.0, Enchantment::Poison);
	Potion mixed = healA + healB;
	std::cout << "=== Potion Mix ===" << std::endl;
	std::cout << mixed << std::endl;
	std::cout << std::endl;

	// --- Cleanup ---
	for (const Item* item : items) 
	{
		delete item;
	}
	items.clear();

	return 0;
}
