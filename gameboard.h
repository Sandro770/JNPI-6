#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "field.h"
#include "player.h"

#include <string>
#include <map>
#include <memory>

class Gameboard {
public:
    void move(Player &player, int steps) {
        int position = player_position.find(player)->second;

        while (steps > 1) {
            position = nextPosition(position);
            auto passing_field = fields[position];
            passing_field->actionOnPassing(player);
            steps--;
        }
        position = nextPosition(position);
        auto stop_field = fields[position];

        stop_field->actionOnStop(player);

        player_position[player] = position;
    }

    std::string const getPlayersPosition(Player &player) const {
        int field_number = player_position.find(player)->second;
        return fields.find(field_number)->second->getName();
    }

    void addField(std::shared_ptr<Field> field) {
        field_num++;
        fields[field_num] = field;
    }

    void addPlayer(Player &player) {
        alive_players++;
        player_position[player] = 1;
    }

    void deadPlayer() {
        alive_players--;
    }

    bool isGameOver() {
        return alive_players == 1;
    }

private:
    int field_num = 0;
    int alive_players;
    std::map<Player,int> player_position;
    std::map<int, std::shared_ptr<Field>> fields;

    int nextPosition(int current) {
        if(current + 1 > field_num) {
            return 1;
        } else {
            return current + 1;
        }
    }
};

#endif