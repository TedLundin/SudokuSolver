#include "Constraint.h"
#include <sys/time.h>


// Constraint class constructor
// parameter hints : beginning Sudoku puzzle hints for the algorithm to solve
Constraint::Constraint(int* hints) {
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
bool Constraint::solve(int r, int c) {
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
void Constraint::solvePuzzle() {
    // Get the current time which will be the time the algorithm first began solving
    struct timeval begin, end;
    gettimeofday(&begin, 0);
    // While the puzzle is not solved
    int changes = 1;
    while(changes != 0) {
        changes = 0;
        // Iterate through each Cell and check to see if they only have one single answer they can be
        for(int i = 0; i < 81; i++) {
            if(this->current.getCell(i)->getAnswer() >= 10 || this->current.getCell(i)->getAnswer() <= 0) {
                int numTrues = 0;
                int index = -1;
                // Check to see how many trues there are in the notes of the Cell
                for(int n = 0; n < 9; n++) {
                    if(this->current.getCell(i)->getNotes()[n]) {
                        numTrues++;
                        index = n;
                    }
                }
                // If there is a singular true in the notes, the answer must be that number
                if(numTrues == 1) {
                    this->current.setAnswer(i, index + 1);
                    changes++;
                }
            }
        }
        // If there is a number that only appears once in a row, column, or block then the Cell containing that number must have that answer
        for(int i = 0; i < 9; i++) {
            int rowNumCounts[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
            int colNumCounts[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
            int blockNumCounts[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
            for(int j = 0; j < 9; j++) {
                // Count the amount of times each Cell in the given row has each number as one of its possible answers
                if(this->current.getCell(i, j)->getAnswer() >= 10 || this->current.getCell(i, j)->getAnswer() <= 0) {
                    for(int n = 0; n < 9; n++) {
                        if(this->current.getCell(i, j)->getNotes()[n]) {
                            rowNumCounts[n]++;
                        }
                    }
                }
                // Count the amount of times each Cell in the given column has each number as one of its possible answers
                if(this->current.getCell(j, i)->getAnswer() >= 10 || this->current.getCell(j, i)->getAnswer() <= 0) {
                    for(int n = 0; n < 9; n++) {
                        if(this->current.getCell(j, i)->getNotes()[n]) {
                            colNumCounts[n]++;
                        }
                    }
                }
                // Count the amount of times each Cell in the given block has each number as one of its possible answers
                if(this->current.getCell(((i / 3) * 3) + (j / 3), ((i % 3) * 3) + (j % 3))->getAnswer() >= 10 || 
                  this->current.getCell(((i / 3) * 3) + (j / 3), ((i % 3) * 3) + (j % 3))->getAnswer() <= 0) {
                    for(int n = 0; n < 9; n++) {
                        if(this->current.getCell(((i / 3) * 3) + (j / 3), ((i % 3) * 3) + (j % 3))->getNotes()[n]) {
                            blockNumCounts[n]++;
                        }
                    }
                }
            }
            for(int j = 0; j < 9; j++) {
                // If only one instance of any given answer appears in the row's notes, then the Cell containing that note must have that answer
                if(this->current.getCell(i, j)->getAnswer() >= 10 || this->current.getCell(i, j)->getAnswer() <= 0) {
                    for(int n = 0; n < 9; n++) {
                        if(this->current.getCell(i, j)->getNotes()[n] && rowNumCounts[n] == 1) {
                            this->current.setAnswer(i, j, n + 1);
                            changes++;
                            break;
                        }
                    }
                }
                // If only one instance of any given answer appears in the column's notes, then the Cell containing that note must have that answer
                if(this->current.getCell(j, i)->getAnswer() >= 10 || this->current.getCell(j, i)->getAnswer() <= 0) {
                    for(int n = 0; n < 9; n++) {
                        if(this->current.getCell(j, i)->getNotes()[n] && colNumCounts[n] == 1) {
                            this->current.setAnswer(j, i, n + 1);
                            changes++;
                            break;
                        }
                    }
                }
                // If only one instance of any given answer appears in the block's notes, then the Cell containing that note must have that answer
                if(this->current.getCell(((i / 3) * 3) + (j / 3), ((i % 3) * 3) + (j % 3))->getAnswer() >= 10 || 
                  this->current.getCell(((i / 3) * 3) + (j / 3), ((i % 3) * 3) + (j % 3))->getAnswer() <= 0) {
                    for(int n = 0; n < 9; n++) {
                        if(this->current.getCell(((i / 3) * 3) + (j / 3), ((i % 3) * 3) + (j % 3))->getNotes()[n] && blockNumCounts[n] == 1) {
                            this->current.setAnswer(((i / 3) * 3) + (j / 3), ((i % 3) * 3) + (j % 3), n + 1);
                            changes++;
                            break;
                        }
                    }
                }
            }
        }
    }
    // In more advanced puzzles, this level of constraint propagation will likely not be able to finish the puzzle completely
    // If this is the case, use the backtracking algorithm to fill in the remaining empty Cell's of the puzzle
    solve(0, 0);
    this->solution = this->current;
    // Get the current time which will be the time the algorithm finished solving
    gettimeofday(&end, 0);
    // Calculate the time it took to solve the puzzle
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    this->timeElapsed = seconds + microseconds * (1e-6);
}
// Getter function for the initial state of the puzzle
SudokuPuzzle Constraint::getInitial() { return this->initial; }
// Getter function for the current state of the puzzle
SudokuPuzzle Constraint::getCurrent() { return this->current; }
// Getter function for the solution state of the puzzle
SudokuPuzzle Constraint::getSolution() { return this->solution; }
// Getter function for the total time elapsed to arrive at a solution
double Constraint::getTimeElapsed() { return this->timeElapsed; }
