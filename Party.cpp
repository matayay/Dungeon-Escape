// Author: Matayay Karuna

#include <iostream>
#include <string>
#include "Party.h"

using namespace std;


Party::Party()
{
    // Declare variables.
    string player;
    string member;

    // Declare arrays.
    Member party[5];

    cout << "Enter your name: " << endl;
    getline(cin, player);
    party[0] = Member(player, 50);
    members.push_back(party[0]);
    main_player = party[0];

    for ( int i = 1; i < 5; i++ )
    {
        cout << "Enter name for member " << i << ": " << endl;
        getline(cin, member);
        party[i] = Member(member, 50);
        members.push_back(party[i]);
    }

    num_members = 5;
}


int Party::getNumMembers()
{
    return num_members;
}


int Party::getMemberHealth( string member )
{
    for ( int i = 0; i < num_members; i++ )
    {
        if ( members[i].getName() == member )
        {
            return members[i].getHealth();
        }
    }

    return -1;
}


vector<Member> Party::getMembers()
{
    return members;
}


bool Party::isPlayerAlive()
{
    for ( int i = 0; i < members.size(); i++ )
    {
        if ( members[i].getName() == main_player.getName() )
        {
            return true;
        }
    }

    return false;
}


void Party::damage( string member, int hp )
{
    int index = -1;
    int health_change;

    for ( int i = 0; i < num_members; i++ )
    {
        if ( members[i].getName() == member )
        {
            index = i;
            break;
        }
    }

    if ( index == -1 )
    {
        cout << "There is no living member by that name." << endl;
        return;
    }

    health_change = members[index].getHealth() - hp;
    members[index].setHealth(health_change);

    return;
}


void Party::killMember( int index )
{
    members.erase(members.begin() + index);
    num_members--;
}


void Party::eat( int kg )
{
    int hp = kg / 5;
    int health_change;

    for ( int i = 0; i < num_members; i++ )
    {
        health_change = members[i].getHealth() + hp;
        members[i].setHealth(health_change);
    }

    return;
}


void Party::printParty()
{
    cout << "+-------------+" << endl <<
        "| PARTY       |" << endl <<
        "+-------------+" << endl;

    for ( int i = 0; i < members.size(); i++ )
    {
        cout << "| " << members[i].getName() << " | Fullness: " << getMemberHealth(members[i].getName()) << endl;
    }

    cout << "+-------------+" << "\n" << endl;

    return;
}