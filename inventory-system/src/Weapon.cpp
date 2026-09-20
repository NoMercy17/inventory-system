#include "Weapon.hpp"
#include "Character.hpp"
#include <sstream>
#include <iostream>

Weapon::Weapon(std::string name, Rarity rarity, double weight, int price, double damage)
	: Item(std::move(name), rarity, weight, price), damage_(damage) {
}

void Weapon::use(Character& target) {
	// For now, we just print a message indicating that the weapon is being used
	std::cout << "Using weapon " << name_ << " on " << target.getName() << ", dealing " << damage_ << " damage." << std::endl;
}

std::string Weapon::describe() const {
	std::ostringstream oss;
	oss << name_ << " (Weapon) - dmg: " << damage_;
	return oss.str();
}
