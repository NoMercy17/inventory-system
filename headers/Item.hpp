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
	virtual std::string describe() const = 0;
	virtual ItemType type() const = 0;

	virtual bool operator==(const Item& other) const;
	bool operator!=(const Item& other) const;

	friend std::ostream& operator<<(std::ostream& os, const Item& item);

	const std::string& getNameRef() const { return m_name_; }
	Rarity getRarity() const { return m_rarity_; }
	double getWeight() const { return m_weight_; }
	int getPrice() const { return m_price_; }

protected:
	std::string m_name_;
	Rarity m_rarity_;
	double m_weight_;
	int m_price_;
};


