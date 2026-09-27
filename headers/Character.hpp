#pragma once
#include <string>
#include <iostream>

class Weapon;
class Armor;

class Character
{
public:
	explicit Character(std::string name, double speed = 20, double health = 100.0, double attack = 10.0, double defense = 5.0)
		: m_name_(std::move(name)), m_speed_(speed), m_health_(health), m_baseAttack_(attack), m_baseDefense_(defense) {}

	const std::string& getName() const { return m_name_; }
	double getHealth() const { return m_health_; }
	double getAttack() const;
	double getDefense() const;
	double getSpeed() const { return m_speed_; }
	Weapon* getEquippedWeapon() const { return m_equippedWeapon_; }
	Armor* getEquippedArmor() const { return m_equippedArmor_; }


	void heal(double amount);
	void takeDamage(double amount);

	void buffAttack(double amount); // permanently raises the Base stat
	void buffDefense(double amount); // permanently raises the Base stat
	void buffHealth(double amount);


	void equipArmor(Armor* armor);
	void equipWeapon(Weapon* weapon);
	void unequipArmor();
	void unequipWeapon();


	void printStats() const;

private:
	std::string m_name_;
	double m_speed_;
	double m_health_;
	double m_baseAttack_;
	double m_baseDefense_;

	Weapon* m_equippedWeapon_ = nullptr; // the inventory owns the object
	Armor* m_equippedArmor_ = nullptr;
};
