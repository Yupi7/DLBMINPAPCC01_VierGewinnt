#include "Board.h"
#include <iostream>

Board::Board() {
    reset();
}

void Board::reset() {
    for (int row = 0; row < ROWS; row++) {
        for (int column = 0; column < COLUMNS; column++) {
            grid[row][column] = ' ';
        }
    }
}

void Board::display() const {
    std::cout << "\n";

    for (int row = 0; row < ROWS; row++) {
        std::cout << "|";

        for (int column = 0; column < COLUMNS; column++) {
            std::cout << " " << grid[row][column] << " |";
        }

        std::cout << "\n";
    }

    std::cout << "+---+---+---+---+---+---+---+\n";
    std::cout << "  1   2   3   4   5   6   7\n\n";
}

bool Board::isColumnFull(int column) const {
    if (column < 0 || column >= COLUMNS) {
        return true;
    }

    return grid[0][column] != ' ';
}

bool Board::dropPiece(int column, char symbol) {
    if (column < 0 || column >= COLUMNS || isColumnFull(column)) {
        return false;
    }

    for (int row = ROWS - 1; row >= 0; row--) {
        if (grid[row][column] == ' ') {
            grid[row][column] = symbol;
            return true;
        }
    }

    return false;
}

bool Board::isFull() const {
    for (int column = 0; column < COLUMNS; column++) {
        if (!isColumnFull(column)) {
            return false;
        }
    }

    return true;
}

bool Board::checkWin(char symbol) const {
    for (int row = 0; row < ROWS; row++) {
        for (int column = 0; column <= COLUMNS - 4; column++) {
            if (grid[row][column] == symbol &&
                grid[row][column + 1] == symbol &&
                grid[row][column + 2] == symbol &&
                grid[row][column + 3] == symbol) {
                return true;
            }
        }
    }

    for (int row = 0; row <= ROWS - 4; row++) {
        for (int column = 0; column < COLUMNS; column++) {
            if (grid[row][column] == symbol &&
                grid[row + 1][column] == symbol &&
                grid[row + 2][column] == symbol &&
                grid[row + 3][column] == symbol) {
                return true;
            }
        }
    }

    for (int row = 0; row <= ROWS - 4; row++) {
        for (int column = 0; column <= COLUMNS - 4; column++) {
            if (grid[row][column] == symbol &&
                grid[row + 1][column + 1] == symbol &&
                grid[row + 2][column + 2] == symbol &&
                grid[row + 3][column + 3] == symbol) {
                return true;
            }
        }
    }

    for (int row = 0; row <= ROWS - 4; row++) {
        for (int column = 3; column < COLUMNS; column++) {
            if (grid[row][column] == symbol &&
                grid[row + 1][column - 1] == symbol &&
                grid[row + 2][column - 2] == symbol &&
                grid[row + 3][column - 3] == symbol) {
                return true;
            }
        }
    }

    return false;
}
