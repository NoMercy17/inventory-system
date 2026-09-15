#include <Item.hpp>

Item::Item(std::string name, Rarity rarity, double weight, int price)
	: name_(std::move(name)), rarity_(rarity), weight_(weight), price_(price) {
}