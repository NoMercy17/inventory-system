#include "Potion.hpp"
#include "Character.hpp"
#include <sstream>
#include <iostream>

Potion::Potion(std::string name, Rarity rarity, double weight, int price, double healing)
	: Item(std::move(name), rarity, weight, price), m_healing_(healing) 
{}

void Potion::use(Character& target) 
{
	// For now, we just print a message indicating that the potion is being used
	std::cout << "Using potion " << m_name_ << " on " << target.getName() << ", restoring " << m_healing_ << " health." << std::endl;
}

std::string Potion::describe() const 
{
	std::ostringstream oss;
	oss << m_name_ << " (Potion) - healing: " << m_healing_;
	return oss.str();
}
