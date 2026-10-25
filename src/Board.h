#ifndef BOARD_H
#define BOARD_H

class Board {
private:
    static const int ROWS = 6;
    static const int COLUMNS = 7;

    char grid[ROWS][COLUMNS];

public:
    Board();

    void reset();
    void display() const;
    bool dropPiece(int column, char symbol);
    bool isColumnFull(int column) const;
    bool isFull() const;
    bool checkWin(char symbol) const;
};

#endif
