#include "DataLoader.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace 
{

std::vector<std::string> split(const std::string& line, char delim = ',') 
{
	std::vector<std::string> tokens;
	std::stringstream ss(line);
	std::string token;
	while (std::getline(ss, token, delim)) 
	{
		size_t start = token.find_first_not_of(" \t\r\n");
		size_t end = token.find_last_not_of(" \t\r\n");
		if (start != std::string::npos && end != std::string::npos)
			tokens.push_back(token.substr(start, end - start + 1));
		else
			tokens.push_back("");
	}
	return tokens;
}

std::ifstream openFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open()) 
	{
		// Fallback for running from inside build/ directory
		file.open("../" + filename);
	}
	return file;
}

} // anonymous namespace

Character DataLoader::loadCharacter(const std::string& filename)
{
	std::ifstream file = openFile(filename);
	if (!file.is_open()) 
	{
		std::cerr << "DataLoader: Could not open character file: " << filename << std::endl;
		return Character("Unknown Hero", 20, 100.0, 10.0, 5.0);
	}

	std::string line;
	while (std::getline(file, line)) 
	{
		if (line.empty() || line[0] == '#') continue;

		auto tokens = split(line, ',');
		// Format: Name, speed, health, attack, defense
		if (tokens.size() >= 5) 
		{
			try 
			{
				std::string name = tokens[0];
				double speed = std::stod(tokens[1]);
				double health = std::stod(tokens[2]);
				double attack = std::stod(tokens[3]);
				double defense = std::stod(tokens[4]);
				return Character(name, speed, health, attack, defense);
			}
			catch (const std::exception& e)
			{
				std::cerr << "DataLoader: Malformed character line in " << filename << " (" << e.what() << ")" << std::endl;
			}
		}
	}

	std::cerr << "DataLoader: No valid character data found in: " << filename << std::endl;
	return Character("Default Hero", 20, 100.0, 10.0, 5.0);
}
