#pragma once
#include "Cell.h"


class SudokuPuzzle {
    public:
        SudokuPuzzle();

        void installHints(int hintList[81]);
        Cell* getBoard();
        Cell* getCell(int r, int c);
        Cell* getCell(int n);
        void setAnswer(int r, int c, int num);
        void setAnswer(int n, int num);
        void printBoard();
        bool isValid(int r, int c, int n);
    private:
        Cell board[9][9];
};
