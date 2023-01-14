#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
    Player(std::string const &name, int money) : name(name), money(money), waiting_time(0) {}

    void addMoney(int amount) {
        money += amount;
    }

    void subMoney(int amount) {
        money -= amount;
    }

    void setWaitingTime(int waiting_time) {
        this->waiting_time = waiting_time;
    }

private:
    std::string const &name;
    int money;
    int waiting_time;
};

#endif