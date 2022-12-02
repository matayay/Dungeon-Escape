// Author: Matayay Karuna

#include <iostream>
#include <string>
#include <cctype>
#include "Merchant.h"

using namespace std;


Merchant::Merchant()
{
    price = 1;
}


int Merchant::getPrice()
{
    return price;
}


void Merchant::setPrice( double new_price )
{
    price = new_price;
}


void Merchant::menu()
{
    // Declare variables.
    int choice;
    int amount;
    char confirm;
    int gold;
    int item_price;

    int cookware;
    int pot = 2 * price;
    int pan = 10 * price;
    int cauldron = 20 * price;

    int ingrediants = 1 * price;

    int weapons;
    int club = 2 * price;
    int spear = 2 * price;
    int rapier = 5 * price;
    int axe = 15 * price;
    int longsword = 50 * price;

    int armor = 5 * price;

    int treasures;
    int ring = 10;
    int necklace = 20;
    int bracelet = 30;
    int circlet = 40;
    int goblet = 50;

    // Declare arrays.
    string cookware_arr[3] = { "Ceramic Pot(s)", "Frying Pan(s)", "Cauldron(s)" };
    string weapons_arr[5] = { "Stone Club(s)", "Iron Spear(s)", "(+1) Mythril Rapier(s)", "(+2) Flaming Battle-Axe(s)", "(+3) Vorpal Longsword(s)" };
    string treasures_arr[5] = { "Silver Ring(s)", "Ruby Necklace(s)", "Emerald Bracelet(s)", "Diamond Circlet(s)", "Gem-encrusted Goblet(s)" };
    int cookware_price[3] = { pot, pan, cauldron };
    int weapons_price[5] = { club, spear, rapier, axe, longsword };
    int treasures_price[5] = { ring, necklace, bracelet, circlet, goblet };


    cout << "\n" << "If you're looking to get supplies, you've come to the right place." << endl <<
        "I would be happy to part with some of my wares...for the proper price!" << endl;

    do 
    {   
        cout << "\n";
        printInventory();
        cout << "\n" << "Choose one of the following:" << endl <<
            "1. Ingredients: To make food, you have to cook raw ingredients." << endl <<
            "2. Cookware: You will need something to cook those ingredients." << endl <<
            "3. Weapons: It's dangerous to go alone, take this!" << endl <<
            "4. Armor: If you want to survive monster attacks, you will need some armor." << endl <<
            "5. Sell treasures: If you find anything shiny, I would be happy to take it off your hands." << endl <<
            "6. Leave: Make sure you get everything you need, I'm leaving after this sale!" << endl;
        cin >> choice;

        if ( choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 )
        {
            cout << "Invalid input, please try again." << endl;
            continue;
        }

        else if ( choice == 1 )
        {
            cout << "\n" << "How many kg of ingredients do you need [" << ingrediants << " gold/kg]?" << "(Enter a positive mulitple of 5, or 0 to cancel): " << endl;
            cin >> amount;

            if ( amount < 0 || amount % 5 != 0 )
            {
                cout << "Invalid input, please try again." << endl;
                continue;
            }

            else if ( amount == 0 )
            {
                continue;
            }

            gold = getGold();
            item_price = ingrediants * amount;
            
            if ( gold < item_price )
            {
                cout << "You cannot afford to buy this." << endl;
            }

            else
            {
                cout << "\n" << "You want to buy " << amount << " kg of ingrediants for " << item_price << " Gold? (y/n): " << endl;
                cin >> confirm;

                if ( tolower(confirm) != 'y' )
                {
                    continue;
                }

                setGold(gold - item_price);
                setIngrediants(getIngrediants() + amount);
                cout << "\n" << "Thank you for your patronage! What else can I get for you?" << endl;
            }
        }

        else if ( choice == 2 )
        {
            cout << "\n" << "I have a several types of cookware, which one would you like?" << endl <<
                "Each type has a different probability of breaking when used, marked with (XX%)." << endl;

            do 
            {
                cout << "\n" << "Choose one of the following:" << endl <<
                    "1. (25%) Ceramic Pot " << pot << " gold" << endl <<
                    "2. (10%) Frying Pan " << pan << " gold" << endl <<
                    "3. ( 2%) Cauldron " << cauldron << " gold" << endl <<
                    "4. Cancel" << endl;
                cin >> cookware;

                if ( cookware != 1 && cookware != 2 && cookware != 3 && cookware != 4 )
                {
                    cout << "Invalid input, please try again." << endl;
                    continue;
                }

                else if ( cookware == 4 )
                {
                    break;
                }

                cout << "\n" << "How many would you like? (Enter a positive integer, or 0 to cancel): " << endl;
                cin >> amount;

                if ( amount < 0 )
                {
                    cout << "Invalid input, please try again." << endl;
                    continue;
                }

                else if ( amount > 0 )
                {
                    gold = getGold();
                    item_price = cookware_price[cookware-1] * amount;
                    
                    if ( gold < item_price )
                    {
                        cout << "You cannot afford to buy this." << endl;
                    }

                    else
                    {
                        cout << "\n" << "You want to buy " << amount << " " << cookware_arr[cookware-1] << " for " << item_price << " Gold? (y/n): " << endl;
                        cin >> confirm;

                        if ( tolower(confirm) != 'y' )
                        {
                            continue;
                        }

                        setGold(gold - item_price);
                        setCookware((getCookware(cookware-1) + amount), (cookware-1));
                        cout << "\n" << "Thank you for your patronage! What else can I get for you?" << endl;
                    }
                }
            }
            while ( cookware != 3 );
        }

        else if ( choice == 3 )
        {
            cout << "\n" << "I have a plentiful collection of weapons to choose from, what would you like?" << endl <<
                "Note that some of them provide you a special bonus in combat, marked by a (+X)." << endl;

            do 
            {
                cout << "\n" << "Choose one of the following:" << endl << 
                "1. Stone Club " << club << " gold" << endl <<
                "2. Iron Spear " << spear << " gold" << endl <<
                "3. (+1) Mythril Rapier " << rapier << " gold" << endl <<
                "4. (+2) Flaming Battle-Axe " << axe << " gold" << endl <<
                "5. (+3) Vorpal Longsword " << longsword << " gold" << endl <<
                "6. Cancel" << endl;
                cin >> weapons;

                if ( weapons != 1 && weapons != 2 && weapons != 3 && weapons != 4 && weapons != 5 && weapons != 6 )
                {
                    cout << "Invalid input, please try again." << endl;
                    continue;
                }

                else if ( weapons == 6 )
                {
                    break;
                }

                cout << "\n" << "How many would you like? (Enter a positive integer, or 0 to cancel): " << endl;
                cin >> amount;

                if ( amount < 0 )
                {
                    cout << "Invalid input, please try again." << endl;
                    continue;
                }

                else if ( amount > 0 )
                {
                    gold = getGold();
                    item_price = weapons_price[weapons-1] * amount;

                    if ( gold < item_price )
                    {
                        cout << "You cannot afford to buy this." << endl;
                    }

                    else if ( (getTotalWeapons() + amount) > getMaxWeapons() )
                    {
                        cout << "You cannot carry any more weapons." << endl;
                    }

                    else
                    {
                        cout << "\n" << "You want to buy " << amount << " " << weapons_arr[weapons-1] << " for " << item_price << " Gold? (y/n): " << endl;
                        cin >> confirm;

                        if ( tolower(confirm) != 'y' )
                        {
                            continue;
                        }

                        setGold(gold - item_price);
                        setWeapon((getWeapons(weapons-1) + amount), (weapons-1));
                        cout << "\n" << "Thank you for your patronage! What else can I get for you?" << endl;
                    }
                }
            }
            while( weapons != 5 );
        }

        else if ( choice == 4 )
        {
            cout << "\n" << "How many suits of armor can I get you? (Enter a positive integer, or 0 to cancel): " << endl;
            cin >> amount;

            if ( amount < 0 )
            {
                cout << "Invalid input, please try again." << endl;
                continue;
            }

            else if ( amount == 0 )
            {
                continue;
            }

            gold = getGold();
            item_price = armor * amount;
            
            if ( gold < item_price )
            {
                cout << "You cannot afford to buy this." << endl;
            }

            else if ( (getArmor() + amount) > getMaxArmor() )
            {
                cout << "You cannot carry any more armor." << endl;
            }

            else
            {
                cout << "\n" << "You want to buy " << amount << " suit(s) of armor for " << item_price << " Gold? (y/n): " << endl;
                cin >> confirm;

                if ( tolower(confirm) != 'y' )
                {
                    continue;
                }

                setGold(gold - item_price);
                setArmor(getArmor() + amount);
                cout << "\n" << "Thank you for your patronage! What else can I get for you?" << endl;
            }
        }

        else if ( choice == 5 )
        {
            do 
            {
                cout << "\n" << "What would you like to sell?" << endl <<
                "1. 1 Room: Silver ring - 10 gold pieces each" << endl <<
                "2. 2 Rooms: Ruby necklace - 20 gold pieces each" << endl <<
                "3. 3 Rooms: Emerald bracelet - 30 gold pieces each" << endl <<
                "4. 4 Rooms: Diamond circlet - 40 gold pieces each" << endl <<
                "5. 5 Rooms: Gem-encrusted goblet - 50 gold pieces each" << endl <<
                "6. Cancel." << endl;
                cin >> treasures;

                if ( treasures != 1 && treasures != 2 && treasures != 3 && treasures != 4 && treasures != 5 && treasures != 6 )
                {
                    cout << "Invalid input, please try again." << endl;
                    continue;
                }

                else if ( treasures == 6 )
                {
                    break;
                }

                cout << "\n" << "How many would you like to sell? (Enter a positive integer, or 0 to cancel): " << endl;
                cin >> amount;

                if ( amount < 0 )
                {
                    cout << "Invalid input, please try again." << endl;
                    continue;
                }

                else if ( amount > 0 )
                {
                    gold = getGold();
                    item_price = treasures_price[treasures-1] * amount;

                    cout << "\n" << "You want to sell " << amount << " " << treasures_arr[treasures-1] << " for " << item_price << " Gold? (y/n): " << endl;
                    cin >> confirm;

                    if ( tolower(confirm) != 'y' )
                    {
                        continue;
                    }

                    else if ( getTreasures(treasures-1) < amount )
                    {
                        cout << "You are trying to sell items you do not have." << endl;
                    }

                    else
                    {
                        setGold(gold + item_price);
                        setTreasure((getTreasures(treasures-1) - amount), (treasures-1));
                        cout << "\n" << "Thank you for your patronage! What else can I get for you?" << endl;
                    }
                }
            }
            while ( treasures != 6 );
        }
    }
    while( choice != 6 );

    return;
}