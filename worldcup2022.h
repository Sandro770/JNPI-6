#ifndef WORLDCUP2022_H
#define WORLDCUP2022_H

#include "worldcup.h"
#include "player.h"
#include "field.h"
#include "exceptions.h"
#include "dice.h"
#include "gameboard.h"

#include <memory>
#include <string>
#include <vector>
#include <map>

class WorldCup2022 : public WorldCup {
public:
    const size_t REQUIRED_DICE = 2;
    const int START_MONEY = 1000;

    ~WorldCup2022() = default;

    void addDie(std::shared_ptr<Die> die) override {
        dice.addDice(die);
    }

    void addPlayer(std::string const &name) override {
        Player new_player = Player(name,START_MONEY);
        players.push_back(new_player);
        board.addPlayer(new_player);
    }

    void setScoreBoard(std::shared_ptr<ScoreBoard> scoreboard) override {
        this->scoreboard = scoreboard;
    }

    void play(unsigned int rounds) override {
        if (dice.size() < REQUIRED_DICE) {
            throw TooFewDiceException();
        }
        if (dice.size() > REQUIRED_DICE) {
            throw TooManyDiceException();
        }
        if (players.size() > 11) {
            throw TooManyPlayersException();
        }
        if (players.size() < 2) {
            throw TooFewPlayersException();
        }

        initBoard();

        for (unsigned int round_num = 0; round_num < rounds; round_num++) {
            scoreboard->onRound(round_num);
            for (auto &player : players) {
                if (!player.isInGame()) {
                    continue;
                }

                if (!player.isWaiting()) {
                    int sum = dice.roll();
                    board.move(player, sum);
                }
                scoreboard->onTurn(player.getName(), player.getStatus(), board.getPlayersPosition(player), player.getMoney());
                if (player.isWaiting()) {
                    player.decreaseWaitingTime();
                }
            }

            int alive_num = 0;
            std::string winner;
            int max_money = 0;
            for (auto &player : players) {
                max_money = std::max(max_money, player.getMoney());
                if(player.isInGame()) {
                    alive_num++;
                    winner = player.getName();
                }
            }
            if (alive_num == 1 || round_num == rounds - 1) {
                for (auto &player : players) {
                    if (player.isInGame() && player.getMoney() == max_money) {
                        winner = player.getName();
                    }
                }
                scoreboard->onWin(winner);
                return;
            }
        }
    }

private:
    std::shared_ptr<ScoreBoard> scoreboard;
    Dice dice;
    std::vector<Player> players;
    Gameboard board;

    void initBoard() {
        board.addField(std::make_shared<SeasonField>("Początek sezonu"));
        
        board.addField(std::make_shared<MatchField>("Mecz z San Marino",160,1));
        
        board.addField(std::make_shared<EmptyField>("Dzień wolny od treningu"));
    
        board.addField(std::make_shared<MatchField>("Mecz z Lichtensteinem",220,1));

        board.addField(std::make_shared<YellowCardField>("Żółta kartka",3));

        board.addField(std::make_shared<MatchField>("Mecz z Meksykiem",300,2.5));

        board.addField(std::make_shared<MatchField>("Mecz z Arabią Saudyjską",280,2.5));

        board.addField(std::make_shared<BookmakerField>("Bukmacher",100));

        board.addField(std::make_shared<MatchField>("Mecz z Argentyną",250,2.5));

        board.addField(std::make_shared<GoalField>("Gol",120));
        
        board.addField(std::make_shared<MatchField>("Mecz z Francją",400,4));
        
        board.addField(std::make_shared<PenaltyField>("Rzut karny",180));
    }
};

#endif