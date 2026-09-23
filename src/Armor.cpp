#include "Armor.hpp"
#include "Character.hpp"
#include <sstream>
#include <iostream>

Armor::Armor(std::string name, Rarity rarity, double weight, int price, double defense)
	: Item(std::move(name), rarity, weight, price), m_defense_(defense) 
{}

void Armor::use(Character& target) 
{
	std::cout << "Using armor " << m_name_ << " on " << target.getName() << ", providing " << m_defense_ << " protection." << std::endl;
}

std::string Armor::describe() const 
{
	std::ostringstream oss;
	oss << m_name_ << " (Armor) - protection: " << m_defense_;
	return oss.str();
}

bool Armor::operator==(const Item& other) const
{
	if (!Item::operator==(other))
	{
		return false;
	}

	const auto* otherArmor = dynamic_cast<const Armor*>(&other);
	return otherArmor && m_defense_ == otherArmor->m_defense_;
}

