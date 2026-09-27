#pragma once
#include <string>
#include <iostream>

class Character 
{
public:
	explicit Character(std::string name, double speed = 20, double health = 100.0, double attack = 10.0, double defense = 5.0)
		: m_name_(std::move(name)), m_speed_(speed), m_health_(health), m_attack_(attack), m_defense_(defense) {}

	const std::string& getName() const { return m_name_; }
	double getHealth() const { return m_health_; }
	double getAttack() const { return m_attack_; }
	double getDefense() const { return m_defense_; }
	double getSpeed() const { return m_speed_; }


	void heal(double amount);
	void takeDamage(double amount);

	void buffAttack(double amount);
	void buffDefense(double amount);
	void buffHealth(double amount);

	void printStats() const;

private:
	std::string m_name_;
	double m_speed_;
	double m_health_;
	double m_attack_;
	double m_defense_;
};
