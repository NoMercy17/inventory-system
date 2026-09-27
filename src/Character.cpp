#include <iostream>
#include "Character.hpp"
#include "Armor.hpp"
#include "Weapon.hpp"

void Character::heal(double amount) 
{ 
    m_health_ += amount; 
}

void Character::takeDamage(double amount)
{
    // uses getDefense() (base + currently equipped gear) instead of a raw member,
    // so damage taken reflects whatever armor/weapon is actually worn right now
    double effective = amount - getDefense();
    if (effective > 0) 
        m_health_ -= effective;
}

void Character::buffAttack(double amount) 
{
    m_baseAttack_ += amount; 
}
void Character::buffDefense(double amount) 
{
    m_baseDefense_ += amount; 
}

void Character::buffHealth(double amount) 
{ 
    m_health_ += amount; 
}

double Character::getDefense() const 
{
	double bonus = 0.0;
	if(m_equippedWeapon_)
	{
		bonus += getEnchantmentBuff(m_equippedWeapon_->getEnchantment()).defenseBonus;
	}
	if(m_equippedArmor_)
	{
		bonus += m_equippedArmor_ -> getDefense() + 
		getEnchantmentBuff(m_equippedArmor_-> getEnchantment()).defenseBonus; 
	}

	return m_baseDefense_ + bonus;
}

double Character::getAttack() const
{
    double bonus = 0.0;
    if (m_equippedWeapon_)
    {
        bonus += m_equippedWeapon_->getDamage()
               + getEnchantmentBuff(m_equippedWeapon_->getEnchantment()).attackBonus;
    }
    if (m_equippedArmor_)
    {
        bonus += getEnchantmentBuff(m_equippedArmor_->getEnchantment()).attackBonus;
    }
    return m_baseAttack_ + bonus;
}



void Character::equipWeapon(Weapon* weapon) { m_equippedWeapon_ = weapon; }
void Character::equipArmor(Armor* armor) { m_equippedArmor_ = armor; }
void Character::unequipWeapon() { m_equippedWeapon_ = nullptr; }
void Character::unequipArmor() { m_equippedArmor_ = nullptr; }



void Character::printStats() const
{
    std::cout << m_name_ << " — HP: " << m_health_
        << " | ATK: " << getAttack()
        << " | DEF: " << getDefense() << std::endl;
}