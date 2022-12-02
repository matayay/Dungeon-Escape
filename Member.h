// Author: Matayay Karuna

#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <string>

using namespace std;


class Member
{
    public:
        // Constructors.
        Member();
        Member( string member_name, int member_health );

        // Getters.
        int getHealth();
        string getName();

        // Setters.
        void setHealth( int hp );

    private:
        int health;
        string name;
};

#endif