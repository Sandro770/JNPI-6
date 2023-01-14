#ifndef FIELD_H
#define FIELD_H

#include "player.h"

class Field {
public:
    Field(std::string &name) : name(name) {}


    virtual void actionOnPassing(Player &player) = 0;
    virtual void actionOnStop(Player &player) = 0;

private:
    std::string name;
};

class MatchField : public Field {
public:

    MatchField(std::string &name, int fee, float weight) : Field(name), money(0), fee(fee), weight(weight) {}

    // Nawet jak nie ma tyle to i tak dodajemy tyle do puli
    // i ustawiamy gracza jako bankruta.
    void actionOnPassing(Player &player) override {
        player.subMoney(fee);
        money += fee;
    }

    void actionOnStop(Player &player) override {
        player.addMoney(money * weight);
        money = 0;
    }

private:
    int money;
    int fee;
    float weight;
};

class BookmakerField : public Field {
public:

    BookmakerField(std::string &name, int bonus) : Field(name), series(0), bonus(bonus) {}

    void actionOnPassing(Player &player) override {}

    void actionOnStop(Player &player) override {
        if (series == 0) {
            player.addMoney(bonus);
        } else {
            player.subMoney(bonus);
        }
        series = (series + 1) % 3;
    }

private:
    int series;
    int bonus;
};

class PenaltyField : public Field {
public:

    PenaltyField(std::string &name, int fee) : Field(name), fee(fee) {}
    
    void actionOnPassing(Player &player) override {}

    void actionOnStop(Player &player) override {
        player.subMoney(fee);
    }
private:
    int fee;
};

class YellowCardField : public Field {
public:

    YellowCardField(std::string &name, int waiting_time) : Field(name), waiting_time(waiting_time) {}
    
    void actionOnPassing(Player &player) override {}

    void actionOnStop(Player &player) override {
        player.setWaitingTime(waiting_time);
    }

private:
    int waiting_time;
};


class SeasonField : public Field {
public:
    SeasonField(std::string &name) : Field(name) {}

    void actionOnPassing(Player &player) override {
        player.addMoney(50);
    }

    void actionOnStop(Player &player) override {
        player.addMoney(50);
    }
};

class GoalField : public Field {
public:

    GoalField(std::string &name, int bonus) : Field(name), bonus(bonus) {}

    void actionOnStop(Player &player) override {
        player.addMoney(bonus);
    }

    void actionOnPassing(Player &player) override {}

private:
    int bonus;
};

#endif