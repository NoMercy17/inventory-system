#pragma once
#include "Item.hpp"

class Armor : public Item 
{
public:
	Armor(std::string name, Rarity rarity, double weight, int price, double defense, Enchantment enchantment = Enchantment::None);

	void use(Character& target) override;
	std::string describe() const override;
	ItemType type() const override { return ItemType::Armor; }
	bool operator==(const Item& other) const override;

	double getDefense() const { return m_defense_; }
	Enchantment getEnchantment() const { return m_enchantment_; }

protected:
	double m_defense_;
	Enchantment m_enchantment_;
};
