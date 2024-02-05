#include "Backtrack.h"
#include <sys/time.h>


// Backtrack class constructor
// parameter hints : beginning Sudoku puzzle hints for the algorithm to solve
Backtrack::Backtrack(int* hints) {
    // Initialize instance variables
    this->initial = *(new SudokuPuzzle());
    this->current = *(new SudokuPuzzle());
    this->initial.installHints(hints);
    this->current.installHints(hints);
    // Solve the puzzle
    solvePuzzle();
}

// The solve function takes in a row and a column number and fills in the Cell at row r, column c with a number
// If this number is found to be invalid, the algorithm will backtrack and try the next number after
bool Backtrack::solve(int r, int c) {
    // If the final Cell has been passed on, return true, a solution has been found
    if(r == 9) {
        return true;
    // If the final Cell in a column has been passed on, move on to the next row
    } else if(c == 9) {
        return solve(r + 1, 0);
    // If the current Cell has already been filled in, move on to the next Cell
    } else if(this->current.getCell(r, c)->getAnswer() < 10 && this->current.getCell(r, c)->getAnswer() > 0) {
        return solve(r, c + 1);
    // Otherwise
    } else {
        for(int i = 1; i < 10; i++) {
            // Fill in with the first valid number possible
            if(this->current.isValid(r, c, i)) {
                this->current.getCell(r, c)->setAnswer(i);
                if(solve(r, c + 1)) {
                    return true;
                }
                this->current.getCell(r, c)->setAnswer(0);
            }
        }
        return false;
    }
}
// Find a solution for the inputted Sudoku puzzle
void Backtrack::solvePuzzle() {
    // Get the current time which will be the time the algorithm first began solving
    struct timeval begin, end;
    gettimeofday(&begin, 0);
    // Solve the puzzle
    solve(0, 01);
    this->solution = this->current;
    // Get the current time which will be the time the algorithm finished solving
    gettimeofday(&end, 0);
    // Calculate the time it took to solve the puzzle
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    this->timeElapsed = seconds + microseconds * (1e-6);
}
// Getter function for the initial state of the puzzle
SudokuPuzzle Backtrack::getInitial() { return this->initial; }
// Getter function for the current state of the puzzle
SudokuPuzzle Backtrack::getCurrent() { return this->current; }
// Getter function for the solution state of the puzzle
SudokuPuzzle Backtrack::getSolution() { return this->solution; }
// Getter function for the total time elapsed to arrive at a solution
double Backtrack::getTimeElapsed() { return this->timeElapsed; }
