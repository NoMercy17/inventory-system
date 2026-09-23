#include "Armor.hpp"
#include "Character.hpp"
#include <sstream>
#include <iostream>

Armor::Armor(std::string name, Rarity rarity, double weight, int price, double defense)
	: Item(std::move(name), rarity, weight, price), m_defense_(defense) 
{}

void Armor::use(Character& target) 
{
	// For now, we just print a message indicating that the armor is being used
	std::cout << "Using armor " << m_name_ << " on " << target.getName() << ", providing " << m_defense_ << " protection." << std::endl;
}

std::string Armor::describe() const 
{
	std::ostringstream oss;
	oss << m_name_ << " (Armor) - protection: " << m_defense_;
	return oss.str();
}
