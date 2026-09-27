#pragma once
#include "Item.hpp"

class Weapon : public Item 
{
public:
	Weapon(std::string name, Rarity rarity, double weight, int price, double damage = 0.0, Enchantment enchantment = Enchantment::None);

	void use(Character& target) override;
	void equip(Character& wielder) override;
	std::string describe() const override;
	ItemType type() const override { return ItemType::Weapon; }
	bool operator==(const Item& other) const override;

	double getDamage() const { return m_damage_; }
	Enchantment getEnchantment() const { return m_enchantment_; }

protected:
	double m_damage_;
	Enchantment m_enchantment_;
};
