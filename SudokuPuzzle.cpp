#include <iostream>
#include "SudokuPuzzle.h"

using namespace std;

// SudokuPuzzle class constructor
SudokuPuzzle::SudokuPuzzle() {
    // Initialize all 81 Cell objects contained in the SudokuPuzzle
    for(int r = 0; r < 9; r++) {
        for(int c = 0; c < 9; c++) {
            this->board[r][c] = *(new Cell(r, c, 0));
        }
    }
}

// This function inputs all the given hints into the SudokuPuzzle
// A hint is a number that is already given by the puzzle makers, these numbers cannot change
void SudokuPuzzle::installHints(int hintList[81]) {
    for(int i = 0; i < 81; i++) {
        // Check to make sure the hint is a valid number
        if(hintList[i] < 10 && hintList[i] > 0) {
            this->board[(i / 9)][(i % 9)].setAnswer(hintList[i]);
            this->board[(i / 9)][(i % 9)].setIsHint(true);
            // Update all peer Cell notes to reflect the hint input
            int* peers = this->board[(i / 9)][(i % 9)].getPeers();
            for(int j = 0; j < 20; j++) {
                getCell(peers[j])->removeNote(hintList[i]);
            }
        // If no hint is given, set the Cell's value to 0
        } else {
            this->board[i / 9][i % 9].setAnswer(0);
        }
    }
}
// Getter function for SudokuPuzzle's board instance variable
Cell* SudokuPuzzle::getBoard() { return *(this->board); }
// This function returns the Cell in row r, column c
Cell* SudokuPuzzle::getCell(int r, int c) { return &(this->board[r][c]); }
// This function returns the Cell with the indentifying number n
Cell* SudokuPuzzle::getCell(int n) { return &(this->board[(n / 9)][(n % 9)]); }
// Set the answer of the Cell at row r, column c
void SudokuPuzzle::setAnswer(int r, int c, int num) {
    getCell(r, c)->setAnswer(num);
    // Update the notes of the Cell's peers
    int* peers = getCell(r, c)->getPeers();
    for(int i = 0; i < 20; i++) {
        getCell(peers[i])->removeNote(num);
    }
}
// Set the answer of the Cell with the identifying number n
void SudokuPuzzle::setAnswer(int n, int num) {
    getCell(n)->setAnswer(num);
    // Update the notes of the Cell's peers
    int* peers = getCell(n)->getPeers();
    for(int i = 0; i < 20; i++) {
        getCell(peers[i])->removeNote(num);
    }
}
// Function to print out the SudokuPuzzle in a legible format
void SudokuPuzzle::printBoard() {
    std::cout << "__________________________________________________" << std::endl;
    for(int i = 0; i < 81; i++) {
        if(i % 27 == 0 && i != 0 && getCell(i)->getAnswer() < 10 && getCell(i)->getAnswer() > 0) {
            std::cout << "|\n|____|____|____| |____|____|____| |____|____|____|\n__________________________________________________\n| " << getCell(i)->getAnswer() << "  ";
        } else if(i % 27 == 0 && i != 0) {
            std::cout << "|\n|____|____|____| |____|____|____| |____|____|____|\n__________________________________________________\n|    ";
        } else if(i % 9 == 0 && i != 0 && getCell(i)->getAnswer() < 10 && getCell(i)->getAnswer() > 0) {
            std::cout << "|\n|____|____|____| |____|____|____| |____|____|____|\n| " << getCell(i)->getAnswer() << "  ";
        } else if(i % 9 == 0 && i != 0) {
            std::cout << "|\n|____|____|____| |____|____|____| |____|____|____|\n|    ";
        } else if(i % 3 == 0 && i != 0 && getCell(i)->getAnswer() < 10 && getCell(i)->getAnswer() > 0) {
            std::cout << "| | " << getCell(i)->getAnswer() << "  ";
        } else if(i % 3 == 0 && i != 0) {
            std::cout << "| |    ";
        } else if(getCell(i)->getAnswer() < 10 && getCell(i)->getAnswer() > 0) {
            std::cout << "| " << getCell(i)->getAnswer() << "  ";
        } else {
            std::cout << "|    ";
        }
    }
    std::cout << "|\n|____|____|____| |____|____|____| |____|____|____|\n\n";
}
// Function to check if the number n is a valid number for the Cell at row r, column c
bool SudokuPuzzle::isValid(int r, int c, int n) {
    // Iterate through the 9 Cells in the given Cell's row, column, and block
    for(int i = 0; i < 9; i++) {
        // If a Cell with the same number is found within the Cell's column, return false
        if(this->board[i][c].getAnswer() == n)
            return false;
        // If a Cell with the same number is found within the Cell's row, return false
        if(this->board[r][i].getAnswer() == n)
            return false;
        // If a Cell with the same number is found within the Cell's block, return false
        int b = 3 * (r / 3) + (c / 3);
        if(this->board[((b / 3) * 3) + (i / 3)][((b % 3) * 3) + (i % 3)].getAnswer() == n)
            return false;
    }
    // Otherwise, return true
    return true;
}


/* ______________   ______________   ______________ 
  | 1  | 2  | 3  | | 4  |    | 6  | | 7  | 8  | 9  |
  |____|____|____| |____|____|____| |____|____|____|
  | 1  | 2  | 3  | | 4  | 5  | 6  | | 7  | 8  | 9  |
  |____|____|____| |____|____|____| |____|____|____|
  | 1  | 2  | 3  | | 4  | 5  | 6  | | 7  | 8  | 9  |
  |____|____|____| |____|____|____| |____|____|____|
  ________________ ________________ ________________
  | 1  | 2  | 3  | | 4  | 5  | 6  | | 7  | 8  | 9  |
  |____|____|____| |____|____|____| |____|____|____|
  | 1  | 2  | 3  | | 4  | 5  | 6  | | 7  | 8  | 9  |
  |____|____|____| |____|____|____| |____|____|____|
  | 1  | 2  | 3  | | 4  | 5  | 6  | | 7  | 8  | 9  |
  |____|____|____| |____|____|____| |____|____|____|
  ________________ ________________ ________________
  | 1  | 2  | 3  | | 4  | 5  | 6  | | 7  | 8  | 9  |
  |____|____|____| |____|____|____| |____|____|____|
  | 1  | 2  | 3  | | 4  | 5  | 6  | | 7  | 8  | 9  |
  |____|____|____| |____|____|____| |____|____|____|
  | 1  | 2  | 3  | | 4  | 5  | 6  | | 7  | 8  | 9  |
  |____|____|____| |____|____|____| |____|____|____| */
