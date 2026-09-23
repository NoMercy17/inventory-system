#pragma once
#include "Item.hpp"

class Potion : public Item 
{
public:
	Potion(std::string name, Rarity rarity, double weight, int price, double healing);

	void use(Character& target) override; // we heal the target
    std::string describe() const override;
	ItemType type() const override { return ItemType::Potion; }

	double getHealingAmount() const { return m_healing_; }

protected:
	double m_healing_;
};
