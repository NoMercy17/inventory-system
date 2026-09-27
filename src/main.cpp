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

	// --- Poison potion verification ---
    std::cout << "=== Poison Potion Test ===" << std::endl;
    Character tester("Test Dummy", 20, 50.0, 10.0, 5.0);
    tester.printStats();

    Potion poison("Potion of Corruption", Rarity::Rare, 0.5, 80, 10.0, Enchantment::Poison);
    poison.equip(tester);
    tester.printStats();
    std::cout << std::endl;


	Character hero("Heroic Knight", 20, 100.0, 10.0, 5.0);
	std::cout << "=== Initial Stats ===" << std::endl;
	hero.printStats();
	std::cout << std::endl;

	// Heroic Knight's items
	std::vector<Item*> hero_items;

	Item* sword = new Weapon("Iron Sword", Rarity::Common, 5.0, 100, 100.0);
	Item* shield = new Armor("Shield of Tinos", Rarity::Uncommon, 7.0, 150, 5.0, Enchantment::Holy);
	Item* enchantedBow = new Weapon("Sunpiercer", Rarity::Epic, 3.5, 350, 30.0, Enchantment::Fire);

	hero_items.push_back(sword);
	hero_items.push_back(shield);
	hero_items.push_back(enchantedBow);
	hero_items.push_back(new Potion("Potion of Rejuvenation", Rarity::Rare, 0.5, 50, 20.0, Enchantment::Holy));
	hero_items.push_back(new Weapon("BattleCry Axe", Rarity::Epic, 6.0, 200, 15.0, Enchantment::Lightning));

	// --- Print all items ---
	std::cout << "=== Inventory ===" << std::endl;
	for (const Item* item : hero_items) 
	{
		std::cout << *item << std::endl;
	}
	std::cout << std::endl;

	// --- Use items on hero ---
	std::cout << "=== Using Items on himself ===" << std::endl;
	for (Item* item : hero_items)
	{
		item->equip(hero);
	}
	std::cout << std::endl;

	std::cout << "=== Stats After Items ===" << std::endl;
    hero.printStats();
    std::cout << "Currently equipped weapon: " << hero.getEquippedWeapon()->describe() << std::endl;
    std::cout << "Currently equipped armor: "  << hero.getEquippedArmor()->describe()  << std::endl;
    std::cout << std::endl;

    // --- Prove the swap doesn't stack ---
    std::cout << "=== Swapping back to Iron Sword ===" << std::endl;
    sword->equip(hero);
    std::cout << std::endl;

    std::cout << "=== Stats After Swap ===" << std::endl;
    hero.printStats();
    std::cout << "Currently equipped weapon: " << hero.getEquippedWeapon()->describe() << std::endl;
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
	for (const Item* item : hero_items) 
	{
		delete item;
	}
	hero_items.clear();

	return 0;
}
