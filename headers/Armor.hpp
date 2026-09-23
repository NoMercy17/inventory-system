#pragma once
#include "Item.hpp"

class Armor : public Item {
public:
	Armor(std::string name, Rarity rarity, double weight, int price, double defense);

	void use(Character& target) override; // we equip and reduce dmg from the target
    std::string describe() const override;
	ItemType type() const override { return ItemType::Armor; }

	double getDefense() const { return defense_; }

protected:
	double defense_;
};
