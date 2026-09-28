#include "Potion.hpp"
#include "Character.hpp"
#include <sstream>
#include <iostream>
#include <cmath>

Potion::Potion(std::string name, Rarity rarity, double weight, int price, double healing, Enchantment enchantment)
	: Item(std::move(name), rarity, weight, price)
	, m_healing_(healing)
	, m_enchantment_(enchantment)
{}

std::string Potion::describe() const 
{
	std::ostringstream oss;
	oss << m_name_ << " (Potion) - healing: " << m_healing_;
	if (m_enchantment_ != Enchantment::None)
	{
		oss << " [" << enchantmentToString(m_enchantment_) << "]";
	}
	return oss.str();
}

bool Potion::operator==(const Item& other) const
{
	if (!Item::operator==(other))
	{
		return false;
	}

	const auto* otherPotion = dynamic_cast<const Potion*>(&other);
	return otherPotion
		&& m_healing_ == otherPotion->m_healing_
		&& m_enchantment_ == otherPotion->m_enchantment_;
}

Potion Potion::operator+(const Potion& other) const
{
	std::string combinedName = (m_name_ == other.m_name_) ? "Enhanced " + m_name_ : m_name_ + " & " + other.m_name_;
	Rarity combinedRarity = (m_rarity_ > other.m_rarity_) ? m_rarity_ : other.m_rarity_;
	double combinedWeight = m_weight_ + other.m_weight_;
	int combinedPrice = m_price_ + other.m_price_;
	double combinedHealing = m_healing_ + other.m_healing_;

	// Enchantment sum Logic
	Enchantment combinedEnchantment = Enchantment::None;
	if (m_enchantment_ == other.m_enchantment_)
	{
		combinedEnchantment = m_enchantment_;
	}
	else if (m_enchantment_ == Enchantment::None)
	{
		combinedEnchantment = other.m_enchantment_;
	}
	else if (other.m_enchantment_ == Enchantment::None)
	{
		combinedEnchantment = m_enchantment_;
	}
	else
	{
		// Opposing volatile enchantments neutralize each other
		combinedEnchantment = Enchantment::None;
	}

	return Potion(combinedName, combinedRarity, combinedWeight, combinedPrice, combinedHealing, combinedEnchantment);
}

void Potion::use(Character& target) 
{
	BuffStats debuff = getEnchantmentBuff(m_enchantment_);
	std::cout << "Using potion " << m_name_ << " offensively on " << target.getName()
			  << ", inflicting " << m_healing_ << " damage";
	if (m_enchantment_ != Enchantment::None)
	{
		std::cout << " [" << enchantmentToString(m_enchantment_) << " debuff effect]";
	}
	std::cout << std::endl;

	target.takeDamage(m_healing_);
	if (debuff.healthBonus != 0.0) target.buffHealth(-std::abs(debuff.healthBonus));
	if (debuff.attackBonus != 0.0) target.buffAttack(-std::abs(debuff.attackBonus));
	if (debuff.defenseBonus != 0.0) target.buffDefense(-std::abs(debuff.defenseBonus));
}

void Potion::equip(Character& wielder)
{
	BuffStats buff = getEnchantmentBuff(m_enchantment_);

	std::cout << wielder.getName() << " drinks potion " << m_name_
			  << ", restoring " << m_healing_ << " health";
	if (m_enchantment_ != Enchantment::None)
	{
		std::cout << " [" << enchantmentToString(m_enchantment_) << " buff effect]";
	}
	std::cout << std::endl;

	wielder.heal(m_healing_);
	if (buff.healthBonus != 0.0) wielder.buffHealth(buff.healthBonus);
	if (buff.attackBonus != 0.0) wielder.buffAttack(buff.attackBonus);
	if (buff.defenseBonus != 0.0) wielder.buffDefense(buff.defenseBonus);
}