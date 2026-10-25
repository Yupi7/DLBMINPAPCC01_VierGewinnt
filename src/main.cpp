#include "Game.h"
#include "GameRepository.h"
#include "Player.h"
#include "Replay.h"

#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

int readChoice(int min, int max) {
    while (true) {
        std::string input;
        std::getline(std::cin, input);

        std::stringstream stream(input);
        int choice;
        char rest;

        if (stream >> choice &&
            !(stream >> rest) &&
            choice >= min &&
            choice <= max) {
            return choice;
        }

        std::cout << "Ungueltige Eingabe. Bitte "
                  << min << " bis " << max << " eingeben: ";
    }
}

std::string readName(const std::string& prompt) {
    while (true) {
        std::cout << prompt;

        std::string name;
        std::getline(std::cin, name);

        if (!name.empty()) {
            return name;
        }

        std::cout << "Der Name darf nicht leer sein.\n";
    }
}

void showSavedGames(const std::vector<SavedGame>& games) {
    if (games.empty()) {
        std::cout << "\nKeine gespeicherten Spiele vorhanden.\n";
        return;
    }

    std::cout << "\nGespeicherte Spiele\n";
    std::cout << "===================\n";

    for (std::size_t i = 0; i < games.size(); i++) {
        std::cout << i + 1 << ". "
                  << games[i].playerOneName
                  << " gegen "
                  << games[i].playerTwoName
                  << " | Ergebnis: "
                  << games[i].result
                  << " | Zuege: "
                  << games[i].moves.size()
                  << '\n';
    }
}

int main() {
    GameRepository repository("../data/games.dat");

    bool running = true;

    while (running) {
        std::cout << "\n=========================\n";
        std::cout << "       VIER GEWINNT      \n";
        std::cout << "=========================\n";
        std::cout << "1. Neues Spiel\n";
        std::cout << "2. Gespeicherte Spiele anzeigen\n";
        std::cout << "3. Spiel wiederholen\n";
        std::cout << "4. Programm beenden\n";
        std::cout << "Auswahl: ";

        int choice = readChoice(1, 4);

        switch (choice) {
            case 1: {
                std::string playerOneName =
                    readName("Name Spieler 1: ");

                std::string playerTwoName =
                    readName("Name Spieler 2: ");

                Player playerOne(playerOneName, 'X');
                Player playerTwo(playerTwoName, 'O');

                Game game(playerOne, playerTwo);
                game.start();

                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(),
                    '\n'
                );

                SavedGame savedGame{
                    game.getPlayerOne().getName(),
                    game.getPlayerTwo().getName(),
                    game.getResult(),
                    game.getMoves()
                };

                if (repository.saveGame(savedGame)) {
                    std::cout << "Spiel wurde gespeichert.\n";
                }
                else {
                    std::cout << "Fehler beim Speichern des Spiels.\n";
                }

                break;
            }

            case 2: {
                std::vector<SavedGame> games =
                    repository.loadGames();

                showSavedGames(games);
                break;
            }

            case 3: {
                std::vector<SavedGame> games =
                    repository.loadGames();

                if (games.empty()) {
                    std::cout
                        << "\nKeine gespeicherten Spiele vorhanden.\n";
                    break;
                }

                showSavedGames(games);

                std::cout << "Welches Spiel soll wiederholt werden? ";

                int gameNumber =
                    readChoice(1, static_cast<int>(games.size()));

                Replay::play(games[gameNumber - 1]);
                break;
            }

            case 4:
                running = false;
                std::cout << "Programm beendet.\n";
                break;
        }
    }

    return 0;
}
