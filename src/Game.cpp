#include "Game.h"

#include <chrono>
#include <iostream>
#include <limits>
#include <thread>

Game::Game(const Player& playerOne, const Player& playerTwo,
           bool playerTwoIsComputer, Difficulty difficulty)
    : playerOne(playerOne), playerTwo(playerTwo),
      playerTwoIsComputer(playerTwoIsComputer), difficulty(difficulty) {
}

void Game::start() {
    int currentPlayer = 1;
    bool gameRunning = true;

    while (gameRunning) {
        board.display();
        Player& player = currentPlayer == 1 ? playerOne : playerTwo;
        int column = -1;

        if (playerTwoIsComputer && currentPlayer == 2) {
            std::cout << player.getName() << " denkt nach...\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(450));
            column = ComputerPlayer::chooseMove(
                board, difficulty, playerTwo.getSymbol(), playerOne.getSymbol());
            std::cout << player.getName() << " waehlt Spalte " << column + 1 << ".\n";
        } else {
            std::cout << player.getName() << " (" << player.getSymbol()
                      << "), waehle eine Spalte (1-7): ";

            int inputColumn;
            if (!(std::cin >> inputColumn)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ungueltige Eingabe. Bitte eine Zahl eingeben.\n";
                continue;
            }

            if (inputColumn < 1 || inputColumn > 7) {
                std::cout << "Bitte eine Spalte zwischen 1 und 7 waehlen.\n";
                continue;
            }

            column = inputColumn - 1;
        }

        if (column < 0 || !board.dropPieceAnimated(column, player.getSymbol())) {
            if (playerTwoIsComputer && currentPlayer == 2) {
                std::cout << "Der Computer konnte keinen gueltigen Zug ausfuehren.\n";
                break;
            }
            std::cout << "Diese Spalte ist bereits voll.\n";
            continue;
        }

        moves.push_back({currentPlayer, -1, column});

        if (board.checkWin(player.getSymbol())) {
            board.display();
            std::cout << player.getName() << " hat gewonnen!\n";
            result = player.getName();
            gameRunning = false;
        } else if (board.isFull()) {
            board.display();
            std::cout << "Das Spiel endet unentschieden.\n";
            result = "Unentschieden";
            gameRunning = false;
        } else {
            currentPlayer = currentPlayer == 1 ? 2 : 1;
        }
    }
}

const std::vector<Move>& Game::getMoves() const { return moves; }
const Player& Game::getPlayerOne() const { return playerOne; }
const Player& Game::getPlayerTwo() const { return playerTwo; }
std::string Game::getResult() const { return result; }
