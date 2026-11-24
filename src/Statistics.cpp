#include "Statistics.h"

#include <iomanip>
#include <iostream>

std::map<std::string, PlayerStats> Statistics::calculate(const std::vector<SavedGame>& games) {
    std::map<std::string, PlayerStats> stats;

    for (const SavedGame& game : games) {
        PlayerStats& p1 = stats[game.playerOneName];
        PlayerStats& p2 = stats[game.playerTwoName];
        p1.games++;
        p2.games++;

        if (game.result == "Unentschieden") {
            p1.draws++;
            p2.draws++;
        } else if (game.result == game.playerOneName) {
            p1.wins++;
            p2.losses++;
        } else if (game.result == game.playerTwoName) {
            p2.wins++;
            p1.losses++;
        }
    }

    return stats;
}

void Statistics::display(const std::vector<SavedGame>& games) {
    const auto stats = calculate(games);

    if (stats.empty()) {
        std::cout << "\nNoch keine Statistik vorhanden.\n";
        return;
    }

    std::cout << "\nSPIELERSTATISTIK\n";
    std::cout << "=================================================================\n";
    std::cout << std::left << std::setw(24) << "Spieler"
              << std::right << std::setw(8) << "Spiele"
              << std::setw(8) << "Siege"
              << std::setw(10) << "Niederl."
              << std::setw(10) << "Remis" << '\n';
    std::cout << "-----------------------------------------------------------------\n";

    for (const auto& [name, value] : stats) {
        std::cout << std::left << std::setw(24) << name
                  << std::right << std::setw(8) << value.games
                  << std::setw(8) << value.wins
                  << std::setw(10) << value.losses
                  << std::setw(10) << value.draws << '\n';
    }
}
