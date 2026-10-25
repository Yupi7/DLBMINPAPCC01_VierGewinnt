#include "Game.h"

#include <iostream>
#include <limits>

Game::Game(const Player& playerOne, const Player& playerTwo)
    : playerOne(playerOne), playerTwo(playerTwo) {
}

void Game::start() {
    int currentPlayer = 1;
    bool gameRunning = true;

    while (gameRunning) {
        board.display();

        Player& player = currentPlayer == 1 ? playerOne : playerTwo;

        std::cout << player.getName()
                  << " (" << player.getSymbol()
                  << "), waehle eine Spalte (1-7): ";

        int column;

        if (!(std::cin >> column)) {
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            std::cout << "Ungueltige Eingabe. Bitte eine Zahl eingeben.\n";
            continue;
        }

        if (column < 1 || column > 7) {
            std::cout << "Bitte eine Spalte zwischen 1 und 7 waehlen.\n";
            continue;
        }

        column--;

        if (!board.dropPiece(column, player.getSymbol())) {
            std::cout << "Diese Spalte ist bereits voll.\n";
            continue;
        }

        moves.push_back({currentPlayer, -1, column});

        if (board.checkWin(player.getSymbol())) {
            board.display();
            std::cout << player.getName() << " hat gewonnen!\n";
            gameRunning = false;
        }
        else if (board.isFull()) {
            board.display();
            std::cout << "Das Spiel endet unentschieden.\n";
            gameRunning = false;
        }
        else {
            currentPlayer = currentPlayer == 1 ? 2 : 1;
        }
    }
}
