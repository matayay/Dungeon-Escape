// Author: Matayay Karuna

#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Monster
{
    public:
        Monster();

        vector<string> getMonsters();
        vector<string> getTier1();
        vector<string> getTier2();
        vector<string> getTier3();
        vector<string> getTier4();
        vector<string> getTier5();
        string getSorcerer();

        bool isSorcererAlive();
        string getMonsterName( string monster );
        int getMonsterHealth( string monster );

        void killMonster(string monster, int tier);

        int split( string input_string, char separator, string arr[], int arr_size );

    private:
        vector<string> monsters;
        vector<string> tier1;
        vector<string> tier2;
        vector<string> tier3;
        vector<string> tier4;
        vector<string> tier5;
        string sorcerer;
};

#endif