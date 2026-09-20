#include <iostream>
#include <vector>

#include "Item.hpp"
#include "Weapon.hpp"
#include "Armor.hpp"
#include "Potion.hpp"

int main() {
	std::vector<Item*> items;

	Item* sword = new Weapon("Iron Sword", Rarity::Common, 5.0, 100, 10.0);
	Item* shield = new Armor("Shield of Tinos", Rarity::Uncommon, 7.0, 150, 5.0);

	items.push_back(sword);
	items.push_back(shield);
	items.push_back(new Potion("Potion of Rejuvenation", Rarity::Rare, 0.5, 50, 20.0));
	items.push_back(new Weapon("BattleCry Axe", Rarity::Epic, 6.0, 200, 15.0));

	for (const Item* item : items) {
		std::cout << item->describe() << std::endl;
	}

	// free the memory since raw pointers
	
	for(const Item* item : items) {
		delete item;
	}

	// defensive measure to avoid dangling pointer from the vector
	items.clear();

	return 0;
}
