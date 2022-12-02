// Author: Matayay Karuna

#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <string>

using namespace std;


class Inventory
{
    public:
        Inventory();

        // Setters.
        int getGold();
        int getIngrediants();
        int getCookware(int index);
        int getTotalCookware();
        int getWeapons(int index);
        int getTotalWeapons();
        int getArmor();
        int getTreasures(int index);
        int getTotalTreasures();
        int getMaxWeapons();
        int getMaxArmor();
        int getUniqueWeapons();

        // Getters.
        void setGold(int num_gold);
        void setIngrediants(int num_ingrediants);
        void setCookware(int num_ware, int index);
        void setWeapon(int num_weapon, int index);
        void setArmor(int num_armor);
        void setTreasure(int num_treasure, int index);
        void setMaxWeapons(int max);
        void setMaxArmor(int max);

        // Print Inventory.
        void printInventory();

    private:
        int gold;
        int ingrediants;
        int cookware[3];
        int weapons[5];
        int armor;
        int treasures[5];
        int max_armor;
        int max_weapons;
};

#endif