#include "Item.hpp"
#include <iostream>

Item::Item(std::string name, Rarity rarity, double weight, int price)
	: m_name_(std::move(name)), m_rarity_(rarity), m_weight_(weight), m_price_(price) 
{}

bool Item::operator==(const Item& other) const
{
	return type() == other.type() &&
		m_name_ == other.m_name_ &&
		m_rarity_ == other.m_rarity_ &&
		m_weight_ == other.m_weight_ &&
		m_price_ == other.m_price_;
}

bool Item::operator!=(const Item& other) const
{
	return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Item& item)
{
	os << item.describe();
	return os;
}

