#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "fields.h"
#include "player.h"

#include <string>
#include <map>

class Gameboard {
public:

    // Porusza gracza do przodu o liczbę steps
    void move(Player &player, int steps) {
    }

    // Zwraca nazwe pola na którym znajude sie gracz
    std::string const getPlayerPosition(Player &player) const {
    }

    // Dodaje nowe pole
    void addField(std::shared_ptr<Field> &field) {
    }

    // Dodaje nowego gracza
    void addPlayer(Player &player) {
        player_position[player] = 1;
    }

private:
    int field_num;
    std::map<Player,int> player_position;
    std::map<int, std::shared_ptr<Field>> fields;
};

#endif