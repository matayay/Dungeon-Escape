// Author: Matayay Karuna

#include <iostream>
#include "Dungeon.h"

using namespace std;


Dungeon::Dungeon()
{
    anger = 0;
    keys = 0;
    rooms_cleared = 0;
}


int Dungeon::getAnger()
{
    return anger;
}


int Dungeon::getKeys()
{
    return keys;
}


int Dungeon::getCleared()
{
    return rooms_cleared;
}


void Dungeon::setAnger(int anger_level)
{
    anger = anger_level;
}


void Dungeon::setKeys(int num_keys)
{
    keys = num_keys;
}


void Dungeon::setCleared(int num_cleared)
{
    rooms_cleared = num_cleared;
}