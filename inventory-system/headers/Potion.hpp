#pragma once
#include "Item.hpp"

class Potion : public Item {
public:
	Potion(std::string name, Rarity rarity, double weight, int price, double healing);

	void use(Character& target) override; // we heal the target
	std::string describe() const override;
	ItemType type() override { return ItemType::Potion; }

	double getHealingAmount() const { return healing_; }

protected:
	double healing_;
};
