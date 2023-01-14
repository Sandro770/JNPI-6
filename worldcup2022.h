#ifndef WORLDCUP2022_H
#define WORLDCUP2022_H

#include "worldcup.h"
#include "player.h"
#include "field.h"
#include "exceptions.h"
#include "gameboard.h"

#include <memory>
#include <string>
#include <vector>
#include <map>

class WorldCup2022 : public WorldCup {
public:
    const size_t REQUIRED_DICE = 2;

    ~WorldCup2022() = default;

    void addDie(std::shared_ptr<Die> die) override {
        if (dice.size() + 1 > REQUIRED_DICE) {
            throw TooManyDiceException();
        }
        dice.push_back(die);
    }

    void addPlayer(std::string const &name) override {
        if (players.size() + 1 > 11) {
            throw TooManyPlayersException();
        }
        players.push_back(Player(name,0));
    }

    void setScoreBoard(std::shared_ptr<ScoreBoard> scoreboard) override {
        this->scoreboard = scoreboard;
    }

    void play(unsigned int rounds) override {
        if (dice.size() < REQUIRED_DICE) {
            throw TooFewDiceException();
        }
        if (players.size() < 2) {
            throw TooFewPlayersException();
        }
        for (unsigned int round_num = 0; round_num < rounds; round_num++) {
            scoreboard->onRound(round_num);
            for (auto &player : players) {
                if (player.getStatus() == "...") {
                    player.decreaseWaitingTime();
                    continue;
                } 
                if (player.getStatus() != "in game") {
                    continue;
                }
                
                int sum = 0;
                for (auto &die : dice) {
                    sum += die->roll();
                }
                board.move(player, sum);

                scoreboard->onTurn(player.getName(), player.getStatus(), board.getPlayersPosition(player), player.getMoney());
            }
        }
    }

private:
    std::shared_ptr<ScoreBoard> scoreboard;
    std::vector<std::shared_ptr<Die>> dice;
    std::vector<Player> players;
    Gameboard board;
};

#endif