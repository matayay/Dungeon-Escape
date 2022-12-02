// Author: Matayay Karuna

#ifndef RIDDLES_H
#define RIDDLES_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Monster.h"

using namespace std;


class Riddles: public Monster
{
    public:
        Riddles();

        string getRiddle( int index );
        string getRiddleAnswer( int index );
    
    private:
        vector<string> riddles;
        vector<string> questions;
        vector<string>answers;
};

#endif