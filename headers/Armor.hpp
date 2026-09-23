#pragma once
#include "Item.hpp"

class Armor : public Item 
{

public:
	Armor(std::string name, Rarity rarity, double weight, int price, double defense);

	void use(Character& target) override;
	std::string describe() const override;
	ItemType type() const override { return ItemType::Armor; }
	bool operator==(const Item& other) const override;

	double getDefense() const { return m_defense_; }

protected:
	double m_defense_;
};
