// Author: Matayay Karuna

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Monster.h"

using namespace std;


Monster::Monster()
{
    string line;
    string monster_arr[2];

    ifstream fin;
    fin.open("monsters.txt");

    if ( fin.fail() )
    {
        cout << "File failed to open." << endl;
    }

    else
    {
        while ( getline(fin, line) )
        {
            monsters.push_back(line);

            split( line, ',', monster_arr, 2 );

            if ( stoi(monster_arr[1]) == 1 )
            {
                tier1.push_back(line);
            }

            else if ( stoi(monster_arr[1]) == 2 )
            {
                tier2.push_back(line);
            }

            else if ( stoi(monster_arr[1]) == 3 )
            {
                tier3.push_back(line);
            }

            else if ( stoi(monster_arr[1]) == 4 )
            {
                tier4.push_back(line);
            }

            else if ( stoi(monster_arr[1]) == 5 )
            {
                tier5.push_back(line);
            }

            else if ( stoi(monster_arr[1]) == 6 )
            {
                sorcerer = line;
            }
        }
    }

    fin.close();
}


vector<string> Monster::getMonsters()
{
    return monsters;
}


vector<string> Monster::getTier1()
{
    return tier1;
}


vector<string> Monster::getTier2()
{
    return tier2;
}


vector<string> Monster::getTier3()
{
    return tier3;
}


vector<string> Monster::getTier4()
{
    return tier4;
}


vector<string> Monster::getTier5()
{
    return tier5;
}


bool Monster::isSorcererAlive()
{
    for ( int i = 0; i < monsters.size(); i++ )
    {
        if ( monsters[i] == sorcerer )
        {
            return true;
        }
    }

    return false;
}


string Monster::getMonsterName( string monster )
{
    string monster_arr[2];

    split(monster, ',', monster_arr, 2);

    return monster_arr[0];
}


int Monster::getMonsterHealth( string monster )
{
    string monster_arr[2];

    split(monster, ',', monster_arr, 2);

    return stoi(monster_arr[1]);
}


void Monster::killMonster( string monster, int tier )
{
    if ( tier == 6 )
    {
        monsters.pop_back();
        return;
    }

    for ( int i = 0; i < monsters.size(); i++ )
    {
        if ( monsters[i] == monster )
        {
            monsters.erase(monsters.begin() + i);
        }
    }

    if ( tier == 1 )
    {
        for ( int i = 0; i < tier1.size(); i++ )
        {
            if ( tier1[i] == monster )
            {
                tier1.erase(tier1.begin() + i);
            }
        }
    }

    else if ( tier == 2 )
    {
        for ( int i = 0; i < tier2.size(); i++ )
        {
            if ( tier2[i] == monster )
            {
                tier2.erase(tier2.begin() + i);
            }
        }
    }

    else if ( tier == 3 )
    {
        for ( int i = 0; i < tier3.size(); i++ )
        {
            if ( tier3[i] == monster )
            {
                tier3.erase(tier3.begin() + i);
            }
        }
    }

    else if ( tier == 4 )
    {
        for ( int i = 0; i < tier4.size(); i++ )
        {
            if ( tier4[i] == monster )
            {
                tier4.erase(tier4.begin() + i);
            }
        }
    }

    else if ( tier == 5 )
    {
        for ( int i = 0; i < tier5.size(); i++ )
        {
            if ( tier5[i] == monster )
            {
                tier5.erase(tier5.begin() + i);
            }
        }
    }
}


/**
 * Algorithm: Splits up a given string at given deliminator(s) and stores the split contents in a given array.
 * 1. Accept string input_string, char separator, string arr[], and int arr_size as parameters.
 * 2. Declare variables string split = "", int count = 0, and int index_array = 0.
 * 3. Check if the given string is empty, if so stop and return 0.
 * 4. Go through each character in the given string.
 * 5. Check if the array has space left to add new elements, if no then stop and return -1.
 * 6. Check if the current character in the string matches the given deliminator.
 * 7. If so then cut out the section of the string starting from the last deliminator or the begginning of the string
 *      and go to the current detected deliminator.
 * 8. Check if the current character is the last character in the string.
 * 9. If so then cut out the section of the string starting from the last deliminator or the begginning of the string
 *      and go to the end of the string.
 * 10. If the string has no deliminator then populate index 0 of the array with the entire string and return 1;
 * Parameters: input_string (string), separator (char), arr[] (string), arr_size (int).
 * Returns: The number of times the string was split.
*/
int Monster::split( string input_string, char separator, string arr[], int arr_size )
{
    // Declare variables.
    string split = "";
    int count = 0;
    int index_array = 0;

    // Checks to see if input_string is empty. If so return 0.
    if ( input_string == "" )
    {
        return 0;
    }

    // Loops through each character in input_string.
    for ( int i = 0; i < (int) input_string.length(); i++ )
    {
        // If the string can be split up more but the array is full then return -1;
        if ( index_array == arr_size )
        {
            return -1;
        }

        // Looks for the given deliminator in the string.
        if ( input_string[i] == separator )
        {
            // If the string hasn't already been split and this is the first time.
            if ( index_array == 0 )
            {
                // Reset this variable to empty.
                split = "";

                // Start from beginning of string and copy each character into split until deliminator is reached.
                for ( int j = count; j < i; j++ )
                {   
                    split += input_string[j];
                }

                // Add split into the first spot in the array.
                arr[index_array] = split;

                index_array++;
                count = i; // Set count = i so that next time a split occurs it starts from the previous deliminator.
            }

            // If the string has been split before.
            else
            {
                // Reset this variable to empty.
                split = "";

                // Start from last deliminator and copy each character into split until next deliminator is reached.
                for ( int j = count+1; j < i; j++ )
                {   
                    split += input_string[j];
                }

                // Add split into the array at index = index_array.
                arr[index_array] = split;

                index_array++;
                count = i; // Set count = i so that next time a split occurs it starts from the previous deliminator.
            }
        }
        
        // If the loop has reached the end of input_string but has had previous splits.
        if ( i == (int) input_string.length() - 1 && index_array > 0 )
        {
            // Reset this variable to empty.
            split = "";

            // Start from last deliminator and copy each character into split until the end of input_string is reached.
            for ( int j = count+1; j <= i; j++ )
            {   
                split += input_string[j];
            }

            // Add split into the array at index = index_array.
            arr[index_array] = split;

            index_array++;
            count = i;
        }
    }

    // If the loop has reached the end of input_string and has never been split.
    // Return 1.
    if ( index_array == 0 )
    {
        // Adds all of input_string into the first spot in the array.
        arr[0] = input_string;

        return 1;
    }

    return index_array; // Retruns the number of times the string was split.
}

