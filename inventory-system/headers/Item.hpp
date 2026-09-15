#ifndef ITEM_HPP
#define ITEM_HPP
#include "Enums.hpp"

class Character; // Forward declaration

class Item {
public:
	Item(std::string name, Rarity rarity, double weight, int price);
	virtual ~Item() = default; // Virtual destructor for proper cleanup of derived classes
	virtual void use(Character& target) = 0;
	virtual std::string describe() = 0;
	virtual ItemType type() = 0;

	const std::string &getNameRef() const { return name_; };
	Rarity getRarity() const { return rarity_; };
	double getWeight() const { return weight_; };
	int getPrice() const { return price_; };
		
protected:
	std::string name_;
	Rarity rarity_;
	double weight_;
	int price_;
};


#endif 
