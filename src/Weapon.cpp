#include "Weapon.hpp"
#include "Character.hpp"
#include <sstream>
#include <iostream>

Weapon::Weapon(std::string name, Rarity rarity, double weight, int price, const double damage, const Enchantment enchantment)
	: Item(std::move(name), rarity, weight, price)
	, m_damage_(damage)
	, m_enchantment_(enchantment)
{}


std::string Weapon::describe() const 
{
	std::ostringstream oss;
	oss << m_name_ << " (Weapon) - dmg: " << m_damage_;
	if (m_enchantment_ != Enchantment::None)
	{
		oss << " [Enchanted: " << enchantmentToString(m_enchantment_) << "]";
	}
	return oss.str();
}

bool Weapon::operator==(const Item& other) const
{
	if (!Item::operator==(other))
	{
		return false;
	}

	const auto* otherWeapon = dynamic_cast<const Weapon*>(&other);
	return otherWeapon
		&& m_damage_ == otherWeapon->m_damage_
		&& m_enchantment_ == otherWeapon->m_enchantment_;
}

void Weapon::use(Character& target)
{
	BuffStats buff = getEnchantmentBuff(m_enchantment_);
	double totalDamage = m_damage_ + buff.attackBonus;

	std::cout << "Using weapon " << m_name_ << " on " << target.getName()
			  << ", dealing " << totalDamage << " damage";

	if (m_enchantment_ != Enchantment::None)
	{
		std::cout << " [" << enchantmentToString(m_enchantment_) << " enchantment]";
	}
	std::cout << std::endl;

	target.takeDamage(totalDamage);
}


void Weapon::equip(Character& wielder)
{
	if (!wielder.equipWeapon(this))
	{
		return;
	}

	std::cout << wielder.getName() << " equips " << m_name_;                                                                                                               
	if (m_enchantment_ != Enchantment::None)                                                                                                                               
	{                                                                                                                                                                      
		std::cout << " [" << enchantmentToString(m_enchantment_) << "]";                                                                                                   
	}                                                                                                                                                                      
	std::cout << std::endl; 
}