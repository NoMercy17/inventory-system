#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <thread>
#include <span>

#include "Helpers.hpp"
#include "Item.hpp"
#include "Weapon.hpp"
#include "Armor.hpp"
#include "Potion.hpp"
#include "Character.hpp"
#include "DataLoader.hpp"
#include "Timer.hpp"

int main() 
{	
	using namespace std::chrono_literals;

	std::cout << "\n=== Real-time Combat Simulation ===" << std::endl;
	GameClock gameClock;

	{
		SystemTimer combatTimer{"TOTAL COMBAT DURATION (WALL TIME)"};

		// Warmup ticks
		for (int turn = 1; turn <= 3; ++turn) {
			std::this_thread::sleep_for(100ms);
			gameClock.tick();
			std::cout << "Turn " << turn 
			          << " | Delta: " << gameClock.getDeltaTime() << "s"
			          << " | Total Game Time: " << gameClock.getTotalTime() << "s\n";
		}
	}

	Character hero{"", 0, 0, 0, 0};
	Character villain{"", 0, 0, 0, 0};

	{
		SystemTimer timer{"DISK ACCESS & STRING PARSING"};
		hero = DataLoader::getInstance().loadCharacter("data/hero.txt");
		villain = DataLoader::getInstance().loadCharacter("data/villain.txt");
	}
	
	hero.setTitle("The Good Guy");
	villain.setTitle("The Bad Guy");

	std::vector<std::unique_ptr<Item>> hero_items;
	std::vector<std::unique_ptr<Item>> villain_items;

	{
		SystemTimer timer{"RUNTIME COST OF DYNAMIC ALLOCATION"};
		hero_items.push_back(std::make_unique<Weapon>("Iron Sword", Rarity::Common, 5.0, 100, 20.0));
		hero_items.push_back(std::make_unique<Weapon>("Sunpiercer", Rarity::Epic, 3.5, 350, 30.0, Enchantment::Fire));
		hero_items.push_back(std::make_unique<Weapon>("BattleCry Axe", Rarity::Epic, 6.0, 200, 25.0, Enchantment::Lightning));
		hero_items.push_back(std::make_unique<Armor>("Shield of Tinos", Rarity::Uncommon, 7.0, 150, 10.0, Enchantment::Holy));
		hero_items.push_back(std::make_unique<Armor>("Dragon Scale Plate", Rarity::Epic, 12.0, 300, 20.0, Enchantment::Fire));
		hero_items.push_back(std::make_unique<Potion>("Potion of Vitality", Rarity::Rare, 0.5, 50, 25.0, Enchantment::Holy));
		hero_items.push_back(std::make_unique<Potion>("Toxic Concoction", Rarity::Rare, 0.5, 45, 15.0, Enchantment::Poison));

		villain_items.push_back(std::make_unique<Weapon>("Shadow Dagger", Rarity::Rare, 2.0, 180, 22.0, Enchantment::Shadow));
		villain_items.push_back(std::make_unique<Armor>("Night Cloak", Rarity::Rare, 3.0, 120, 8.0, Enchantment::Shadow));
		villain_items.push_back(std::make_unique<Potion>("Vile Poison Flask", Rarity::Rare, 0.5, 40, 12.0, Enchantment::Poison));
	}

	{
		SystemTimer timer{"TEMPLATE AND DYNAMIC_CAST LOOKUP MEASUREMENT"};
		if (auto* sword = findItem<Weapon>(hero_items, "Iron Sword"))
			sword->equip(hero);
		if (auto* sword = findItem<Weapon>(hero_items, "Sunpiercer"))
			sword->equip(hero);
		if (auto* armor = findItem<Armor>(hero_items, "Shield of Tinos"))
			armor->equip(hero);

		if (auto* sword = findItem<Weapon>(villain_items, "Shadow Dagger"))
			sword->equip(villain);
		if (auto* armor = findItem<Armor>(villain_items))
			armor->equip(villain);
	}

	std::cout << "\n=== Characters Before Combat ===" << std::endl;
	std::cout << hero << "\n";
	for (const auto* weapon : hero.getEquippedWeapons()) {
		if (weapon) std::cout << "  - " << *weapon << "\n";
	}
	std::cout << villain << "\n";
	for (const auto* weapon : villain.getEquippedWeapons()) {
		if (weapon) std::cout << "  - " << *weapon << "\n";
	}
	std::cout << std::endl;

	std::cout << "=== Direct Combat & Potion Actions ===" << std::endl;

	std::cout << "[Round 1] " << villain.getName() << " attacks with Shadow Dagger!" << std::endl;
	if (auto* weapon = findItem<Weapon>(villain_items, "Shadow Dagger"))
		weapon->use(hero);
	std::cout << std::endl;

	std::cout << "[Round 2] " << hero.getName() << " strikes back with Sunpiercer!" << std::endl;
	if (auto* weapon = findItem<Weapon>(hero_items, "Sunpiercer"))
		weapon->use(villain);
	std::cout << std::endl;

	std::cout << "[Round 3] " << villain.getName() << " throws an offensive poison potion!" << std::endl;
	if (auto* potion = findItem<Potion>(villain_items)) {
		potion->use(hero);
		dropItem(villain, villain_items, potion);
	}
	std::cout << std::endl;

	std::cout << "[Round 4] " << hero.getName() << " drinks a restorative holy potion!" << std::endl;
	if (auto* healPotion = findItem<Potion>(hero_items, "Potion of Vitality")) {
		healPotion->equip(hero);
		dropItem(hero, hero_items, healPotion);
	}
	std::cout << std::endl;

	std::cout << "=== Real-Time Over-Time Effects Simulation (GameClock) ===" << std::endl;
	GameClock battleClock;
	while (hero.hasActiveEffects() || villain.hasActiveEffects()) {
		std::this_thread::sleep_for(500ms);
		battleClock.tick();
		double dt = battleClock.getDeltaTime();

		std::cout << "\n[Tick | dt: " << dt << "s | Total: " << battleClock.getTotalTime() << "s]\n";
		hero.update(dt);
		villain.update(dt);
		std::cout << "  Status: " << hero << "\n";
	}
	std::cout << std::endl;

	std::cout << "=== Characters After Combat ===" << std::endl;
	std::cout << hero << "\n";
	std::cout << villain << "\n";
	std::cout << std::endl;

	/*
	// [Test 1] Duplicate Weapon Equip Guard:
	// hero_items[1]->equip(hero);

	// [Test 2] Weapon Replacement (Equipping 3rd weapon replaces Slot 1):
	// hero_items[2]->equip(hero);

	// [Test 3] Single Unequip & Filling Freed Slot:
	// hero.unequipWeapon(dynamic_cast<Weapon*>(hero_items[1].get()));
	// hero_items[0]->equip(hero);

	// [Test 4] Armor 1-Slot Limit (Rejected until current armor is unequipped):
	// hero_items[4]->equip(hero);
	// hero.unequipArmor();
	// hero_items[4]->equip(hero);

	// [Test 5] Potion Mixing & Alchemical Neutralization:
	// Potion healA("Healing Elixir", Rarity::Common, 0.5, 25, 15.0, Enchantment::Holy);
	// Potion healB("Healing Elixir", Rarity::Uncommon, 0.5, 40, 25.0, Enchantment::Poison);
	// Potion mixed = healA + healB;
	// std::cout << mixed << std::endl;

	// [Test 6] Compile-Time Type Safety Guard:
	// findItem<Character>(hero_items);
	*/

	return 0;
}
