#pragma once
#include <string>
#include <iostream>
#include <array>

class Weapon;
class Armor;

class Character
{
public:
	static constexpr size_t MAX_NR_WEAPONS {2};

	explicit Character(std::string name, double speed = 20, double health = 100.0, double attack = 10.0, double defense = 5.0)
		: m_name_(std::move(name)), m_speed_(speed), m_health_(health), m_baseAttack_(attack), m_baseDefense_(defense) {}

	const std::string& getName() const { return m_name_; }
	double getHealth() const { return m_health_; }
	double getAttack() const;
	double getDefense() const;
	double getSpeed() const { return m_speed_; }
	Weapon* getEquippedWeapon(size_t slot = 0) const;
	const std::array<Weapon*, MAX_NR_WEAPONS>& getEquippedWeapons() const;
	Armor* getEquippedArmor() const { return m_equippedArmor_; }



	void heal(double amount);
	void takeDamage(double amount);

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
	std::string m_name_;
	double m_speed_;
	double m_health_;
	double m_baseAttack_;
	double m_baseDefense_;
	std::array<Weapon*, MAX_NR_WEAPONS> m_equippedWeapons_ {nullptr, nullptr};

	Armor* m_equippedArmor_ = nullptr;
};
