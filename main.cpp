// Author: Matayay Karuna

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include "Game.h"

using namespace std;


int main()
{
    Game dungeon_escape = Game();

    string leader = dungeon_escape.getMembers()[0].getName();
    string line;
    int num_defeated;
    int count_turns = 0;
    int explored_spaces = 0;
    string treasure_types[5] = { "Silver ring", "Ruby necklace", "Emerald bracelet", "Diamond circlet", "Gem-encrusted goblet" };

    cout << "\n" << "Between the 5 of you, you have 100 gold pieces." << endl <<
        "You will need to spend the some of your money on the following items:" << "\n" << endl <<
        "- INGREDIENTS. To make food, you have to cook raw ingredients." << endl <<
        "- COOKWARE. If you want to cook, you have to have cookware first." << endl <<
        "- WEAPONS. You'll want at least one weapon per party member to fend off monsters." << endl <<
        "- ARMOR. Armor increases the chances of surviving a monster attack." << "\n" << endl <<
        "You can spend all of your money here before you start" << endl << 
        "your journey, or you can save some to spend on merchants along the way." << endl << 
        "But beware, some of the merchants in this dungeon are shady characters, and they won't always give you a fair price..." << endl;

    dungeon_escape.menu();
    dungeon_escape.generateMap();

    bool end_game;

    do 
    {
        count_turns++;

        for ( int i = 0; i < dungeon_escape.getNumMembers(); i++ )
        {
            if ( dungeon_escape.getMembers()[i].getHealth() == 0 )
            {
                cout << "Warning: " << dungeon_escape.getMembers()[i].getName() << " is on the brink of starvation!" << endl <<
                    "You should could and eat some food!" << endl;
            }
        }

        if ( dungeon_escape.getAnger() == 100 )
        {
            cout << "The sorcerer has lost his patience and destroyed the entire dungeon! You lose!" << endl;
            break;
        }

        if ( dungeon_escape.isPlayerAlive() == false )
        {
            cout << "You died! Your party will be trapped within the dungeon forever!" << endl;
            break;
        }

        if ( dungeon_escape.getNumMembers() < 2 )
        {
            cout << "The party is no longer large enough to escape the dungeon! You lose!" << endl;
            break;
        }

        if ( !(dungeon_escape.isExplored(dungeon_escape.getPlayerRow(), dungeon_escape.getPlayerCol())) )
        {
            if ( dungeon_escape.isSorcererAlive() )
            {
                dungeon_escape.setAnger(dungeon_escape.getAnger() + 1);
            }
        }

        dungeon_escape.printStatus();

        if ( dungeon_escape.isFreeSpace(dungeon_escape.getPlayerRow(), dungeon_escape.getPlayerCol()) )
        {
            end_game = dungeon_escape.normalAction();
        }

        else if ( dungeon_escape.isRoomLocation(dungeon_escape.getPlayerRow(), dungeon_escape.getPlayerCol()) )
        {
            end_game = dungeon_escape.roomAction();
        }

        else if ( dungeon_escape.isNPCLocation(dungeon_escape.getPlayerRow(), dungeon_escape.getPlayerCol()) )
        {
            end_game = dungeon_escape.npcAction();
        }

        else if ( dungeon_escape.isDungeonExit(dungeon_escape.getPlayerRow(), dungeon_escape.getPlayerCol()) )
        {
            end_game = dungeon_escape.exitAction();

            if ( end_game )
            {
                cout << "You escaped the dungeon!!!" << endl;
            }
        }

        if ( end_game == false )
        {
            for ( int i = 0; i < dungeon_escape.getNumMembers(); i++ )
            {
                if ( dungeon_escape.getMembers()[i].getHealth() == 0 )
                {
                    cout << "OH NO! " << dungeon_escape.getMembers()[i].getName() << " has died!" << endl;
                    dungeon_escape.killMember(i);
                    dungeon_escape.setMaxWeapons(dungeon_escape.getNumMembers());
                    dungeon_escape.setMaxArmor(dungeon_escape.getNumMembers());

                    if ( dungeon_escape.getTotalWeapons() > 0 )
                    {
                        for ( int i = 0; i < 5; i++ )
                        {
                            if ( dungeon_escape.getWeapons(i) > 0 )
                            {
                                dungeon_escape.setWeapon(dungeon_escape.getWeapons(i) - 1, i);
                                break;
                            }
                        }
                    }

                    if ( dungeon_escape.getArmor() > 0 )
                    {
                        dungeon_escape.setArmor(dungeon_escape.getArmor() - 1);
                    }

                    cout << "Your party size has reduced to " << dungeon_escape.getNumMembers() << " members.";
                }
            }
        }
    }
    while ( end_game == false );

    cout << "\n" << "Thanks for playing!" << endl;

    num_defeated = (21 - dungeon_escape.getMonsters().size());

    for ( int i = 0; i < 12; i++ )
    {
        for ( int j = 0; j < 12; j++ )
        {
            if ( dungeon_escape.isExplored(i, j) )
            {
                explored_spaces++;
            }
        }
    }

    ofstream fout;

    fout.open("results.txt", ios::out | ios::trunc);

    if ( fout.fail() )
    {
        cout << "Failed to log game data" << endl;
    }

    else
    {
        fout << "\n" << "Final Game Stats:" << endl <<
            "Party Leader: " << leader << endl <<
            "Remaining Members: " << endl;

        if ( dungeon_escape.getNumMembers() > 1 )
        {
            for ( int i = 1; i < dungeon_escape.getNumMembers(); i++ )
            {
                fout << dungeon_escape.getMembers()[i].getName() << endl;
            }
        }

        else
        {
            fout << "None" << endl;
        }

        fout << "\n" << "Number of rooms cleared: " << dungeon_escape.getCleared() << endl;
        fout << "Gold pieces remaining: " << dungeon_escape.getGold() << endl;
        fout << "Treasure items:" << endl;

        if ( dungeon_escape.getTotalTreasures() > 0 )
        {
            for ( int i = 0; i < 5; i++ )
            {
                if ( dungeon_escape.getTreasures(i) > 0 )
                {
                    fout << treasure_types[i] << ": " << dungeon_escape.getTreasures(i) << endl;
                }
            }
        }

        else
        {
            fout << "None" << endl;
        }

        fout << "\n" << "Number of spaces explored: " << explored_spaces << endl;
        fout << "Number of monsters defeated: " << num_defeated << endl;
        fout << "Number of turns elapsed: " << count_turns << endl;
    }

    fout.close();

    ifstream fin;

    fin.open("results.txt");

    while ( getline(fin, line) )
    {
        cout << line << endl;
    }

    fin.close();

    return 0;
}