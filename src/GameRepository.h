#ifndef GAMEREPOSITORY_H
#define GAMEREPOSITORY_H

#include "Move.h"

#include <string>
#include <vector>

struct SavedGame {
    std::string playerOneName;
    std::string playerTwoName;
    std::string result;
    std::vector<Move> moves;
};

class GameRepository {
private:
    std::string filePath;

public:
    explicit GameRepository(const std::string& filePath);

    bool saveGame(const SavedGame& game) const;
    std::vector<SavedGame> loadGames() const;
};

#endif
