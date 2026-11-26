#include "ComputerPlayer.h"
#include "Game.h"
#include "GameRepository.h"
#include "Player.h"
#include "Replay.h"
#include "Statistics.h"

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

        if (stream >> choice && !(stream >> rest) && choice >= min && choice <= max)
            return choice;

        std::cout << "Ungueltige Eingabe. Bitte "
                  << min << " bis " << max << " eingeben: ";
    }
}

std::string readName(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string name;
        std::getline(std::cin, name);

        if (!name.empty()) return name;
        std::cout << "Der Name darf nicht leer sein.\n";
    }
}

void showSavedGames(const std::vector<SavedGame>& games) {
    if (games.empty()) {
        std::cout << "\nKeine gespeicherten Spiele vorhanden.\n";
        return;
    }

    std::cout << "\nGespeicherte Spiele\n===================\n";
    for (std::size_t i = 0; i < games.size(); i++) {
        std::cout << i + 1 << ". "
                  << games[i].playerOneName << " gegen "
                  << games[i].playerTwoName << " | Ergebnis: "
                  << games[i].result << " | Zuege: "
                  << games[i].moves.size() << '\n';
    }
}

void saveFinishedGame(GameRepository& repository, const Game& game) {
    SavedGame savedGame{
        game.getPlayerOne().getName(),
        game.getPlayerTwo().getName(),
        game.getResult(),
        game.getMoves()
    };

    if (repository.saveGame(savedGame))
        std::cout << "Spiel wurde gespeichert.\n";
    else
        std::cout << "Fehler beim Speichern des Spiels.\n";
}

int main() {
    GameRepository repository("../data/games.dat");
    bool running = true;

    while (running) {
        std::cout << "\n=================================\n";
        std::cout << "          VIER GEWINNT           \n";
        std::cout << "=================================\n";
        std::cout << "1. Spieler gegen Spieler\n";
        std::cout << "2. Spieler gegen Computer\n";
        std::cout << "3. Gespeicherte Spiele anzeigen\n";
        std::cout << "4. Spiel wiederholen\n";
        std::cout << "5. Spielerstatistik\n";
        std::cout << "6. Programm beenden\n";
        std::cout << "Auswahl: ";

        int choice = readChoice(1, 6);

        switch (choice) {
            case 1: {
                std::string p1 = readName("Name Spieler 1: ");
                std::string p2 = readName("Name Spieler 2: ");

                Game game(Player(p1, 'X'), Player(p2, 'O'));
                game.start();

                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');

                saveFinishedGame(repository, game);
                break;
            }

            case 2: {
                std::string name = readName("Dein Name: ");
                std::cout << "Schwierigkeit: 1 = Amateur, 2 = Profi, 3 = Legende\n"
                          << "Auswahl: ";

                Difficulty difficulty =
                    static_cast<Difficulty>(readChoice(1, 3));

                std::string computerName =
                    "Computer (" +
                    ComputerPlayer::difficultyName(difficulty) + ")";

                Game game(
                    Player(name, 'X'),
                    Player(computerName, 'O'),
                    true,
                    difficulty
                );

                game.start();

                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');

                saveFinishedGame(repository, game);
                break;
            }

            case 3:
                showSavedGames(repository.loadGames());
                break;

            case 4: {
                auto games = repository.loadGames();

                if (games.empty()) {
                    std::cout << "\nKeine gespeicherten Spiele vorhanden.\n";
                    break;
                }

                showSavedGames(games);
                std::cout << "Welches Spiel soll wiederholt werden? ";

                int number =
                    readChoice(1, static_cast<int>(games.size()));

                Replay::play(games[number - 1]);
                break;
            }

            case 5:
                Statistics::display(repository.loadGames());
                break;

            case 6:
                running = false;
                std::cout << "Programm beendet.\n";
                break;
        }
    }

    return 0;
}
