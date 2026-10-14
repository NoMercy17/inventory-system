#pragma once
#include <string>
#include <iostream>
#include <array>
#include <vector>
#include "Enums.hpp"

class Weapon;
class Armor;

class Character
{
public:
	static constexpr size_t MAX_NR_WEAPONS {2};

	friend std::ostream& operator<<(std::ostream& os, const Character& character);


	// Rule of 5 because of the m_title_ pointer
	explicit Character(std::string name, double speed = 20, double health = 100.0, double attack = 10.0, double defense = 5.0)
		: m_name_(std::move(name)), m_speed_(speed), m_health_(health), m_baseAttack_(attack), m_baseDefense_(defense) {}
	
	~Character();
	Character(const Character& rhs);
	Character& operator=(const Character& rhs);
	Character(Character&& rhs) noexcept;
	Character& operator=(Character&& rhs) noexcept;

	// [Unused speculative getters]
	// const char* getTitle() const { return m_title_; }
	void setTitle(const char* title);

	// we can modify from std::string& to string_view since we just print/compare the names, we do not rly work with them
	std::string_view getName() const noexcept { return m_name_; }
	// [Unused speculative getters]
	// double getHealth() const { return m_health_; }
	double getAttack() const;
	double getDefense() const;
	// double getSpeed() const { return m_speed_; }
	// Weapon* getEquippedWeapon(size_t slot = 0) const;

	const std::array<Weapon*, MAX_NR_WEAPONS>& getEquippedWeapons() const;
	Armor* getEquippedArmor() const { return m_equippedArmor_; }

	void heal(double amount);
	void takeDamage(double amount);

	// Over-Time Effect Management
	void applyEffect(const StatusEffect& effect);
	void update(double dt);
	bool hasActiveEffects() const noexcept { return !m_activeEffects_.empty(); }

	void buffAttack(double amount); // permanently raises the Base stat
	void buffDefense(double amount); // permanently raises the Base stat
	void buffHealth(double amount); // permanently raises the Base stat

	bool equipArmor(Armor* armor);
	bool equipWeapon(Weapon* weapon);
	void unequipArmor();
	void unequipWeapon(Weapon* weapon);
	void unequipAllWeapons();

	void printStats() const;
	
private:
	// 0 padding preserved
	std::string m_name_; // 32 bytes
	char* m_title_ = nullptr; // 8 bytes

	double m_speed_; // 8 bytes
	double m_health_; // 8 bytes
	double m_baseAttack_; // 8 bytes
	double m_baseDefense_; // 8 bytes

	std::array<Weapon*, MAX_NR_WEAPONS> m_equippedWeapons_ {nullptr, nullptr}; // 16 bytes, 2 * 8 bytes
	Armor* m_equippedArmor_ = nullptr; // 8 bytes
	std::vector<StatusEffect> m_activeEffects_; // 24 bytes (3 * 8 bytes pointers)
};

std::ostream& operator<<(std::ostream& os, const Character& character);
