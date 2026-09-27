#include "Armor.hpp"
#include "Character.hpp"
#include <sstream>
#include <iostream>

Armor::Armor(std::string name, Rarity rarity, double weight, int price, double defense, Enchantment enchantment)
	: Item(std::move(name), rarity, weight, price), m_defense_(defense), m_enchantment_(enchantment)
{}


std::string Armor::describe() const 
{
	std::ostringstream oss;
	oss << m_name_ << " (Armor) - protection: " << m_defense_;
	if (m_enchantment_ != Enchantment::None)
	{
		oss << " [Enchanted: " << enchantmentToString(m_enchantment_) << "]";
	}
	return oss.str();
}

bool Armor::operator==(const Item& other) const
{
	if (!Item::operator==(other))
	{
		return false;
	}

	const auto* otherArmor = dynamic_cast<const Armor*>(&other);
	return otherArmor
		&& m_defense_ == otherArmor->m_defense_
		&& m_enchantment_ == otherArmor->m_enchantment_;
}


// atm no clear offensive use for armor
void Armor::use(Character& /*target*/) 
{}

void Armor::equip(Character& wielder)
{
    BuffStats buff = getEnchantmentBuff(m_enchantment_);
    double totalDefense = m_defense_ + buff.defenseBonus;

    std::cout << "Equipping armor " << m_name_ << " on himself"
        << ", providing " << totalDefense << " protection";
    if (m_enchantment_ != Enchantment::None)
    {
        std::cout << " [" << enchantmentToString(m_enchantment_) << " enchantment]";
    }
    std::cout << std::endl;

    wielder.equipArmor(this);               
    if (buff.healthBonus != 0.0)
    {
        wielder.buffHealth(buff.healthBonus);
    }
}
