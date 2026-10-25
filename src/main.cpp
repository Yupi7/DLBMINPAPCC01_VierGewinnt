#include "Game.h"
#include "Player.h"

#include <iostream>
#include <string>

int main() {
    std::string playerOneName;
    std::string playerTwoName;

    std::cout << "=========================\n";
    std::cout << "       VIER GEWINNT      \n";
    std::cout << "=========================\n\n";

    std::cout << "Name Spieler 1: ";
    std::getline(std::cin, playerOneName);

    std::cout << "Name Spieler 2: ";
    std::getline(std::cin, playerTwoName);

    Player playerOne(playerOneName, 'X');
    Player playerTwo(playerTwoName, 'O');

    Game game(playerOne, playerTwo);
    game.start();

    return 0;
}
