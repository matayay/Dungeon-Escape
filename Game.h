// Author: Matayay Karuna

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include "Party.h"
#include "Dungeon.h"
#include "Merchant.h"
#include "Map.h"
#include "Riddles.h"

using namespace std;


class Game: public Party, public Dungeon, public Merchant, public Map, public Riddles
{
    public:
        Game();

        void printStatus();
        bool normalAction();
        bool roomAction();
        bool npcAction();
        bool exitAction();
        bool monsterEncounter( bool room );
        int fightMonster( string monster );
        bool boulderParchmentShears();
        void misfortunes( bool room );
};

#endif