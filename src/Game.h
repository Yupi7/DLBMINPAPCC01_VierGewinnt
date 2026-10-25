#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include "Move.h"

#include <string>
#include <vector>

class Game {
private:
    Board board;
    Player playerOne;
    Player playerTwo;
    std::vector<Move> moves;
    std::string result;

public:
    Game(const Player& playerOne, const Player& playerTwo);

    void start();

    const std::vector<Move>& getMoves() const;
    const Player& getPlayerOne() const;
    const Player& getPlayerTwo() const;
    std::string getResult() const;
};

#endif
