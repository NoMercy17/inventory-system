#include "Potion.hpp"
#include "Character.hpp"
#include <sstream>
#include <iostream>

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
	Enchantment combinedEnchantment = (m_enchantment_ != Enchantment::None) ? m_enchantment_ : other.m_enchantment_;

	return Potion(combinedName, combinedRarity, combinedWeight, combinedPrice, combinedHealing, combinedEnchantment);
}

void Potion::use(Character& target) 
{
	BuffStats debuff = getEnchantmentBuff(m_enchantment_);
	double debuff_stats = debuff.attackBonus + debuff.defenseBonus + debuff.healthBonus;
	std::cout << "Using potion " << m_name_ << " on " << target.getName()
			  << ", restoring " << m_healing_ << " health";
	if (m_enchantment_ != Enchantment::None)
	{
		std::cout << " [" << enchantmentToString(m_enchantment_) << " effect]";
	}
	std::cout << std::endl;

	// take them as reverse, we sum and then substract from the target ( we debuff the target with what buffs we would've got)
	if(debuff.attackBonus != 0.0 || debuff.defenseBonus != 0.0 || debuff.healthBonus != 0.0) 
		target.takeDamage(debuff_stats);	
}

void Potion::equip(Character& wielder)
{
	BuffStats buff = getEnchantmentBuff(m_enchantment_);

	std::cout << "Using potion " << m_name_ << " on himself"
			  << ", restoring " << m_healing_ << " health";
	if (m_enchantment_ != Enchantment::None)
	{
		std::cout << " [" << enchantmentToString(m_enchantment_) << " effect]";
	}
	std::cout << std::endl;

	
	wielder.heal(m_healing_);
	if (buff.healthBonus != 0.0) wielder.buffHealth(buff.healthBonus);
	if (buff.attackBonus != 0.0) wielder.buffAttack(buff.attackBonus);
	if (buff.defenseBonus != 0.0) wielder.buffDefense(buff.defenseBonus);
}