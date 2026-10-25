#include "Replay.h"

#include "Board.h"

#include <iostream>

void Replay::play(const SavedGame& game) {
    Board board;

    std::cout << "\nWiedergabe: "
              << game.playerOneName << " (X) gegen "
              << game.playerTwoName << " (O)\n";

    board.display();

    for (std::size_t i = 0; i < game.moves.size(); i++) {
        const Move& move = game.moves[i];

        char symbol = move.playerNumber == 1 ? 'X' : 'O';

        std::cout << "Zug " << i + 1
                  << " von " << game.moves.size()
                  << " - Spieler " << move.playerNumber
                  << ", Spalte " << move.column + 1
                  << "\n[Enter] fuer naechsten Zug";

        std::cin.get();

        board.dropPiece(move.column, symbol);
        board.display();
    }

    std::cout << "Ergebnis: " << game.result << "\n";
}
