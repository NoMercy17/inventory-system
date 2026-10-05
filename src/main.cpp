#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

#include "Helpers.hpp"
#include "Item.hpp"
#include "Weapon.hpp"
#include "Armor.hpp"
#include "Potion.hpp"
#include "Character.hpp"
#include "DataLoader.hpp"


int main() 
{
	// Load characters from single-line files via DataLoader Singleton
	Character hero = DataLoader::getInstance().loadCharacter("data/hero.txt");
	Character villain = DataLoader::getInstance().loadCharacter("data/villain.txt");

	// dumb pointer usage
	hero.setTitle("The Good Guy");
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



	// Problem if we reorder or we access an invalid index!
	// std::cout << "=== Equipping Gear ===" << std::endl;
	// hero_items[0]->equip(hero); // Slot 1: Iron Sword
	// hero_items[1]->equip(hero); // Slot 2: Sunpiercer
	// hero_items[3]->equip(hero); // Armor: Shield of Tinos

	// Equipping Phase Improved
	if(auto* sword = findItem<Weapon>(hero_items, "Iron Sword"))
		sword->equip(hero);
	if(auto* sword = findItem<Weapon>(hero_items, "Sunpiercer"))
		sword->equip(hero);
	if(auto* armor = findItem<Armor>(hero_items, "Shield of Tinos"))
		armor->equip(hero);


	// std::cout << "---" << std::endl;
	// villain_items[0]->equip(villain); // Slot 1: Shadow Dagger
	// villain_items[1]->equip(villain); // Armor: Night Cloak
	// std::cout << std::endl;


	if(auto* sword = findItem<Weapon>(villain_items, "Shadow Dagger"))
		sword->equip(villain);
	if(auto* armor = findItem<Armor>(villain_items))
		armor->equip(villain);


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
	if (auto* weapon = findItem<Weapon>(villain_items, "Shadow Dagger"))
        weapon->use(hero);	
	std::cout << std::endl;

	std::cout << "[Round 2] " << hero.getName() << " strikes back!" << std::endl;
	if (auto* weapon = findItem<Weapon>(hero_items, "Iron Sword"))
        weapon->use(villain);	
	std::cout << std::endl;


	// refactored handling potions from the inventories using the template helper function
	// villain uses poison on hero
	std::cout << "[Round 3] " << villain.getName() << " throws an offensive potion!" << std::endl;
	if (auto* potion = findItem<Potion>(villain_items))                                                                                                                                      
    {                                                                                                                                                                                                               
        potion->use(hero);                                                                                                                                                                                    
        dropItem(villain, villain_items, potion);                                                                                                                                                                     
    } 
	std::cout << std::endl;

	// Hero drinks a restorative Holy potion )
	std::cout << "[Round 4] " << hero.getName() << " drinks a restorative potion!" << std::endl;
	if (auto* healPotion = findItem<Potion>(hero_items, "Potion of Vitality"))                                                                                                                                      
    {                                                                                                                                                                                                               
        healPotion->equip(hero);                                                                                                                                                                                    
        dropItem(hero, hero_items, healPotion); // consumed & discarded from backpack                                                                                                                                                                      
    } 
	std::cout << std::endl;



	// Stats
	std::cout << "=== Final Stats After Combat ===" << std::endl;
	hero.printStats();
	villain.printStats();
	std::cout << std::endl;

	return 0;
}
