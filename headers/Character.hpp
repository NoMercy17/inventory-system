#pragma once
#include <string>


// minimal for now
class Character 
{
public:
	explicit Character(std::string name) : m_name_(std::move(name)) {}
	const std::string& getName() const { return m_name_; }

private:
	std::string m_name_;

};
