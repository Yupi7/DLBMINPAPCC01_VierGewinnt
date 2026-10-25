#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include "Move.h"

#include <vector>

class Game {
private:
    Board board;
    Player playerOne;
    Player playerTwo;
    std::vector<Move> moves;

public:
    Game(const Player& playerOne, const Player& playerTwo);

    void start();
};

#endif
