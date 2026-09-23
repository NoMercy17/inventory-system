#include "Weapon.hpp"
#include "Character.hpp"
#include <sstream>
#include <iostream>
#include <cstring>

static char* allocateAndCopy(const char* str)
{
	if (!str)
	{
		return nullptr;
	}
	std::size_t len = std::strlen(str) + 1;
	char* copy = new char[len];
	std::memcpy(copy, str, len);
	return copy;
}

Weapon::Weapon(std::string name, Rarity rarity, double weight, int price, double damage, const char* enchantment)
	: Item(std::move(name), rarity, weight, price)
	, m_damage_(damage)
	, m_enchantment_(allocateAndCopy(enchantment))
{}

Weapon::~Weapon()
{
	delete[] m_enchantment_;
}

Weapon::Weapon(const Weapon& other)
	: Item(other)
	, m_damage_(other.m_damage_)
	, m_enchantment_(allocateAndCopy(other.m_enchantment_))
{}

Weapon& Weapon::operator=(const Weapon& other)
{
	if (this != &other)
	{
		Item::operator=(other);
		m_damage_ = other.m_damage_;

		char* newEnchantment = allocateAndCopy(other.m_enchantment_);
		delete[] m_enchantment_;
		m_enchantment_ = newEnchantment;
	}
	return *this;
}

Weapon::Weapon(Weapon&& other) noexcept
	: Item(std::move(other))
	, m_damage_(other.m_damage_)
	, m_enchantment_(other.m_enchantment_)
{
	other.m_damage_ = 0.0;
	other.m_enchantment_ = nullptr;
}

Weapon& Weapon::operator=(Weapon&& other) noexcept
{
	if (this != &other)
	{
		Item::operator=(std::move(other));
		delete[] m_enchantment_;

		m_damage_ = other.m_damage_;
		m_enchantment_ = other.m_enchantment_;

		other.m_damage_ = 0.0;
		other.m_enchantment_ = nullptr;
	}
	return *this;
}

void Weapon::use(Character& target)
{
	std::cout << "Using weapon " << m_name_ << " on " << target.getName() << ", dealing " << m_damage_ << " damage." << std::endl;
}

std::string Weapon::describe() const 
{
	std::ostringstream oss;
	oss << m_name_ << " (Weapon) - dmg: " << m_damage_;
	if (m_enchantment_)
	{
		oss << " [Enchanted: " << m_enchantment_ << "]";
	}
	return oss.str();
}

bool Weapon::operator==(const Item& other) const
{
	if (!Item::operator==(other))
	{
		return false;
	}

	const auto* otherWeapon = dynamic_cast<const Weapon*>(&other);
	if (!otherWeapon || m_damage_ != otherWeapon->m_damage_)
	{
		return false;
	}

	if (m_enchantment_ == nullptr && otherWeapon->m_enchantment_ == nullptr)
	{
		return true;
	}

	if (m_enchantment_ == nullptr || otherWeapon->m_enchantment_ == nullptr)
	{
		return false;
	}

	return std::strcmp(m_enchantment_, otherWeapon->m_enchantment_) == 0;
}

void Weapon::setEnchantment(const char* enchantment)
{
	char* newEnchantment = allocateAndCopy(enchantment);
	delete[] m_enchantment_;
	m_enchantment_ = newEnchantment;
}

