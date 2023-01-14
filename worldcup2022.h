#ifndef WORLDCUP_H
#define WORLDCUP_H

#include "worldcup.h"

#include <memory>
#include <string>
#include <vector>
#include <map>

class Die;

class ScoreBoard;

// Reprezentuje interfejs gry WorldCup.
// Konkretną implementacją jest WorldCup2022.
// WorldCup2022 ma mieć konstruktor bezparametrowy.
class WorldCup {
public:
    virtual ~WorldCup() = default;

    // Jeżeli argumentem jest pusty wskaźnik, to nie wykonuje żadnej operacji
    // (ale nie ma błędu).
    virtual void addDie(std::shared_ptr<Die> die) = 0;

    // Dodaje nowego gracza o podanej nazwie.
    virtual void addPlayer(std::string const &name) = 0;

    // Konfiguruje tablicę wyników. Domyślnie jest skonfigurowana tablica
    // wyników, która nic nie robi.
    virtual void setScoreBoard(std::shared_ptr<ScoreBoard> scoreboard) = 0;

    // Przeprowadza rozgrywkę co najwyżej podanej liczby rund (rozgrywka może
    // skończyć się wcześniej).
    // Jedna runda obejmuje po jednym ruchu każdego gracza.
    // Gracze ruszają się w kolejności, w której zostali dodani.
    // Na początku każdej rundy przekazywana jest informacja do tablicy wyników
    // o początku rundy (onRound), a na zakończenie tury gracza informacje
    // podsumowujące dla każdego gracza (onTurn).
    // Rzuca TooManyDiceException, jeśli jest zbyt dużo kostek.
    // Rzuca TooFewDiceException, jeśli nie ma wystarczającej liczby kostek.
    // Rzuca TooManyPlayersException, jeśli jest zbyt dużo graczy.
    // Rzuca TooFewPlayersException, jeśli liczba graczy nie pozwala na
    // rozpoczęcie gry.
    // Wyjątki powinny dziedziczyć po std::exception.
    virtual void play(unsigned int rounds) = 0;
};

// Reprezentuje interfejs kostki do gry.
// Konkretna implementacja zostanie dostarczona przy testach.
class Die {
public:
    virtual ~Die() = default;

    // Zwraca wynik rzutu kostką.
    [[nodiscard]] virtual unsigned short roll() const = 0;
};

// Reprezentuje tablicę wyników.
class ScoreBoard {
public:
    virtual ~ScoreBoard() = default;

    // Wywoływane, aby zasygnalizować początek rundy.
    virtual void onRound(unsigned int roundNo) = 0;

    // Wywoływane po skończeniu kolejki danego gracza, aby przekazać informacje o aktualnym stanie gracza.
    virtual void onTurn(std::string const &playerName, std::string const &playerStatus,
                        std::string const &squareName, unsigned int money) = 0;

    // Wywoływane, aby zasygnalizować zwycięstwo danego gracza.
    virtual void onWin(std::string const &playerName) = 0;
};


class Player {
public:
    Player(std::string const &name, int money) : name(name), money(money) {}

    void addMoney(int amount) {
        money += amount;
    }

    void subMoney(int amount) {
        money -= amount;
    }

private:
    std::string const &name;
    int money;
};

class Field {
public:
    virtual void actionOnPassing(Player &player) = 0;
    virtual void actionOnStop(Player &player) = 0;
};

class MatchField : public Field {
public:

    MatchField(int fee, float weight) : money(0), fee(fee), weight(weight) {}

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

    BookmakerField(int bonus) : series(0), bonus(bonus) {}

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

class SeasonField : public Field {
public:
    
    void actionOnPassing(Player &player) override {
        player.addMoney(50);
    }

    void actionOnStop(Player &player) override {
        player.addMoney(50);
    }
};

class GoalField : public Field {
public:

    GoalField(int bonus) : bonus(bonus) {}

    void actionOnStop(Player &player) override {
        player.addMoney(bonus);
    }

    void actionOnPassing(Player &player) override {}

private:
    int bonus;
};


class WorldCup2022 : public WorldCup {
public:

    WorldCup2022() = default;

    ~WorldCup2022() = default;

    void addDie(std::shared_ptr<Die> die) override {
        dice.push_back(die);
    }

    void addPlayer(std::string const &name) override {
        players.push_back(Player(name,0));
    }

    void setScoreBoard(std::shared_ptr<ScoreBoard> scoreboard) override {
        this->scoreboard = scoreboard;
    }

    void play(unsigned int rounds) override {

    }

private:
    int round_num;
    std::shared_ptr<ScoreBoard> scoreboard;
    std::vector<std::shared_ptr<Die>> dice;
    std::vector<Player> players;
};

#endif