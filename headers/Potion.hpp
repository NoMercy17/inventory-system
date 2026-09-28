#pragma once
#include "Item.hpp"

class Potion : public Item 
{
public:
	Potion(std::string name, Rarity rarity, double weight, int price, double healing, Enchantment enchantment = Enchantment::None);

	void use(Character& target) override;
	void equip(Character& wielder) override;
	std::string describe() const override;
	ItemType type() const override { return ItemType::Potion; }
	bool isConsumable() const override { return true; }
	bool operator==(const Item& other) const override;

	Potion operator+(const Potion& other) const;

	double getHealingAmount() const { return m_healing_; }
	Enchantment getEnchantment() const { return m_enchantment_; }

protected:
	double m_healing_;
	Enchantment m_enchantment_;
};
