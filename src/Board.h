#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board {
public:
    static const int ROWS = 6;
    static const int COLUMNS = 7;

    Board();

    void reset();
    void display() const;
    bool dropPiece(int column, char symbol);
    bool dropPieceAnimated(int column, char symbol, int delayMs = 65);
    bool undoPiece(int column);
    bool isColumnFull(int column) const;
    bool isFull() const;
    bool checkWin(char symbol) const;
    char getCell(int row, int column) const;
    std::vector<int> getValidColumns() const;

private:
    char grid[ROWS][COLUMNS];
    void displayInternal(int fallingRow, int fallingColumn, char fallingSymbol) const;
};

#endif
