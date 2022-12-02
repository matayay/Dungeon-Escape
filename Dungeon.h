// Author: Matayay Karuna

#ifndef DUNGEON_H
#define DUNGEON_H

#include <iostream>

using namespace std;


class Dungeon
{
    public:
        Dungeon();

        int getAnger();
        int getKeys();
        int getCleared();

        void setAnger(int anger_level);
        void setKeys(int num_keys);
        void setCleared(int num_cleared);

        void printDungeon()
        {
            cout << "+-------------+" << endl <<
                "| Rooms Cleared: " << rooms_cleared << " | Keys: " << keys << " | Anger Level: " << anger << endl;
        }

    private:
        int anger;
        int keys;
        int rooms_cleared;
};

#endif