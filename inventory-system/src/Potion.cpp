#include "Potion.hpp"
#include "Character.hpp"
#include <sstream>
#include <iostream>

Potion::Potion(std::string name, Rarity rarity, double weight, int price, double healing)
	: Item(std::move(name), rarity, weight, price), healing_(healing) {
}

void Potion::use(Character& target) {
	// For now, we just print a message indicating that the potion is being used
	std::cout << "Using potion " << name_ << " on " << target.getName() << ", restoring " << healing_ << " health." << std::endl;
}

std::string Potion::describe() const {
	std::ostringstream oss;
	oss << name_ << " (Potion) - healing: " << healing_;
	return oss.str();
}
