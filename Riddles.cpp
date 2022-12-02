// Author: Matayay Karuna

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Riddles.h"

using namespace std;


Riddles::Riddles()
{
    string line;
    string riddles_arr[2];

    ifstream fin;
    fin.open("riddles.txt");

    if ( fin.fail() )
    {
        cout << "File failed to open" << endl;
    }

    else
    {
        while ( getline(fin, line) )
        {
            riddles.push_back(line);

            split(line, '~', riddles_arr, 2);

            questions.push_back(riddles_arr[0]);
            answers.push_back(riddles_arr[1]);
        }
    }

    fin.close();
}


string Riddles::getRiddle( int index )
{
    return questions[index];
}


string Riddles::getRiddleAnswer( int index )
{
    return answers[index];
}