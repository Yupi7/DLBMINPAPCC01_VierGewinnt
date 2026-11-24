#include "Board.h"
#include "ComputerPlayer.h"
#include "GameRepository.h"
#include "Statistics.h"

#include <cassert>
#include <iostream>

void testHorizontalWin() {
    Board b;
    for (int c = 0; c < 4; c++) b.dropPiece(c, 'X');
    assert(b.checkWin('X'));
}

void testVerticalWin() {
    Board b;
    for (int i = 0; i < 4; i++) b.dropPiece(0, 'O');
    assert(b.checkWin('O'));
}

void testDiagonalWins() {
    Board downRight;
    downRight.dropPiece(0, 'X');
    downRight.dropPiece(1, 'O'); downRight.dropPiece(1, 'X');
    downRight.dropPiece(2, 'O'); downRight.dropPiece(2, 'O'); downRight.dropPiece(2, 'X');
    downRight.dropPiece(3, 'O'); downRight.dropPiece(3, 'O'); downRight.dropPiece(3, 'O'); downRight.dropPiece(3, 'X');
    assert(downRight.checkWin('X'));

    Board downLeft;
    downLeft.dropPiece(6, 'X');
    downLeft.dropPiece(5, 'O'); downLeft.dropPiece(5, 'X');
    downLeft.dropPiece(4, 'O'); downLeft.dropPiece(4, 'O'); downLeft.dropPiece(4, 'X');
    downLeft.dropPiece(3, 'O'); downLeft.dropPiece(3, 'O'); downLeft.dropPiece(3, 'O'); downLeft.dropPiece(3, 'X');
    assert(downLeft.checkWin('X'));
}

void testFullColumn() {
    Board b;
    for (int i = 0; i < Board::ROWS; i++)
        assert(b.dropPiece(0, i % 2 ? 'O' : 'X'));

    assert(b.isColumnFull(0));
    assert(!b.dropPiece(0, 'X'));
}

void testUndo() {
    Board b;
    b.dropPiece(3, 'X');
    assert(b.undoPiece(3));
    assert(b.getCell(Board::ROWS - 1, 3) == ' ');
}

void testProfiPrefersCenter() {
    Board board;
    assert(ComputerPlayer::chooseMove(
        board, Difficulty::Profi, 'O', 'X') == 3);
}

void testProfiWinsAndBlocks() {
    Board win;
    win.dropPiece(0, 'O');
    win.dropPiece(1, 'O');
    win.dropPiece(2, 'O');

    assert(ComputerPlayer::chooseMove(
        win, Difficulty::Profi, 'O', 'X') == 3);

    Board block;
    block.dropPiece(0, 'X');
    block.dropPiece(1, 'X');
    block.dropPiece(2, 'X');

    assert(ComputerPlayer::chooseMove(
        block, Difficulty::Profi, 'O', 'X') == 3);
}

void testLegendWinsAndBlocks() {
    Board win;
    win.dropPiece(0, 'O');
    win.dropPiece(1, 'O');
    win.dropPiece(2, 'O');

    assert(ComputerPlayer::chooseMove(
        win, Difficulty::Legende, 'O', 'X') == 3);

    Board block;
    block.dropPiece(0, 'X');
    block.dropPiece(1, 'X');
    block.dropPiece(2, 'X');

    assert(ComputerPlayer::chooseMove(
        block, Difficulty::Legende, 'O', 'X') == 3);
}

void testStatistics() {
    std::vector<SavedGame> games = {
        {"Anna", "Ben", "Anna", {}},
        {"Anna", "Ben", "Unentschieden", {}},
        {"Anna", "Ben", "Ben", {}}
    };

    auto s = Statistics::calculate(games);

    assert(s["Anna"].games == 3 &&
           s["Anna"].wins == 1 &&
           s["Anna"].losses == 1 &&
           s["Anna"].draws == 1);

    assert(s["Ben"].games == 3 &&
           s["Ben"].wins == 1 &&
           s["Ben"].losses == 1 &&
           s["Ben"].draws == 1);
}

int main() {
    testHorizontalWin();
    testVerticalWin();
    testDiagonalWins();
    testFullColumn();
    testUndo();
    testProfiPrefersCenter();
    testProfiWinsAndBlocks();
    testLegendWinsAndBlocks();
    testStatistics();

    std::cout << "Alle automatisierten Tests erfolgreich.\n";
    return 0;
}
