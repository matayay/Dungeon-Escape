// Author: Matayay Karuna

#include <iostream>
#include "Inventory.h"

using namespace std;


Inventory::Inventory()
{
    gold = 100;
    ingrediants = 0;
    armor = 0;
    max_weapons = 5;
    max_armor = 5;

    for ( int i = 0; i < 3; i++ )
    {
        cookware[i] = 0;
    }

    for ( int i = 0; i < 5; i++ )
    {
        weapons[i] = 0;
        treasures[i] = 0;
    }
}


int Inventory::getGold()
{
    return gold;
}


int Inventory::getIngrediants()
{
    return ingrediants;
}


int Inventory::getCookware(int index)
{
    return cookware[index];
}


int Inventory::getTotalCookware()
{
    int total_cookware = 0;

    for ( int i = 0; i < 3; i++ )
    {
        total_cookware += cookware[i];
    }

    return total_cookware;
}


int Inventory::getWeapons(int index)
{
    return weapons[index];
}


int Inventory::getTotalWeapons()
{
    int total_weapons = 0;

    for ( int i = 0; i < 5; i++ )
    {
        total_weapons += weapons[i];
    }

    return total_weapons;
}


int Inventory::getArmor()
{
    return armor;
}


int Inventory::getTreasures(int index)
{
    return treasures[index];
}


int Inventory::getTotalTreasures()
{
    int total_treasures = 0;

    for ( int i = 0; i < 5; i++ )
    {
        total_treasures += treasures[i];
    }

    return total_treasures;
}


int Inventory::getMaxWeapons()
{
    return max_weapons;
}


int Inventory::getMaxArmor()
{
    return max_armor;
}


int Inventory::getUniqueWeapons()
{
    int unique_weapons = 0;

    for ( int i = 0; i < 5; i++ )
    {
        if ( getWeapons(i) > 0 )
        {
            unique_weapons += 1;
        }
    }

    return unique_weapons;
}


void Inventory::setGold(int num_gold)
{
    gold = num_gold;
}


void Inventory::setIngrediants(int num_ingrediants)
{
    ingrediants = num_ingrediants;
}


void Inventory::setCookware(int num_ware, int index)
{
    cookware[index] = num_ware;
}


void Inventory::setWeapon(int num_weapon, int index)
{
    weapons[index] = num_weapon;
}


void Inventory::setArmor(int num_armor)
{
    armor = num_armor;
}


void Inventory::setTreasure(int num_treasure, int index)
{
    treasures[index] = num_treasure;
}


void Inventory::setMaxWeapons(int max)
{
    max_weapons = max;
}


void Inventory::setMaxArmor(int max)
{
    max_armor = max;
}


void Inventory::printInventory()
{
    cout << "+-------------+" << endl <<
        "| INVENTORY   |" << endl <<
        "+-------------+" << endl <<
        "| Gold        | " << getGold() << endl <<
        "| Ingredients | " << getIngrediants() << " kg" << endl <<
        "| Cookware    | P: " << getCookware(0) << " | F: " << getCookware(1) << " | C: " << getCookware(2) << endl <<
        "| Weapons     | C: " << getWeapons(0) << " | S: " << getWeapons(1) << " | R: " << getWeapons(2) << " | B: " << getWeapons(3) << " | L: " << getWeapons(4) << endl <<
        "| Armor       | " << getArmor() << endl <<
        "| Treasures   | R: " << getTreasures(0) << " | N: " << getTreasures(1) << " | B: " << getTreasures(2) << " | C: " << getTreasures(3) << " | G: " << getTreasures(4) << endl;
}