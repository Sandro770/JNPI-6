#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <sstream>

class Player {
public:
    Player(const std::string &name, int money) : name(name), money(money), waiting_time(0), is_in_game(true){}

    bool operator<(const Player& src)const
    {
        return (this->name.compare(src.name) > 0);
    }

    void addMoney(int amount) {
        if (is_in_game) {
            money += amount;
        }
    }

    void subMoney(int amount) {
        if (is_in_game) {
            money -= amount;
        }
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

    int getWaitingTime() {
        return waiting_time;
    }

    bool isWaiting() {
        return waiting_time > 0;
    }

    bool isInGame() {
        return is_in_game;
    }

    void game_over() {
        is_in_game = false;
    }

    std::string const &getName() const {
        return name;
    }

    // Zwraca status gracz (czy jest w grze, czy czeka, czy jest bankrutem)
    std::string const getStatus() const {
        std::stringstream status;
        if (is_in_game && waiting_time > 0) {
            status << "*** czekanie: " << waiting_time << " ***";
            
        } else if (is_in_game) {
            status << "w grze";
        } else {
            status << "*** bankrut ***";
        }

        return status.str();
    }

private:
    const std::string name;
    int money;
    int waiting_time;
    bool is_in_game;
};

#endif