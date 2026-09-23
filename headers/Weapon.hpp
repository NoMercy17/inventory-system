#pragma once
#include "Item.hpp"

class Weapon : public Item 
{
public:
	Weapon(std::string name, Rarity rarity, double weight, int price, double damage);

	void use(Character& target) override; // we equip and deal dmg to the target
    std::string describe() const override;
	ItemType type() const override { return ItemType::Weapon; }

	double getDamage() const { return m_damage_; }

protected:
	double m_damage_;
};
