#include "Potion.hpp"
#include "Character.hpp"
#include <sstream>
#include <iostream>

Potion::Potion(std::string name, Rarity rarity, double weight, int price, double healing)
	: Item(std::move(name), rarity, weight, price), m_healing_(healing) 
{}

void Potion::use(Character& target) 
{
	std::cout << "Using potion " << m_name_ << " on " << target.getName() << ", restoring " << m_healing_ << " health." << std::endl;
}

std::string Potion::describe() const 
{
	std::ostringstream oss;
	oss << m_name_ << " (Potion) - healing: " << m_healing_;
	return oss.str();
}

bool Potion::operator==(const Item& other) const
{
	if (!Item::operator==(other))
	{
		return false;
	}

	const auto* otherPotion = dynamic_cast<const Potion*>(&other);
	return otherPotion && m_healing_ == otherPotion->m_healing_;
}

Potion Potion::operator+(const Potion& other) const
{
	std::string combinedName = (m_name_ == other.m_name_) ? "Enhanced " + m_name_ : m_name_ + " & " + other.m_name_;
	Rarity combinedRarity = (m_rarity_ > other.m_rarity_) ? m_rarity_ : other.m_rarity_;
	double combinedWeight = m_weight_ + other.m_weight_;
	int combinedPrice = m_price_ + other.m_price_;
	double combinedHealing = m_healing_ + other.m_healing_;

	return Potion(combinedName, combinedRarity, combinedWeight, combinedPrice, combinedHealing);
}

