#pragma once
#include "Enums.hpp"
#include <string>

class Character; // Forward declaration

class Item 
{
public:
	Item(std::string name, Rarity rarity, double weight, int price);
	virtual ~Item() = default; // Virtual destructor for proper cleanup of derived classes
	virtual void use(Character& target) = 0;
	virtual std::string describe() const = 0;
	virtual ItemType type() const = 0;

	const std::string &getNameRef() const { return m_name_; }
	Rarity getRarity() const { return m_rarity_; }
	double getWeight() const { return m_weight_; }
	int getPrice() const { return m_price_; }

protected:
	std::string m_name_;
	Rarity m_rarity_;
	double m_weight_;
	int m_price_;
};

