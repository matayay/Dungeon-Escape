// Author: Matayay Karuna

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <time.h>
#include "Game.h"

using namespace std;


Game::Game()
{

}


/**
 * Algorithm: prints the current game status.
 * 1. Print dungeon stats.
 * 2. Print inventory.
 * 3. Print party stats.
 * 4. Print map.
 * Parameters: none.
 * Returns: void.
*/
void Game::printStatus()
{
    cout << "\n" << "+-------------+" << endl <<
        "| STATUS      |" << endl;
    printDungeon();
    printInventory();
    printParty();
    displayMap();
}


/**
 * Algorithm: Prompts the user for input on what they would like to do if on a normal space.
 * 1. Declare varibles int choice, char move_party, int cookware, and int amount.
 * 3. Prompt user for options and validate the input.
 * 4. Case 1, give them the option to move on the map.
 * 5. Case 2, allow them to explore a space. Investigating has the chance of giving
 *      the party a key, treasure, and spawn a monster.
 * 6. Case 3, spawn a monster for the party to fight. If there are no available monsters to fight print so.
 * 7. Case 4, allow the party to cook food and recover health.
 * 8. Case 5, end the game.
 * Parameters: none.
 * Returns: false.
*/
bool Game::normalAction()
{
    int choice;
    char move_party;
    int cookware;
    int amount;

    srand(time(0));

    do 
    {
        cout << "Select one:" << endl <<
        "1. Move" << endl <<
        "2. Investigate" << endl <<
        "3. Pick a Fight" << endl <<
        "4. Cook and Eat" << endl <<
        "5. Give up" << endl;
        cin >> choice;

        if ( choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 )
        {
            cout << "Invalid input, please try again." << "\n" << endl;
        }
    }
    while ( choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 );

    switch (choice)
    {
        case 1:
            do 
            {
                cout << "Which direction? (W A S D), C to cancel: " << endl;
                cin >> move_party;

                move_party = tolower(move_party);

                if ( move_party != 'w' && move_party != 'a' && move_party != 's' && move_party != 'd' && move_party != 'c' )
                {
                    cout << "Invalid input, please try again." << endl;
                    continue;
                }

                else if ( move_party == 'c' )
                {
                    if ( !(isExplored(getPlayerRow(), getPlayerCol())) )
                    {
                        setAnger(getAnger() - 1);
                    }
                    break;
                }

                move(move_party);

                for ( int i = 0; i < getNumMembers(); i++ )
                {
                    if ( randomNumbers(1, 5) ==  3 )
                    {
                        damage(getMembers()[i].getName(), 1);
                    }
                }
            }
            while ( move_party != 'w' && move_party != 'a' && move_party != 's' && move_party != 'd' && move_party != 'c' );
            break;

        case 2:
            if ( isExplored(getPlayerRow(), getPlayerCol()) )
            {
                cout << "You have already explored this space." << endl;
            }

            else
            {
                exploreSpace(getPlayerRow(), getPlayerCol());

                if ( randomNumbers(1, 10) == 3 )
                {
                    cout << "You found a key!" << endl;
                    setKeys(getKeys() + 1);
                }

                if ( randomNumbers(1, 5) == 3 )
                {
                    cout << "You found treasure!" << endl;

                    if ( getCleared() < 5 )
                    {
                        setTreasure(getTreasures(getCleared()) + 1, getCleared());
                    }

                    else
                    {
                        setTreasure(getTreasures(4) + 1, 4);
                    }
                }

                if ( randomNumbers(1, 5) == 3 )
                {
                    monsterEncounter(false);
                }

                else
                {
                    for ( int i = 0; i < getNumMembers(); i++ )
                    {
                        if ( randomNumbers(1, 2) ==  1 )
                        {
                            damage(getMembers()[i].getName(), 1);
                        }
                    }
                }

                if ( randomNumbers(1, 2) == 2 )
                {
                    misfortunes(false);
                }
            }
            break;

        case 3:
            monsterEncounter(false);
            
            if ( randomNumbers(1, 2) == 2 )
            {
                misfortunes(false);
            }
            break;

        case 4:
            if ( getTotalCookware() == 0 )
            {
                cout << "You need cookware to make food." << endl;
            }

            else if ( getIngrediants() == 0 )
            {
                cout << "You need ingrediants to make food." << endl;
            }

            else
            {
                do 
                {
                    cout << "\n" << "Choose one of the following:" << endl <<
                        "1. (25%) Ceramic Pot " << getCookware(0) << endl <<
                        "2. (10%) Frying Pan " << getCookware(1) << endl <<
                        "3. ( 2%) Cauldron " << getCookware(2) << endl <<
                        "4. Cancel" << endl;
                    cin >> cookware;

                    if ( cookware == 4 )
                    {
                        break;
                    }

                    else if ( getCookware(cookware - 1) == 0 )
                    {
                        cout << "You do not have any of this cookware. Choose a different option" << endl;
                        continue;
                    }

                    if ( cookware != 1 && cookware != 2 && cookware != 3 && cookware != 4 )
                    {
                        cout << "Invalid input, please try again." << endl;
                    }
                }
                while ( cookware != 1 && cookware != 2 && cookware != 3 && cookware != 4 || getCookware(cookware - 1) == 0 );

                if ( cookware != 4 )
                {
                    do 
                    {
                        cout << "How many ingrediants would you like to use? Enter a multiple of 5: " << endl;
                        cin >> amount;

                        if ( amount < 0 || amount % 5 != 0 )
                        {
                            cout << "Invalid input, please try again." << endl;
                        }

                        else if ( amount > getIngrediants() )
                        {
                            cout << "You are trying to use ingrediants which you do not have" << endl;
                            continue;
                        }
                    }
                    while ( amount < 0 || amount % 5 != 0 );

                    if ( cookware == 1 )
                    {
                        if ( randomNumbers(1, 4) == 1 )
                        {
                            cout << "Your pot broke" << endl;
                            setCookware(getCookware(0) - 1, 0);
                        }

                        else
                        {
                            eat(amount);
                            setIngrediants(getIngrediants() - amount);
                        }
                    }

                    else if ( cookware == 2 )
                    {
                        if ( randomNumbers(1, 10) == 1 )
                        {
                            cout << "Your pot broke" << endl;
                            setCookware(getCookware(1) - 1, 1);
                        }

                        else
                        {
                            eat(amount);
                            setIngrediants(getIngrediants() - amount);
                        }
                    }

                    else if ( cookware == 3 )
                    {
                        if ( randomNumbers(1, 50) == 1 )
                        {
                            cout << "Your pot broke" << endl;
                            setCookware(getCookware(2) - 1, 2);
                        }

                        else
                        {
                            eat(amount);
                            setIngrediants(getIngrediants() - amount);
                        }
                    }

                    if ( randomNumbers(1, 2) == 2 )
                    {
                        misfortunes(false);
                    }
                }

                else if ( cookware == 4 && !(isExplored(getPlayerRow(), getPlayerCol())) )
                {
                    setAnger(getAnger() - 1);
                }
            }
            break;

        case 5:
            return true;
            break;
        
        default:
            break;
    }

    return false;
}


/**
 * Algorithm: Prompts the user for input on what they would like to do if on a room space.
 * 1. Declare variables int choice, char move_party, bool outcome, and bool door.
 * 2. Prompt the user on options and validate the input.
 * 3. Case 1, give them the option to move on the map.
 * 4. Case 2, open the door to the room. If the party does not have a key then a rock, paper, scissors
 *      game must be won to enter. If lost then a party member will die. Upon entering the room the party
 *      will fight a monster.
 * 5. Case 3, end the game.
 * Parameters: none.
 * Returns: false.
*/
bool Game::roomAction()
{
    int choice;
    char move_party;
    bool outcome;
    bool door;

    do 
    {
        cout << "Select one:" << endl <<
        "1. Move" << endl <<
        "2. Open the Door" << endl <<
        "3. Give up" << endl;
        cin >> choice;

        if ( choice != 1 && choice != 2 && choice != 3 )
        {
            cout << "Invalid input, please try again." << "\n" << endl;
        }
    }
    while ( choice != 1 && choice != 2 && choice != 3 );

    switch (choice)
    {
        case 1:
            do 
            {
                cout << "Which direction? (W A S D), C to cancel: " << endl;
                cin >> move_party;

                move_party = tolower(move_party);

                if ( move_party != 'w' && move_party != 'a' && move_party != 's' && move_party != 'd' && move_party != 'c' )
                {
                    cout << "Invalid input, please try again." << endl;
                    continue;
                }

                else if ( move_party == 'c' )
                {
                    if ( !(isExplored(getPlayerRow(), getPlayerCol())) )
                    {
                        setAnger(getAnger() - 1);
                    }
                    break;
                }

                move(move_party);

                for ( int i = 0; i < getNumMembers(); i++ )
                {
                    if ( randomNumbers(1, 5) ==  3 )
                    {
                        damage(getMembers()[i].getName(), 1);
                    }
                }
            }
            while ( move_party != 'w' && move_party != 'a' && move_party != 's' && move_party != 'd' && move_party != 'c' );
            break;

        case 2:
            if ( getKeys() > 0 )
            {
                setKeys(getKeys() - 1);

                if ( randomNumbers(1, 2) == 2 )
                {
                    misfortunes(true);
                }

                outcome = monsterEncounter(true);

                if ( outcome == true )
                {
                    setCleared(getCleared() + 1);
                    removeRoom(getPlayerRow(), getPlayerCol());
                }
            }

            else
            {
                door = boulderParchmentShears();

                if ( door )
                {
                    outcome = monsterEncounter(true);

                    if ( outcome == true )
                    {
                        setCleared(getCleared() + 1);
                        removeRoom(getPlayerRow(), getPlayerCol());
                    }
                }

                else
                {
                    killMember(getNumMembers() - 1);
                    setMaxWeapons(getNumMembers());
                    setMaxArmor(getNumMembers());

                    if ( getTotalWeapons() > 0 )
                    {
                        for ( int i = 0; i < 5; i++ )
                        {
                            if ( getWeapons(i) > 0 )
                            {
                                setWeapon(getWeapons(i) - 1, i);
                                break;
                            }
                        }
                    }

                    if ( getArmor() > 0 )
                    {
                        setArmor(getArmor() - 1);
                    }

                    cout << "Puzzle failed. One member has been killed." << endl;
                }

                if ( randomNumbers(1, 2) == 2 )
                {
                    misfortunes(false);
                }
            }
            break;

        case 3:
            return true;
            break;
        
        default:
            break;
    }

    return false;
}


/**
 * Algorithm: Prompts the user for input on what they would like to do if on an NPC space.
 * 1. Declare variables int choice, char move_party, double new_price, int riddle_index, and string answer.
 * 2. Prompt user for options and validate input.
 * 3. Case 1, give the option to move on the map.
 * 4. Case 2, solve a riddle for the NPC. If successful then the party can buy from them. If not then
 *      the NPC will spawn a monster and disapear.
 * 5. Case 3, end game.
 * Parameters: none.
 * Returns: false.
*/
bool Game::npcAction()
{
    int choice;
    char move_party;
    double new_price;
    int riddle_index;
    string answer;

    srand(time(0));

    do 
    {
        cout << "Select one:" << endl <<
        "1. Move" << endl <<
        "2. Speak to NPC" << endl <<
        "3. Give up" << endl;
        cin >> choice;

        if ( choice != 1 && choice != 2 && choice != 3 )
        {
            cout << "Invalid input, please try again." << "\n" << endl;
        }
    }
    while ( choice != 1 && choice != 2 && choice != 3 );

    switch (choice)
    {
        case 1:
            do 
            {
                cout << "Which direction? (W A S D), C to cancel: " << endl;
                cin >> move_party;

                move_party = tolower(move_party);

                if ( move_party != 'w' && move_party != 'a' && move_party != 's' && move_party != 'd' && move_party != 'c' )
                {
                    cout << "Invalid input, please try again." << endl;
                    continue;
                }

                else if ( move_party == 'c' )
                {
                    break;
                }

                move(move_party);

                for ( int i = 0; i < getNumMembers(); i++ )
                {
                    if ( randomNumbers(1, 5) ==  3 )
                    {
                        damage(getMembers()[i].getName(), 1);
                    }
                }
            }
            while ( move_party != 'w' && move_party != 'a' && move_party != 's' && move_party != 'd' && move_party != 'c' );
            break;

        case 2:
            riddle_index = randomNumbers(0, 19);

            cout << "You must solve my riddle to purchase my wears." << "\n" << endl <<
                getRiddle(riddle_index) << endl;
            cin >> answer;

            if ( answer == getRiddleAnswer(riddle_index) )
            {
                new_price = getCleared();
                new_price *= 0.25;
                setPrice(1 + new_price);
                menu();
            }

            else
            {
                cout << "Wrong answer!" << endl;
                monsterEncounter(false);
            }

            removeNPC(getPlayerRow(), getPlayerCol());

            if ( randomNumbers(1, 2) == 2 )
            {
                misfortunes(false);
            }
            break;

        case 3:
            return true;
            break;
        
        default:
            break;
    }

    return false;
}


/**
 * Algorithm: Allows the player to win the game if the sorcerer has been defeated.
 * 1. Declare variables int choice and char move_party.
 * 2. Prompt the user for options and validate input.
 * 3. Case 1, let the party move somewhare else on the map.
 * 4. Case 2, if the sorcerer is dead then the party wins the game.
 * 5. Case 3, end game.
 * Parameters: none.
 * Returns: false.
*/
bool Game::exitAction()
{
    int choice;
    char move_party;

    srand(time(0));

    do 
    {
        cout << "Select one:" << endl <<
        "1. Move" << endl <<
        "2. Escape Dungeon" << endl <<
        "3. Give up" << endl;
        cin >> choice;

        if ( choice != 1 && choice != 2 && choice != 3 )
        {
            cout << "Invalid input, please try again." << "\n" << endl;
        }
    }
    while ( choice != 1 && choice != 2 && choice != 3 );

    switch (choice)
    {
        case 1:
            do 
            {
                cout << "Which direction? (W A S D), C to cancel: " << endl;
                cin >> move_party;

                move_party = tolower(move_party);

                if ( move_party != 'w' && move_party != 'a' && move_party != 's' && move_party != 'd' && move_party != 'c' )
                {
                    cout << "Invalid input, please try again." << endl;
                    continue;
                }

                else if ( move_party == 'c' )
                {
                    break;
                }

                move(move_party);

                for ( int i = 0; i < getNumMembers(); i++ )
                {
                    if ( randomNumbers(1, 5) ==  3 )
                    {
                        damage(getMembers()[i].getName(), 1);
                    }
                }
            }
            while ( move_party != 'w' && move_party != 'a' && move_party != 's' && move_party != 'd' && move_party != 'c' );
            break;
        
        case 2:
            if ( isSorcererAlive() )
            {
                cout << "You must clear all rooms before you can escape the dungeon." << endl;
            }

            else
            {
                return true;
            }
            break;

        case 3:
            return true;
            break;

        default:
            break;
    }

    return false;
}


/**
 * ALgorithm: spawn a monster for the party to fight.
 * 1. If the battle takes place in a room and there is only one room left then
 *      spawn and fight the sorcerer.
 * 2. Else if the battle is in a room but there is more than one room left spawn a
 *      random monster from the next tier.
 * 3. Else if the battle takes place outside a room and the sorcerer is still alive,
 *      spawn a random monster from the current tier.
 * Parameters: room (bool).
 * Returns: the bool of whether or not the monster was defeated.
*/
bool Game::monsterEncounter( bool room )
{
    int battle_decision;
    int outcome;
    string monster;
    bool monster_defeated = false;

    string tier6 = getMonsters()[getMonsters().size() - 1];
    vector<string> tiers[5];
    tiers[0] = getTier1();
    tiers[1] = getTier2();
    tiers[2] = getTier3();
    tiers[3] = getTier4();
    tiers[4] = getTier5();

    srand(time(0));

    if ( getCleared() == 4 && room == true )
    {
        cout << getMonsterName(tier6) << " Ahead! They Look Hostile!" << endl;

        if ( getTotalWeapons() > 0 )
        {
            do 
            {
                cout << "Choose one:" << endl <<
                "1. Fight" << endl <<
                "2. Surrender" << endl;
                cin >> battle_decision;

                if ( battle_decision != 1 && battle_decision != 2 )
                {
                    cout << "Invalid input" << endl;
                }
            }
            while ( battle_decision != 1 && battle_decision != 2 );
        }

        else
        {
            battle_decision = 2;
        }

        if ( battle_decision == 1 )
        {
            int outcome = fightMonster(tier6);

            if ( outcome > 0 )
            {
                monster_defeated = true;
                killMonster(tier6, getMonsterHealth(tier6));

                setGold(getGold() + (10 * getMonsterHealth(tier6)));
                setIngrediants(getIngrediants() + (5 * getMonsterHealth(tier6)));

                if ( randomNumbers(1, 10) == 3 )
                {
                    setKeys(getKeys() + 1);
                }

                cout << "You defeated the sorcerer!" << endl;
            }

            else
            {
                setGold(getGold() - (0.25 * getGold()));

                if ( getIngrediants() > 30 )
                {
                    setIngrediants(getIngrediants() - 30);
                }

                else
                {
                    setIngrediants(0);
                }

                for ( int i = 1; i < getNumMembers(); i++ )
                {
                    if ( getArmor() == 0 )
                    {
                        if ( randomNumbers(1, 10) == 3 )
                        {
                            cout << getMembers()[i].getName() << " has been killed!" << endl;
                            killMember(i);
                            setMaxWeapons(getNumMembers());
                            setMaxArmor(getNumMembers());

                            if ( getTotalWeapons() > 0 )
                            {
                                for ( int i = 0; i < 5; i++ )
                                {
                                    if ( getWeapons(i) > 0 )
                                    {
                                        setWeapon(getWeapons(i) - 1, i);
                                        break;
                                    }
                                }
                            }

                            if ( getArmor() > 0 )
                            {
                                setArmor(getArmor() - 1);
                            }
                        }
                    }

                    else
                    {
                        if ( randomNumbers(1, 20) == 3 )
                        {
                            cout << getMembers()[i].getName() << " has been killed!" << endl;
                            killMember(i);
                            setMaxWeapons(getNumMembers());
                            setMaxArmor(getNumMembers());

                            if ( getTotalWeapons() > 0 )
                            {
                                for ( int i = 0; i < 5; i++ )
                                {
                                    if ( getWeapons(i) > 0 )
                                    {
                                        setWeapon(getWeapons(i) - 1, i);
                                        break;
                                    }
                                }
                            }

                            if ( getArmor() > 0 )
                            {
                                setArmor(getArmor() - 1);
                            }
                        }
                    }
                }

                cout << "The sorcerer defeated you. Come back later to try again." << endl;
            }
        }

        else if ( battle_decision == 2 )
        {
            killMember(getNumMembers() - 1);
            setMaxWeapons(getNumMembers());
            setMaxArmor(getNumMembers());

            if ( getTotalWeapons() > 0 )
            {
                for ( int i = 0; i < 5; i++ )
                {
                    if ( getWeapons(i) > 0 )
                    {
                        setWeapon(getWeapons(i) - 1, i);
                        break;
                    }
                }
            }

            if ( getArmor() > 0 )
            {
                setArmor(getArmor() - 1);
            }

            cout << "You surrendered to the sorcerer. One party member was left behind." << endl;
        }

        for ( int i = 0; i < getNumMembers(); i++ )
        {
            if ( randomNumbers(1, 2) ==  1 )
            {
                damage(getMembers()[i].getName(), 1);
            }
        }
    }

    else if ( room == true )
    {
        monster = tiers[getCleared() + 1][randomNumbers(0, (tiers[getCleared() + 1].size() - 1))];

        cout << getMonsterName(monster) << " Ahead! They Look Hostile!" << endl;

        if ( getTotalWeapons() > 0 )
        {
            do 
            {
                cout << "Choose one:" << endl <<
                "1. Fight" << endl <<
                "2. Surrender" << endl;
                cin >> battle_decision;

                if ( battle_decision != 1 && battle_decision != 2 )
                {
                    cout << "Invalid input" << endl;
                }
            }
            while ( battle_decision != 1 && battle_decision != 2 );
        }

        else
        {
            battle_decision = 2;
        }

        if ( battle_decision == 1 )
        {
            int outcome = fightMonster(monster);

            if ( outcome > 0 )
            {
                monster_defeated = true;
                killMonster(monster, getMonsterHealth(monster));

                setGold(getGold() + (10 * getMonsterHealth(monster)));
                setIngrediants(getIngrediants() + (5 * getMonsterHealth(monster)));

                if ( randomNumbers(1, 10) == 3 )
                {
                    setKeys(getKeys() + 1);
                }

                cout << "You defeated the monster!" << endl;

                if ( randomNumbers(2, 3) == 2 )
                {
                    misfortunes(false);
                }
            }

            else
            {
                setGold(getGold() - (0.25 * getGold()));

                if ( getIngrediants() > 30 )
                {
                    setIngrediants(getIngrediants() - 30);
                }

                else
                {
                    setIngrediants(0);
                }

                for ( int i = 1; i < getNumMembers(); i++ )
                {
                    if ( getArmor() == 0 )
                    {
                        if ( randomNumbers(1, 10) == 3 )
                        {
                            cout << getMembers()[i].getName() << " has been killed!" << endl;
                            killMember(i);
                            setMaxWeapons(getNumMembers());
                            setMaxArmor(getNumMembers());

                            if ( getTotalWeapons() > 0 )
                            {
                                for ( int i = 0; i < 5; i++ )
                                {
                                    if ( getWeapons(i) > 0 )
                                    {
                                        setWeapon(getWeapons(i) - 1, i);
                                        break;
                                    }
                                }
                            }

                            if ( getArmor() > 0 )
                            {
                                setArmor(getArmor() - 1);
                            }
                        }
                    }

                    else
                    {
                        if ( randomNumbers(1, 20) == 3 )
                        {
                            cout << getMembers()[i].getName() << " has been killed!" << endl;
                            killMember(i);
                            setMaxWeapons(getNumMembers());
                            setMaxArmor(getNumMembers());

                            if ( getTotalWeapons() > 0 )
                            {
                                for ( int i = 0; i < 5; i++ )
                                {
                                    if ( getWeapons(i) > 0 )
                                    {
                                        setWeapon(getWeapons(i) - 1, i);
                                        break;
                                    }
                                }
                            }

                            if ( getArmor() > 0 )
                            {
                                setArmor(getArmor() - 1);
                            }
                        }
                    }
                }

                if ( randomNumbers(1, 2) == 2 )
                {
                    misfortunes(false);
                }

                cout << "The monster defeated you. Come back later to try again." << endl;
            }
        }

        else if ( battle_decision == 2 )
        {
            killMember(getNumMembers() - 1);
            setMaxWeapons(getNumMembers());
            setMaxArmor(getNumMembers());

            if ( getTotalWeapons() > 0 )
            {
                for ( int i = 0; i < 5; i++ )
                {
                    if ( getWeapons(i) > 0 )
                    {
                        setWeapon(getWeapons(i) - 1, i);
                        break;
                    }
                }
            }

            if ( getArmor() > 0 )
            {
                setArmor(getArmor() - 1);
            }

            cout << "You surrendered to the monster. One party member was left behind." << endl;

            if ( randomNumbers(1, 2) == 2 )
            {
                misfortunes(false);
            }
        }

        for ( int i = 0; i < getNumMembers(); i++ )
        {
            if ( randomNumbers(1, 2) ==  1 )
            {
                damage(getMembers()[i].getName(), 1);
            }
        }
    }

    else if ( getCleared() != 5 )
    {
        if ( tiers[getCleared()].size() > 0 )
        {
            monster = tiers[getCleared()][randomNumbers(0, (tiers[getCleared()].size() - 1))];

            cout << getMonsterName(monster) << " Ahead! They Look Hostile!" << endl;

            if ( getTotalWeapons() > 0 )
            {
                do 
                {
                    cout << "Choose one:" << endl <<
                    "1. Fight" << endl <<
                    "2. Surrender" << endl;
                    cin >> battle_decision;

                    if ( battle_decision != 1 && battle_decision != 2 )
                    {
                        cout << "Invalid input" << endl;
                    }
                }
                while ( battle_decision != 1 && battle_decision != 2 );
            }

            else
            {
                battle_decision = 2;
            }

            if ( battle_decision == 1 )
            {
                int outcome = fightMonster(monster);

                if ( outcome > 0 )
                {
                    monster_defeated = true;
                    killMonster(monster, getMonsterHealth(monster));

                    setGold(getGold() + (10 * getMonsterHealth(monster)));
                    setIngrediants(getIngrediants() + (5 * getMonsterHealth(monster)));

                    if ( randomNumbers(1, 10) == 3 )
                    {
                        setKeys(getKeys() + 1);
                    }

                    cout << "You defeated the monster!" << endl;
                }

                else
                {
                    setGold(getGold() - (0.25 * getGold()));

                    if ( getIngrediants() > 30 )
                    {
                        setIngrediants(getIngrediants() - 30);
                    }

                    else
                    {
                        setIngrediants(0);
                    }

                    for ( int i = 1; i < getNumMembers(); i++ )
                    {
                        if ( getArmor() == 0 )
                        {
                            if ( randomNumbers(1, 10) == 3 )
                            {
                                cout << getMembers()[i].getName() << " has been killed!" << endl;
                                killMember(i);
                                setMaxWeapons(getNumMembers());
                                setMaxArmor(getNumMembers());

                                if ( getTotalWeapons() > 0 )
                                {
                                    for ( int i = 0; i < 5; i++ )
                                    {
                                        if ( getWeapons(i) > 0 )
                                        {
                                            setWeapon(getWeapons(i) - 1, i);
                                            break;
                                        }
                                    }
                                }

                                if ( getArmor() > 0 )
                                {
                                    setArmor(getArmor() - 1);
                                }
                            }
                        }

                        else
                        {
                            if ( randomNumbers(1, 20) == 3 )
                            {
                                cout << getMembers()[i].getName() << " has been killed!" << endl;
                                killMember(i);
                                setMaxWeapons(getNumMembers());
                                setMaxArmor(getNumMembers());

                                if ( getTotalWeapons() > 0 )
                                {
                                    for ( int i = 0; i < 5; i++ )
                                    {
                                        if ( getWeapons(i) > 0 )
                                        {
                                            setWeapon(getWeapons(i) - 1, i);
                                            break;
                                        }
                                    }
                                }

                                if ( getArmor() > 0 )
                                {
                                    setArmor(getArmor() - 1);
                                }
                            }
                        }
                    }

                    cout << "You lost the fight with the monster." << endl;
                }
            }

            if ( battle_decision == 2 )
            {
                killMember(getNumMembers() - 1);
                setMaxWeapons(getNumMembers());
                setMaxArmor(getNumMembers());

                if ( getTotalWeapons() > 0 )
                {
                    for ( int i = 0; i < 5; i++ )
                    {
                        if ( getWeapons(i) > 0 )
                        {
                            setWeapon(getWeapons(i) - 1, i);
                            break;
                        }
                    }
                }

                if ( getArmor() > 0 )
                {
                    setArmor(getArmor() - 1);
                }

                cout << "You surrendered to the monster. One party member was left behind." << endl;
            }

            for ( int i = 0; i < getNumMembers(); i++ )
            {
                if ( randomNumbers(1, 2) ==  1 )
                {
                    damage(getMembers()[i].getName(), 1);
                }
            }
        }

        else
        {
            cout << "There are no more monsters left of this tier. Clear a room to fight the next tier." << endl;
        }
    }

    else
    {
        cout << "Sorcerer defeated. You can no longer fight monsters." << endl;
    }

    return monster_defeated;
}


/**
 * Algorithm: fight a monster and determine who won, the party or the monster.
 * 1. Declare variables int outcome, int temp, int w, int d = 0, int a, int c, int r1, and int r2.
 * 2. Set w = to the number of weapons the party has. Add weapon bonuses.
 * 3. Set a = 1 + the number of suits of armor the party has.
 * 4. Set c = the tier of the monster.
 * 5. Set r1 to a random number between 1 and 6.
 * 6. Set r2 to a random number between 1 and 6.
 * 7. Add d to the product of r1 and w and set the value to outcome.
 * 8. Divide the product of r2 and c by a and set the value to temp.
 * 9. Subtract the value of temp from outcome.
 * Parameters: monster (string).
 * Returns: outcome.
*/
int Game::fightMonster( string monster )
{
    srand(time(0));

    int outcome;
    int temp;

    int w;
    int d = 0;
    int a;
    int c;
    int r1;
    int r2;

    w = getTotalWeapons();

    if ( getWeapons(2) > 0 )
    {
        w += getWeapons(2);
    }

    if ( getWeapons(3) > 0 )
    {
        w += (2 * getWeapons(3));
    }

    if ( getWeapons(4) > 0 )
    {
        w += (3 * getWeapons(4));
    }

    if ( getUniqueWeapons() == getNumMembers() )
    {
        d = 4;
    }

    a = getArmor() + 1;
    c = getMonsterHealth(monster);

    r1 = randomNumbers(1, 6);
    r2 = randomNumbers(1, 6);

    outcome = r1;
    outcome *= w;
    outcome += d;

    temp = r2;
    temp *= c;
    temp = temp / a;

    outcome -= temp;

    return outcome;
}


/**
 * Algorithm: rock, paper, scissors game with an AI opponent.
 * 1. Declare variables int count = -1, char door_choice, and char party_choice.
 * 2. Declare arrays char door_choices = b, p, s.
 * 3. Prompt the user for their choice.
 * 4. Randomly pick a choice for the AI.
 * 5. Compute the winner. If the game is a tie then repeat for up to three games.
 * Parameters: none.
 * Returns: false.
*/
bool Game::boulderParchmentShears()
{
    srand(time(0));

    int count = -1;
    char door_choices[3] = {'b', 'p', 's'};
    char door_choice;
    char party_choice;

    do 
    {
        count++;

        do 
        {
            cout << "Pick One:" << endl <<
                "Boulder (B)" << endl <<
                "Parchment (P)" << endl <<
                "Shears (S)" << endl;
            cin >> party_choice;
            
            if ( tolower(party_choice) != 'b' && tolower(party_choice) != 'p' && tolower(party_choice) != 's' )
            {
                cout << "Invalid input." << endl;
            }
        }
        while ( tolower(party_choice) != 'b' && tolower(party_choice) != 'p' && tolower(party_choice) != 's' );

        party_choice = tolower(party_choice);
        door_choice = door_choices[randomNumbers(0, 2)];

        if ( party_choice == 'b' )
        {
            if ( door_choice == 's' )
            {
                return true;
            }

            else if ( door_choice == 'p' )
            {
                return false;
            }

            else if ( door_choice == 'b' )
            {
                cout << "Tie" << endl;
                continue;
            }
        }

        else if ( party_choice == 'p' )
        {
            if ( door_choice == 'b' )
            {
                return true;
            }

            else if ( door_choice == 's' )
            {
                return false;
            }

            else if ( door_choice == 'p' )
            {
                cout << "Tie" << endl;
                continue;
            }
        }

        else if ( party_choice == 's' )
        {
            if ( door_choice == 'p' )
            {
                return true;
            }

            else if ( door_choice == 'b' )
            {
                return false;
            }

            else if ( door_choice == 's' )
            {
                cout << "Tie" << endl;
                continue;
            }
        }
    }
    while ( count < 2 );

    return false;
}


/**
 * Algorithm: has a chance of choosing a random misfortune that befells the party.
 * 1. Compute a random number between 1 and 4.
 * 2. Case 1, 33% chance of the party getting robbed.
 * 3. Case 2, 10% chance of a suit of armor or a weapon breaking.
 * 4. Case 3, 33% chance of one member getting food poisoning and losing 10hp.
 * 5. Case 4, 33% chance of a member being locked in a room and dying.
 * Parameters: room (bool).
 * Returns: void.
*/
void Game::misfortunes( bool room )
{
    srand(time(0));

    int choose_misfortune;
    int stolen;
    int armor_weapons;
    int random_member;

    string weapons[5] = { "Stone Club", "Iron Spear", "(+1) Mythril Rapier", "(+2) Flaming Battle-Axe", "(+3) Vorpal Longsword" };

    choose_misfortune = randomNumbers(1, 4);

    if ( randomNumbers(1, 3) == 2 && choose_misfortune == 1 )
    {
        cout << "OH NO! Your team was robbed by dungeon bandits!" << endl;

        stolen = randomNumbers(1, 3);

        if ( stolen == 1 )
        {
            if ( getIngrediants() > 10 )
            {
                cout << "You lost 10kg of ingrediants!" << endl;
                setIngrediants(getIngrediants() - 10);
            }

            else
            {
                cout << "You lost all of your ingrediants!" << endl;
                setIngrediants(0);
            }
        }

        else if ( stolen == 2 )
        {
            if ( getTotalCookware() > 0 )
            {
                cout << "You lost 1 Cookware!" << endl;

                for ( int i = getTotalCookware() - 1; i >= 0; i-- )
                {
                    if ( getCookware(i) > 0 )
                    {
                        setCookware(getCookware(i) - 1, i);
                        break;
                    }
                }
            }

            else
            {
                cout << "You had nothing of value to the bandits." << endl;
            }
        }

        else if ( stolen == 3 )
        {
            if ( getArmor() > 0 )
            {
                cout << "You lost 1 suit of Armor!" << endl;
                setArmor(getArmor() - 1);
            }

            else
            {
                cout << "You had nothing of value to the bandits." << endl;
            }
        }
    }

    else if ( randomNumbers(1, 10) == 3 && choose_misfortune == 2 )
    {
        armor_weapons = randomNumbers(1, 2);

        if ( armor_weapons == 1 )
        {
            if ( getArmor() > 0 )
            {
                cout << "OH NO! one of your suits of armor broke" << endl;
                setArmor(getArmor() - 1);
            }
        }

        else if ( armor_weapons == 2 )
        {
            if ( getTotalWeapons() > 0 )
            {
                for ( int i = 0; i < 5; i++ )
                {
                    if ( getWeapons(i) > 0 )
                    {
                        cout << "OH NO! Your " << weapons[i] << " broke" << endl;
                        setWeapon(getWeapons(i) - 1, i);
                    }
                }
            }
        }
    }

    else if ( randomNumbers(1, 3) == 2 && choose_misfortune == 3 )
    {
        cout << "OH NO! One of you members got food poisoning!" << endl;

        if ( getMembers()[getNumMembers() - 1].getHealth() > 10 )
        {
            damage(getMembers()[getNumMembers() - 1].getName(), 10);
        }

        else
        {
            killMember(getNumMembers() - 1);
            setMaxWeapons(getNumMembers());
            setMaxArmor(getNumMembers());

            if ( getTotalWeapons() > 0 )
            {
                for ( int i = 0; i < 5; i++ )
                {
                    if ( getWeapons(i) > 0 )
                    {
                        setWeapon(getWeapons(i) - 1, i);
                        break;
                    }
                }
            }

            if ( getArmor() > 0 )
            {
                setArmor(getArmor() - 1);
            }
        }
    }

    else if ( randomNumbers(1, 3) == 2 && choose_misfortune == 4 && room == true )
    {
        random_member = randomNumbers(1, (getNumMembers() - 1));

        cout << "OH NO! Your teammate " << getMembers()[random_member].getName() << " is trapped in the previous room and is unable to get through. You must continue without them." << endl;

        killMember(random_member);
        setMaxWeapons(getNumMembers());
        setMaxArmor(getNumMembers());

        if ( getTotalWeapons() > 0 )
        {
            for ( int i = 0; i < 5; i++ )
            {
                if ( getWeapons(i) > 0 )
                {
                    setWeapon(getWeapons(i) - 1, i);
                    break;
                }
            }
        }

        if ( getArmor() > 0 )
        {
            setArmor(getArmor() - 1);
        }
    }

    return;
}