#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

#include "Item.hpp"
#include "Weapon.hpp"
#include "Armor.hpp"
#include "Potion.hpp"
#include "Character.hpp"
#include "DataLoader.hpp"

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


int main() 
{
	// Load characters from single-line files via DataLoader Singleton
	Character hero = DataLoader::getInstance().loadCharacter("data/hero.txt");
	Character villain = DataLoader::getInstance().loadCharacter("data/villain.txt");

	// dumb pointer usage
	hero.setTitle("The Good guy");
	villain.setTitle("The Bad Guy");

	
	std::cout << "=== Initial Characters ===" << std::endl;
	hero.printStats();
	villain.printStats();
	std::cout << std::endl;

	std::vector<std::unique_ptr<Item>> hero_items;
	hero_items.push_back(std::make_unique<Weapon>("Iron Sword", Rarity::Common, 5.0, 100, 20.0));
	hero_items.push_back(std::make_unique<Weapon>("Sunpiercer", Rarity::Epic, 3.5, 350, 30.0, Enchantment::Fire));
	hero_items.push_back(std::make_unique<Weapon>("BattleCry Axe", Rarity::Epic, 6.0, 200, 25.0, Enchantment::Lightning));
	hero_items.push_back(std::make_unique<Armor>("Shield of Tinos", Rarity::Uncommon, 7.0, 150, 10.0, Enchantment::Holy));
	hero_items.push_back(std::make_unique<Armor>("Dragon Scale Plate", Rarity::Epic, 12.0, 300, 20.0, Enchantment::Fire));
	hero_items.push_back(std::make_unique<Potion>("Potion of Vitality", Rarity::Rare, 0.5, 50, 25.0, Enchantment::Holy));
	hero_items.push_back(std::make_unique<Potion>("Toxic Concoction", Rarity::Rare, 0.5, 45, 15.0, Enchantment::Poison));

	std::vector<std::unique_ptr<Item>> villain_items;
	villain_items.push_back(std::make_unique<Weapon>("Shadow Dagger", Rarity::Rare, 2.0, 180, 22.0, Enchantment::Shadow));
	villain_items.push_back(std::make_unique<Armor>("Night Cloak", Rarity::Rare, 3.0, 120, 8.0, Enchantment::Shadow));
	villain_items.push_back(std::make_unique<Potion>("Vile Poison Flask", Rarity::Rare, 0.5, 40, 12.0, Enchantment::Poison));


	// Equipping Phase
	std::cout << "=== Equipping Gear ===" << std::endl;
	hero_items[0]->equip(hero); // Slot 1: Iron Sword
	hero_items[1]->equip(hero); // Slot 2: Sunpiercer
	hero_items[3]->equip(hero); // Armor: Shield of Tinos
	std::cout << "---" << std::endl;
	villain_items[0]->equip(villain); // Slot 1: Shadow Dagger
	villain_items[1]->equip(villain); // Armor: Night Cloak
	std::cout << std::endl;

	std::cout << "=== Stats After Equipping ===" << std::endl;
	hero.printStats();
	villain.printStats();
	std::cout << std::endl;

	/* =========================================================================
	 * // [Test 1] Duplicate Weapon Equip Guard (Ignored cleanly):
	 * hero_items[1]->equip(hero);
	 *
	 * // [Test 2] Weapon Replacement (Equipping 3rd weapon replaces Slot 1):
	 * hero_items[2]->equip(hero); // BattleCry Axe replaces Iron Sword
	 *
	 * // [Test 3] Single Unequip & Filling Freed Slot:
	 * hero.unequipWeapon(dynamic_cast<Weapon*>(hero_items[1].get()));
	 * hero_items[0]->equip(hero); // Iron Sword fills freed Slot 2
	 *
	 * // [Test 4] Armor 1-Slot Limit (Rejected until current armor is unequipped):
	 * hero_items[4]->equip(hero); // Dragon Scale Plate rejected!
	 * hero.unequipArmor();
	 * hero_items[4]->equip(hero); // Dragon Scale Plate equipped!
	 *
	 * // [Test 5] Potion Mixing & Alchemical Neutralization:
	 * Potion healA("Healing Elixir", Rarity::Common, 0.5, 25, 15.0, Enchantment::Holy);
	 * Potion healB("Healing Elixir", Rarity::Uncommon, 0.5, 40, 25.0, Enchantment::Poison);
	 * Potion mixed = healA + healB; // Conflicting Holy & Poison neutralize into pure healing
	 * std::cout << mixed << std::endl;
	*/


	std::cout << "=== Combat & Potion Actions ===" << std::endl;

	std::cout << "[Round 1] " << villain.getName() << " attacks!" << std::endl;
	villain_items[0]->use(hero);
	std::cout << std::endl;

	std::cout << "[Round 2] " << hero.getName() << " strikes back!" << std::endl;
	hero_items[1]->use(villain);
	std::cout << std::endl;

	std::cout << "[Round 3] " << villain.getName() << " throws an offensive potion!" << std::endl;
	Item* poisonPotion = villain_items[2].get();
	poisonPotion->use(hero);
	dropItem(villain, villain_items, poisonPotion); // Consumed & discarded from backpack
	std::cout << std::endl;

	// Hero drinks a restorative Holy potion )
	std::cout << "[Round 4] " << hero.getName() << " drinks a restorative potion!" << std::endl;
	Item* healPotion = hero_items[5].get();
	healPotion->equip(hero);
	dropItem(hero, hero_items, healPotion); // Consumed & discarded from backpack
	std::cout << std::endl;

	// Stats
	std::cout << "=== Final Stats After Combat ===" << std::endl;
	hero.printStats();
	villain.printStats();
	std::cout << std::endl;

	return 0;
}
