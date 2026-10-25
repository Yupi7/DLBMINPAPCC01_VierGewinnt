#include "GameRepository.h"

#include <fstream>
#include <iomanip>

GameRepository::GameRepository(const std::string& filePath)
    : filePath(filePath) {
}

bool GameRepository::saveGame(const SavedGame& game) const {
    std::ofstream file(filePath, std::ios::app);

    if (!file.is_open()) {
        return false;
    }

    file << std::quoted(game.playerOneName) << '\n';
    file << std::quoted(game.playerTwoName) << '\n';
    file << std::quoted(game.result) << '\n';
    file << game.moves.size() << '\n';

    for (const Move& move : game.moves) {
        file << move.playerNumber << ' '
             << move.column << '\n';
    }

    return true;
}

std::vector<SavedGame> GameRepository::loadGames() const {
    std::vector<SavedGame> games;
    std::ifstream file(filePath);

    if (!file.is_open()) {
        return games;
    }

    while (true) {
        SavedGame game;
        std::size_t moveCount;

        if (!(file >> std::quoted(game.playerOneName))) {
            break;
        }

        if (!(file >> std::quoted(game.playerTwoName))) {
            break;
        }

        if (!(file >> std::quoted(game.result))) {
            break;
        }

        if (!(file >> moveCount)) {
            break;
        }

        for (std::size_t i = 0; i < moveCount; i++) {
            Move move{};

            file >> move.playerNumber >> move.column;
            move.row = -1;

            game.moves.push_back(move);
        }

        games.push_back(game);
    }

    return games;
}
