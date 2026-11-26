#include "ComputerPlayer.h"

#include <algorithm>
#include <cstdlib>
#include <limits>
#include <random>

namespace {
std::mt19937& generator() {
    static std::mt19937 gen(std::random_device{}());
    return gen;
}

int countImmediateWins(const Board& board, char symbol) {
    int wins = 0;
    for (int column : board.getValidColumns()) {
        Board simulation = board;
        simulation.dropPiece(column, symbol);
        if (simulation.checkWin(symbol)) wins++;
    }
    return wins;
}
}

int ComputerPlayer::chooseMove(const Board& board, Difficulty difficulty,
                               char computerSymbol, char humanSymbol) {
    switch (difficulty) {
        case Difficulty::Amateur: return chooseAmateur(board);
        case Difficulty::Profi: return chooseProfi(board, computerSymbol, humanSymbol);
        case Difficulty::Legende: return chooseLegend(board, computerSymbol, humanSymbol);
    }
    return chooseAmateur(board);
}

std::string ComputerPlayer::difficultyName(Difficulty difficulty) {
    switch (difficulty) {
        case Difficulty::Amateur: return "Amateur";
        case Difficulty::Profi: return "Profi";
        case Difficulty::Legende: return "Legende";
    }
    return "Unbekannt";
}

int ComputerPlayer::chooseAmateur(const Board& board) {
    const auto valid = board.getValidColumns();
    if (valid.empty()) return -1;
    std::uniform_int_distribution<int> dist(0, static_cast<int>(valid.size()) - 1);
    return valid[dist(generator())];
}

int ComputerPlayer::chooseProfi(Board board, char computerSymbol, char humanSymbol) {
    const auto valid = board.getValidColumns();
    if (valid.empty()) return -1;

    // 1. Direkten Gewinn immer sofort ausspielen.
    for (int column : valid) {
        Board simulation = board;
        simulation.dropPiece(column, computerSymbol);
        if (simulation.checkWin(computerSymbol)) return column;
    }

    // 2. Direkten gegnerischen Gewinn blockieren.
    for (int column : valid) {
        Board simulation = board;
        simulation.dropPiece(column, humanSymbol);
        if (simulation.checkWin(humanSymbol)) return column;
    }

    // 3. Strategische Bewertung ohne vollständige Minimax-Suche.
    //    Eigene Doppeldrohungen werden belohnt, gegnerische Gabeln vermieden.
    static const int order[] = {3, 2, 4, 1, 5, 0, 6};
    int bestColumn = valid.front();
    int bestScore = std::numeric_limits<int>::min();

    for (int column : order) {
        if (board.isColumnFull(column)) continue;

        Board afterComputer = board;
        afterComputer.dropPiece(column, computerSymbol);

        int score = evaluateBoard(afterComputer, computerSymbol, humanSymbol);

        // Mitte und zentrale Spalten sind bei Vier gewinnt strategisch wertvoll.
        score += 28 - 7 * std::abs(3 - column);

        // Eine Gabel erzeugt mindestens zwei direkte Gewinnmöglichkeiten.
        int ownThreats = countImmediateWins(afterComputer, computerSymbol);
        if (ownThreats >= 2) score += 4500;
        else if (ownThreats == 1) score += 350;

        // Einen Zug vermeiden, nach dem der Gegner sofort gewinnen kann.
        int immediateHumanWins = countImmediateWins(afterComputer, humanSymbol);
        score -= immediateHumanWins * 9000;

        // Einen Halbzug vorausblicken: gegnerische Antworten simulieren.
        int worstForkPenalty = 0;
        for (int humanColumn : afterComputer.getValidColumns()) {
            Board afterHuman = afterComputer;
            afterHuman.dropPiece(humanColumn, humanSymbol);

            if (afterHuman.checkWin(humanSymbol)) {
                worstForkPenalty = std::max(worstForkPenalty, 12000);
                continue;
            }

            int humanThreats = countImmediateWins(afterHuman, humanSymbol);
            if (humanThreats >= 2)
                worstForkPenalty = std::max(worstForkPenalty, 5000);
            else if (humanThreats == 1)
                worstForkPenalty = std::max(worstForkPenalty, 500);
        }

        score -= worstForkPenalty;

        if (score > bestScore) {
            bestScore = score;
            bestColumn = column;
        }
    }

    return bestColumn;
}

int ComputerPlayer::chooseLegend(Board board, char computerSymbol, char humanSymbol) {
    const auto valid = board.getValidColumns();
    int bestColumn = valid.empty() ? -1 : valid.front();
    int bestScore = std::numeric_limits<int>::min();
    const int depth = 7;
    static const int order[] = {3, 2, 4, 1, 5, 0, 6};

    for (int column : order) {
        if (board.isColumnFull(column)) continue;

        board.dropPiece(column, computerSymbol);
        int score = board.checkWin(computerSymbol)
            ? 1000000
            : minimax(board, depth - 1,
                      std::numeric_limits<int>::min() / 2,
                      std::numeric_limits<int>::max() / 2,
                      false, computerSymbol, humanSymbol);
        board.undoPiece(column);

        if (score > bestScore) {
            bestScore = score;
            bestColumn = column;
        }
    }
    return bestColumn;
}

int ComputerPlayer::minimax(Board& board, int depth, int alpha, int beta, bool maximizing,
                            char computerSymbol, char humanSymbol) {
    if (board.checkWin(computerSymbol)) return 100000 + depth;
    if (board.checkWin(humanSymbol)) return -100000 - depth;
    if (depth == 0 || board.isFull()) return evaluateBoard(board, computerSymbol, humanSymbol);

    static const int order[] = {3, 2, 4, 1, 5, 0, 6};

    if (maximizing) {
        int value = std::numeric_limits<int>::min() / 2;
        for (int column : order) {
            if (board.isColumnFull(column)) continue;
            board.dropPiece(column, computerSymbol);
            value = std::max(value, minimax(board, depth - 1, alpha, beta, false,
                                            computerSymbol, humanSymbol));
            board.undoPiece(column);
            alpha = std::max(alpha, value);
            if (alpha >= beta) break;
        }
        return value;
    }

    int value = std::numeric_limits<int>::max() / 2;
    for (int column : order) {
        if (board.isColumnFull(column)) continue;
        board.dropPiece(column, humanSymbol);
        value = std::min(value, minimax(board, depth - 1, alpha, beta, true,
                                        computerSymbol, humanSymbol));
        board.undoPiece(column);
        beta = std::min(beta, value);
        if (alpha >= beta) break;
    }
    return value;
}

int ComputerPlayer::scoreWindow(const char window[4], char computerSymbol, char humanSymbol) {
    int computer = 0, human = 0, empty = 0;
    for (int i = 0; i < 4; i++) {
        if (window[i] == computerSymbol) computer++;
        else if (window[i] == humanSymbol) human++;
        else empty++;
    }

    int score = 0;
    if (computer == 4) score += 10000;
    else if (computer == 3 && empty == 1) score += 120;
    else if (computer == 2 && empty == 2) score += 15;

    if (human == 4) score -= 10000;
    else if (human == 3 && empty == 1) score -= 150;
    else if (human == 2 && empty == 2) score -= 12;

    return score;
}

int ComputerPlayer::evaluateBoard(const Board& board, char computerSymbol, char humanSymbol) {
    int score = 0;

    for (int row = 0; row < Board::ROWS; row++) {
        if (board.getCell(row, 3) == computerSymbol) score += 6;
        if (board.getCell(row, 3) == humanSymbol) score -= 6;
    }

    char window[4];

    for (int row = 0; row < Board::ROWS; row++)
        for (int col = 0; col <= Board::COLUMNS - 4; col++) {
            for (int i = 0; i < 4; i++) window[i] = board.getCell(row, col + i);
            score += scoreWindow(window, computerSymbol, humanSymbol);
        }

    for (int row = 0; row <= Board::ROWS - 4; row++)
        for (int col = 0; col < Board::COLUMNS; col++) {
            for (int i = 0; i < 4; i++) window[i] = board.getCell(row + i, col);
            score += scoreWindow(window, computerSymbol, humanSymbol);
        }

    for (int row = 0; row <= Board::ROWS - 4; row++)
        for (int col = 0; col <= Board::COLUMNS - 4; col++) {
            for (int i = 0; i < 4; i++) window[i] = board.getCell(row + i, col + i);
            score += scoreWindow(window, computerSymbol, humanSymbol);
        }

    for (int row = 0; row <= Board::ROWS - 4; row++)
        for (int col = 3; col < Board::COLUMNS; col++) {
            for (int i = 0; i < 4; i++) window[i] = board.getCell(row + i, col - i);
            score += scoreWindow(window, computerSymbol, humanSymbol);
        }

    return score;
}
