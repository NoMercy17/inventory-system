#include "Weapon.hpp"
#include "Character.hpp"
#include <sstream>
#include <iostream>

Weapon::Weapon(std::string name, Rarity rarity, double weight, int price, double damage)
	: Item(std::move(name), rarity, weight, price), m_damage_(damage) 
{}

void Weapon::use(Character& target)
{
	// For now, we just print a message indicating that the weapon is being used
	std::cout << "Using weapon " << m_name_ << " on " << target.getName() << ", dealing " << m_damage_ << " damage." << std::endl;
}

std::string Weapon::describe() const 
{
	std::ostringstream oss;
	oss << m_name_ << " (Weapon) - dmg: " << m_damage_;
	return oss.str();
}
