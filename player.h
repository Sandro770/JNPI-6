#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
    Player(const std::string &name, int money) : name(name), money(money), waiting_time(0), is_in_game(true){}

    bool operator<(const Player& src)const
    {
        return (this->name.compare(src.name) > 0);
    }

    void addMoney(int amount) {
        money += amount;
    }

    void subMoney(int amount) {
        money -= amount;
    }

    int getMoney() const {
        return money;
    }

    void setWaitingTime(int waiting_time) {
        this->waiting_time = waiting_time;
    }

    void decreaseWaitingTime() {
        if (waiting_time > 0) {
            waiting_time--;
        }
    }

    std::string const &getName() const {
        return name;
    }

    // Zwraca status gracz (czy jest w grze, czy czeka, czy jest bankrutem)
    std::string const getStatus() const {
        return "";
    }

private:
    const std::string name;
    int money;
    int waiting_time;
    bool is_in_game;
};

#endif