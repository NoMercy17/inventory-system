#pragma once
#include "Item.hpp"

class Weapon : public Item 
{
public:
	Weapon(std::string name, Rarity rarity, double weight, int price, double damage, const char* enchantment = nullptr);
	~Weapon() override;
	Weapon(const Weapon& other);
	Weapon& operator=(const Weapon& other);
	Weapon(Weapon&& other) noexcept;
	Weapon& operator=(Weapon&& other) noexcept;

	void use(Character& target) override;
	std::string describe() const override;
	ItemType type() const override { return ItemType::Weapon; }
	bool operator==(const Item& other) const override;

	double getDamage() const { return m_damage_; }
	const char* getEnchantment() const { return m_enchantment_; }
	void setEnchantment(const char* enchantment);

protected:
	double m_damage_;
	char* m_enchantment_;
};

