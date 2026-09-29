#include <iostream>
#include "Character.hpp"
#include "Armor.hpp"
#include "Weapon.hpp"
#include <cstring>

Character::~Character()
{
    delete[] m_title_;
}

Character::Character(const Character& rhs)
    : m_name_(rhs.m_name_),
      m_title_(nullptr),
      m_speed_(rhs.m_speed_),
      m_health_(rhs.m_health_),
      m_baseAttack_(rhs.m_baseAttack_),
      m_baseDefense_(rhs.m_baseDefense_),
      m_equippedWeapons_(rhs.m_equippedWeapons_),
      m_equippedArmor_(rhs.m_equippedArmor_)
{
    if(rhs.m_title_ != nullptr)
    {
        size_t len = std::strlen(rhs.m_title_);
        m_title_ = new char[len + 1];
        std::strcpy(m_title_, rhs.m_title_);
    }
}

Character& Character:: operator=(const Character& rhs)
{   // self-assignment guard
    if(this == &rhs)
        return *this;

    delete[] m_title_;
    m_title_ = nullptr;


    if(rhs.m_title_ != nullptr)
    {
        size_t len = std::strlen(rhs.m_title_);
        m_title_ = new char[len + 1];
        std::strcpy(m_title_, rhs.m_title_);
    }


    m_name_ = rhs.m_name_;
    m_speed_ = rhs.m_speed_;
    m_health_ = rhs.m_health_;
    m_baseAttack_ = rhs.m_baseAttack_;
    m_baseDefense_ = rhs.m_baseDefense_;
    m_equippedWeapons_ = rhs.m_equippedWeapons_;
    m_equippedArmor_ = rhs.m_equippedArmor_;

    return *this;
}


Character::Character(Character&& rhs) noexcept
    : m_name_(std::move(rhs.m_name_)), 
      m_title_(rhs.m_title_),
      m_speed_(rhs.m_speed_),                                                                                                                                                                                 
      m_health_(rhs.m_health_),                                                                                                                                                                               
      m_baseAttack_(rhs.m_baseAttack_),                                                                                                                                                                       
      m_baseDefense_(rhs.m_baseDefense_),                                                                                                                                                                     
      m_equippedWeapons_(rhs.m_equippedWeapons_),                                                                                                                                                             
      m_equippedArmor_(rhs.m_equippedArmor_)
{
    rhs.m_title_ = nullptr;
}

Character& Character::operator=(Character&& rhs) noexcept
{
    if(this == &rhs)
        return *this;

    delete[] m_title_;

    m_name_ = std::move(rhs.m_name_);
    m_title_ = rhs.m_title_;
    m_speed_ = rhs.m_speed_;
    m_health_ = rhs.m_health_;
    m_baseAttack_ = rhs.m_baseAttack_;
    m_baseDefense_ = rhs.m_baseDefense_;
    m_equippedWeapons_ = rhs.m_equippedWeapons_;
    m_equippedArmor_ = rhs.m_equippedArmor_;
    
    rhs.m_title_ = nullptr;
    return *this;
}


void Character::setTitle(const char* title)
{
    delete[] m_title_;
    m_title_ = nullptr;

    if(title != nullptr)
    {
        size_t len = std::strlen(title);
        m_title_ = new char[len + 1];
        std::strcpy(m_title_, title);
    }

}


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
    {
        m_health_ -= effective;
        if (m_health_ < 0.0) m_health_ = 0.0;
    }
}

void Character::buffAttack(double amount) 
{
    m_baseAttack_ += amount; 
    if (m_baseAttack_ < 0.0) m_baseAttack_ = 0.0;
}

void Character::buffDefense(double amount) 
{
    m_baseDefense_ += amount; 
    if (m_baseDefense_ < 0.0) m_baseDefense_ = 0.0;
}

void Character::buffHealth(double amount) 
{ 
    m_health_ += amount; 
    if (m_health_ < 0.0) m_health_ = 0.0;
}

double Character::getDefense() const 
{
	double bonus = 0.0;
	for (const auto* weapon : m_equippedWeapons_)
	{
		if (weapon)
		{
			bonus += getEnchantmentBuff(weapon->getEnchantment()).defenseBonus;
		}
	}
	if (m_equippedArmor_)
	{
		bonus += m_equippedArmor_->getDefense() + 
		         getEnchantmentBuff(m_equippedArmor_->getEnchantment()).defenseBonus; 
	}

	return m_baseDefense_ + bonus;
}

double Character::getAttack() const
{
    double bonus = 0.0;
    for (const auto* weapon : m_equippedWeapons_)
    {
        if (weapon)
        {
            bonus += weapon->getDamage()
                   + getEnchantmentBuff(weapon->getEnchantment()).attackBonus;
        }
    }
    if (m_equippedArmor_)
    {
        bonus += getEnchantmentBuff(m_equippedArmor_->getEnchantment()).attackBonus;
    }
    return m_baseAttack_ + bonus;
}

Weapon* Character::getEquippedWeapon(size_t slot) const
{
    return (slot < MAX_NR_WEAPONS) ? m_equippedWeapons_[slot] : nullptr;
}

const std::array<Weapon*, Character::MAX_NR_WEAPONS>& Character::getEquippedWeapons() const
{
    return m_equippedWeapons_;
}

bool Character::equipWeapon(Weapon* weapon) 
{
    if (!weapon) return false;

    // Do not equip the same weapon twice
    for (const auto* w : m_equippedWeapons_) 
    {
        if (w == weapon) return false;
    }

    if (!m_equippedWeapons_[0]) 
    {
        m_equippedWeapons_[0] = weapon;
    } 
    else if (!m_equippedWeapons_[1]) 
    {
        m_equippedWeapons_[1] = weapon;
    } 
    else 
    {
        m_equippedWeapons_[0] = weapon;
    }
    return true;
}


void Character::unequipWeapon(Weapon* weapon) 
{ 
    if (!weapon) return;

    for (auto*& slot : m_equippedWeapons_) 
    {
        if (slot == weapon) 
        {
            slot = nullptr;
            break;
        }
    }
}

void Character::unequipAllWeapons() 
{
    m_equippedWeapons_.fill(nullptr);
}


bool Character::equipArmor(Armor* armor) 
{ 
    if (!armor) return false;

    if (m_equippedArmor_ != nullptr) 
    {
        std::cout << m_name_ << " already has armor equipped (" << m_equippedArmor_->getName() 
                  << ")! Unequip it before equipping " << armor->getName() << ".\n";
        return false;
    }

    m_equippedArmor_ = armor; 
    return true;
}

void Character::unequipArmor() { m_equippedArmor_ = nullptr; }



void Character::printStats() const
{
    std::cout << m_name_;
    if (m_title_)
    {
        std::cout << " (\"" << m_title_ << "\")";
    }
        std::cout << " — HP: " << m_health_
                  << " | ATK: " << getAttack()
                  << " | DEF: " << getDefense() << std::endl;
}
                
                  