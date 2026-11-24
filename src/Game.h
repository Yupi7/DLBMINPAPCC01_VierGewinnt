#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "ComputerPlayer.h"
#include "Move.h"
#include "Player.h"

#include <string>
#include <vector>

class Game {
public:
    Game(const Player& playerOne, const Player& playerTwo,
         bool playerTwoIsComputer = false,
         Difficulty difficulty = Difficulty::Amateur);

    void start();

    const std::vector<Move>& getMoves() const;
    const Player& getPlayerOne() const;
    const Player& getPlayerTwo() const;
    std::string getResult() const;

private:
    Board board;
    Player playerOne;
    Player playerTwo;
    std::vector<Move> moves;
    std::string result;
    bool playerTwoIsComputer;
    Difficulty difficulty;
};

#endif
