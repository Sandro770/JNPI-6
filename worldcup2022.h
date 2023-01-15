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
        if (dice.size() + 1 > REQUIRED_DICE) {
            throw TooManyDiceException();
        }
        dice.addDice(die);
    }

    void addPlayer(std::string const &name) override {
        if (players.size() + 1 > 11) {
            throw TooManyPlayersException();
        }
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

                if (player.isWaiting() && player.getWaitingTime() != 1) {
                    player.decreaseWaitingTime();
                    scoreboard->onTurn(player.getName(), player.getStatus(), board.getPlayersPosition(player), player.getMoney());
                    continue;
                } 

                // TODO to jest trochę głupie ale jak ktoś stanie na żóltej kartce to ta runda też zalicza się do czekania
                // bez tego ktos stoi zamiast 3 rund 4.
                if(player.getWaitingTime() == 1) {
                    player.decreaseWaitingTime();
                }

                int sum = dice.roll();
                board.move(player, sum);

                scoreboard->onTurn(player.getName(), player.getStatus(), board.getPlayersPosition(player), player.getMoney());
            }

            // TODO troche slaby sposob na sprawdzanie czy juz koniec gry
            int alive_num = 0;
            std::string winner;
            for (auto &player : players) {
                if(player.isInGame()) {
                    alive_num++;
                    winner = player.getName();
                }
            }
            if (alive_num == 1) {
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