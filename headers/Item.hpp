#pragma once
#include "Enums.hpp"
#include <string>
#include <iosfwd>

class Character;

class Item 
{
public:
	Item(std::string name, Rarity rarity, double weight, int price);
	virtual ~Item() = default;
	virtual void use(Character& target) = 0;
	virtual void equip(Character& wielder) = 0;
	virtual std::string describe() const = 0;
	virtual ItemType type() const = 0;
	virtual bool isConsumable() const { return false; }

	virtual bool operator==(const Item& other) const;
	bool operator!=(const Item& other) const;

	friend std::ostream& operator<<(std::ostream& os, const Item& item);

	// we can modify from std::string& to string_view since we just print/compare the names, we do not rly work with them
	std::string_view getName() const noexcept { return m_name_; }
	// [Unused speculative getters]
	// Rarity getRarity() const { return m_rarity_; }
	// double getWeight() const { return m_weight_; }
	// int getPrice() const { return m_price_; }

protected:
	// Memory efficient order
	std::string m_name_; // 32 bytes
	double m_weight_; // 8 bytes
	int m_price_; // 4 bytes 
	Rarity m_rarity_; // 1 byte, +3 padding

};

std::ostream& operator<<(std::ostream& os, const Item& item);


