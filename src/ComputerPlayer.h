#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "Board.h"
#include <string>

enum class Difficulty {
    Amateur = 1,
    Profi = 2,
    Legende = 3
};

class ComputerPlayer {
public:
    static int chooseMove(const Board& board, Difficulty difficulty, char computerSymbol, char humanSymbol);
    static std::string difficultyName(Difficulty difficulty);

private:
    static int chooseAmateur(const Board& board);
    static int chooseProfi(Board board, char computerSymbol, char humanSymbol);
    static int chooseLegend(Board board, char computerSymbol, char humanSymbol);
    static int minimax(Board& board, int depth, int alpha, int beta, bool maximizing,
                       char computerSymbol, char humanSymbol);
    static int evaluateBoard(const Board& board, char computerSymbol, char humanSymbol);
    static int scoreWindow(const char window[4], char computerSymbol, char humanSymbol);
};

#endif
