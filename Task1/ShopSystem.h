#pragma once
#include <iostream>
#include <string>

struct ShopItem {
    std::string name;
    int bonus;
    int cost;
};

class ShopSystem {
public:
    void runShop(int& money) {
        ShopItem item{"Bonus", 2, 2};
        std::cout << "[SHOP]   offered: " << item.name
                  << "(+" << item.bonus << ") cost " << item.cost << "\n";

        if (money >= item.cost) {
            money -= item.cost;
            std::cout << "[SHOP]   purchased! money left: " << money << "\n";
        } else {
            std::cout << "[SHOP]   skipped (not enough money)\n";
        }
    }
};
