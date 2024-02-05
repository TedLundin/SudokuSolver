#pragma once
#include "SudokuPuzzle.h"
#include <sys/time.h>


class Constraint {
    SudokuPuzzle initial;
    SudokuPuzzle current;
    SudokuPuzzle solution;
    double timeElapsed;

    public:
        Constraint(int* hints);

        void solvePuzzle();
        SudokuPuzzle getInitial();
        SudokuPuzzle getCurrent();
        SudokuPuzzle getSolution();
        double getTimeElapsed();
        bool solve(int r, int c);
};
