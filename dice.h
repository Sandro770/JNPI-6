#ifndef DICE_H
#define DICE_H

#include "worldcup.h"
#include <vector>

class Dice {
public:

    void addDice(std::shared_ptr<Die> die) {
        dice.push_back(die);
    }

    int roll() {
        int sum = 0;

        for (auto &die : dice) {
            sum += die->roll();
        }

        return sum;
    }

    size_t size() {
        return dice.size();
    }


private:
    std::vector<std::shared_ptr<Die>> dice;
};

#endif