#include "Board.h"

#include <chrono>
#include <iostream>
#include <thread>

namespace {
constexpr const char* RESET = "\033[0m";
constexpr const char* RED = "\033[1;31m";
constexpr const char* YELLOW = "\033[1;33m";
constexpr const char* BLUE = "\033[1;34m";
constexpr const char* CYAN = "\033[1;36m";

std::string coloredCell(char symbol) {
    if (symbol == 'X') return std::string(RED) + " X " + RESET;
    if (symbol == 'O') return std::string(YELLOW) + " O " + RESET;
    return "   ";
}
}

Board::Board() { reset(); }

void Board::reset() {
    for (int row = 0; row < ROWS; row++)
        for (int column = 0; column < COLUMNS; column++)
            grid[row][column] = ' ';
}

void Board::display() const {
    displayInternal(-1, -1, ' ');
}

void Board::displayInternal(int fallingRow, int fallingColumn, char fallingSymbol) const {
    std::cout << "\n" << BLUE << "╔═══╦═══╦═══╦═══╦═══╦═══╦═══╗" << RESET << "\n";

    for (int row = 0; row < ROWS; row++) {
        std::cout << BLUE << "║" << RESET;
        for (int column = 0; column < COLUMNS; column++) {
            char symbol = grid[row][column];
            if (row == fallingRow && column == fallingColumn) symbol = fallingSymbol;
            std::cout << coloredCell(symbol) << BLUE << "║" << RESET;
        }
        std::cout << "\n";
        if (row < ROWS - 1)
            std::cout << BLUE << "╠═══╬═══╬═══╬═══╬═══╬═══╬═══╣" << RESET << "\n";
    }

    std::cout << BLUE << "╚═══╩═══╩═══╩═══╩═══╩═══╩═══╝" << RESET << "\n";
    std::cout << CYAN << "  1   2   3   4   5   6   7" << RESET << "\n\n";
}

bool Board::isColumnFull(int column) const {
    if (column < 0 || column >= COLUMNS) return true;
    return grid[0][column] != ' ';
}

bool Board::dropPiece(int column, char symbol) {
    if (column < 0 || column >= COLUMNS || isColumnFull(column)) return false;

    for (int row = ROWS - 1; row >= 0; row--) {
        if (grid[row][column] == ' ') {
            grid[row][column] = symbol;
            return true;
        }
    }
    return false;
}

bool Board::dropPieceAnimated(int column, char symbol, int delayMs) {
    if (column < 0 || column >= COLUMNS || isColumnFull(column)) return false;

    int targetRow = -1;
    for (int row = ROWS - 1; row >= 0; row--) {
        if (grid[row][column] == ' ') {
            targetRow = row;
            break;
        }
    }

    for (int row = 0; row <= targetRow; row++) {
        std::cout << "\033[2J\033[H";
        displayInternal(row, column, symbol);
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }

    grid[targetRow][column] = symbol;
    std::cout << '\a' << std::flush;
    return true;
}

bool Board::undoPiece(int column) {
    if (column < 0 || column >= COLUMNS) return false;
    for (int row = 0; row < ROWS; row++) {
        if (grid[row][column] != ' ') {
            grid[row][column] = ' ';
            return true;
        }
    }
    return false;
}

bool Board::isFull() const { return getValidColumns().empty(); }

bool Board::checkWin(char symbol) const {
    for (int row = 0; row < ROWS; row++)
        for (int column = 0; column <= COLUMNS - 4; column++)
            if (grid[row][column] == symbol &&
                grid[row][column + 1] == symbol &&
                grid[row][column + 2] == symbol &&
                grid[row][column + 3] == symbol) return true;

    for (int row = 0; row <= ROWS - 4; row++)
        for (int column = 0; column < COLUMNS; column++)
            if (grid[row][column] == symbol &&
                grid[row + 1][column] == symbol &&
                grid[row + 2][column] == symbol &&
                grid[row + 3][column] == symbol) return true;

    for (int row = 0; row <= ROWS - 4; row++)
        for (int column = 0; column <= COLUMNS - 4; column++)
            if (grid[row][column] == symbol &&
                grid[row + 1][column + 1] == symbol &&
                grid[row + 2][column + 2] == symbol &&
                grid[row + 3][column + 3] == symbol) return true;

    for (int row = 0; row <= ROWS - 4; row++)
        for (int column = 3; column < COLUMNS; column++)
            if (grid[row][column] == symbol &&
                grid[row + 1][column - 1] == symbol &&
                grid[row + 2][column - 2] == symbol &&
                grid[row + 3][column - 3] == symbol) return true;

    return false;
}

char Board::getCell(int row, int column) const {
    if (row < 0 || row >= ROWS || column < 0 || column >= COLUMNS) return '\0';
    return grid[row][column];
}

std::vector<int> Board::getValidColumns() const {
    std::vector<int> columns;
    for (int column = 0; column < COLUMNS; column++)
        if (!isColumnFull(column)) columns.push_back(column);
    return columns;
}
