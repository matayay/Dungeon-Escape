// Author: Matayay Karuna

#ifndef PARTY_H
#define PARTY_H

#include <iostream>
#include <string>
#include <vector>
#include "Member.h"

using namespace std;


class Party
{
    public:
        // Constructors.
        Party();
        // Party( Member player, Member member_one, Member member_two, Member member_three, Member member_four );

        // Getters.
        int getNumMembers();
        int getMemberHealth( string member );
        vector<Member> getMembers();
        bool isPlayerAlive();

        // Setters.
        void damage( string member, int hp );
        void killMember( int index );

        // Member functions.
        void eat( int kg );
        void printParty();

    private:
        int num_members;
        vector<Member> members;
        Member main_player;
};

#endif