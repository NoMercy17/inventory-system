#include <iostream>
#include "Character.hpp"

void Character::heal(double amount) 
{ 
    m_health_ += amount; 
}

void Character::takeDamage(double amount)
{
	double effective = amount - m_defense_;
	if (effective > 0) m_health_ -= effective;
}

void Character::buffAttack(double amount) 
{
    m_attack_ += amount; 
}
void Character::buffDefense(double amount) 
{
    m_defense_ += amount; 
}

void Character::buffHealth(double amount) 
{ 
    m_health_ += amount; 
}

void Character::printStats() const
{
	std::cout << m_name_ << " — HP: " << m_health_
			<< " | ATK: " << m_attack_
			<< " | DEF: " << m_defense_ << std::endl;
}