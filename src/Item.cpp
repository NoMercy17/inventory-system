#include "Item.hpp"

Item::Item(std::string name, Rarity rarity, double weight, int price)
	: m_name_(std::move(name)), m_rarity_(rarity), m_weight_(weight), m_price_(price) 
{}
