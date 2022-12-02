// Author: Matayay Karuna

#include <iostream>
#include <string>
#include "Member.h"

using namespace std;


Member::Member()
{
    name = "";
    health = 0;
}


Member::Member( string member_name, int member_health )
{
    name = member_name;
    health = member_health;
}


int Member::getHealth()
{
    return health;
}


string Member::getName()
{
    return name;
}


void Member::setHealth( int hp )
{
    health = hp;
}