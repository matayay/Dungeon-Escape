// Author: Matayay Karuna

#ifndef MERCHANT_H
#define MERCHANT_H

#include <iostream>
#include <string>
#include <cctype>
#include "Inventory.h"

using namespace std; 


class Merchant: public Inventory
{
    public:
        Merchant();

        int getPrice();
        void setPrice( double new_price );

        void menu();

    private:
        double price;
};

#endif