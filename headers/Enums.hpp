#pragma once
#include <string>
#include <cstdint> // uint8_t

// we alter from the default of using the int = 4 bytes to each enum to 1 byte
enum class Rarity: uint8_t { Common, Uncommon, Rare, Epic };

// check that our assertion brings the problem to compile time
//enum class Rarity: uint32_t { Common, Uncommon, Rare, Epic };

enum class ItemType: uint8_t { Weapon, Potion, Armor };

enum class Enchantment: uint8_t { None, Fire, Frost, Lightning, Holy, Shadow, Poison };



// guards
static_assert(sizeof(Rarity) == 1, "Rarity must occupy exactly 1 byte!");
static_assert(sizeof(ItemType) == 1, "ItemType must occupy exactly 1 byte!");
static_assert(sizeof(Enchantment) == 1, "Enchantment must occupy exactly 1 byte!");



struct BuffStats
{
	double attackBonus = 0.0, defenseBonus = 0.0, healthBonus = 0.0;

};



// inline for linker to not have multiple definitions, since in .hpp
inline BuffStats getEnchantmentBuff(Enchantment ench)
{
	switch (ench)
	{
		case Enchantment::Fire:      return {5.0, 0.0, 4.0};
		case Enchantment::Frost:     return {2.0, 5.0, 1.0};
		case Enchantment::Lightning: return {7.0, 3.0, 0.0};
		case Enchantment::Holy:      return {1.0, 5.0, 5.0};
		case Enchantment::Shadow:    return {4.0, 2.0, 2.0};
		case Enchantment::Poison:    return {11.0, 0.0, -3.0};
		default:                     return {0.0, 0.0, 0.0};
	}
}

inline const char* enchantmentToString(Enchantment ench)
{
	switch (ench)
	{
		case Enchantment::Fire:      return "Fire";
		case Enchantment::Frost:     return "Frost";
		case Enchantment::Lightning: return "Lightning";
		case Enchantment::Holy:      return "Holy";
		case Enchantment::Shadow:    return "Shadow";
		case Enchantment::Poison:    return "Poison";
		default:                     return "None";
	}

}