#pragma once
#include <string>


// minimal for now
class Character {
public:
	explicit Character(std::string name) : name_(std::move(name)) {}
	const std::string& getName() const { return name_; }

private:
	std::string name_;

};
