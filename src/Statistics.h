#ifndef STATISTICS_H
#define STATISTICS_H

#include "GameRepository.h"

#include <map>
#include <string>
#include <vector>

struct PlayerStats {
    int games = 0;
    int wins = 0;
    int losses = 0;
    int draws = 0;
};

class Statistics {
public:
    static std::map<std::string, PlayerStats> calculate(const std::vector<SavedGame>& games);
    static void display(const std::vector<SavedGame>& games);
};

#endif
