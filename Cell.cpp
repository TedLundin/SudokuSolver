#include "Cell.h"


// Cell class default constructor
Cell::Cell() {}
// Cell class constructor
// parameter r : an integer 0 - 8 inclusive denoting which row the Cell object is in
// parameter c : an integer 0 - 8 inclusive denoting which column the Cell object is in
// parameter ans : an integer 1 - 9 that represents what the correct answer for that Cell is within the puzzle
Cell::Cell(int r, int c, int ans = 0) {
    this->cellNum = (9 * r) + c;
    this->row = r;
    this->col = c;
    // block is the 3 x 3 subgrid in the Sudoku puzzle that the Cell is located in
    this->block = 3 * (r / 3) + (c / 3);
    this->answer = ans;
    // isHint is a boolean which tells us if the Cell has a given answer in the puzzle already or not
    this->isHint = false;

    // This section of code is sorting all the other Cells that coincide with our Cell into 'peer' arrays
    // A peer Cell is a Cell that is either in our Cell's row, column, or block
    // Peer Cells are relevant because the answers to these Cells will impact the answer to our Cell and vice versa
    int rowInd = 0, colInd = 0, blockInd = 0, peersInd = 0;
    int r1 = ((this->block / 3) * 3), c1 = ((this->block % 3) * 3);
    for(int i = 0; i < 9; i++) {
        // Iteration through the Cell's row, adding any Cells that are not the Cell itself to its row peer array
        if(9 * r + i != cellNum) {
            this->rowPeers[rowInd] = 9 * r + i;
            this->peers[peersInd] = 9 * r + i;
            peersInd++;
            rowInd++; }
        // Iteration through the Cell's column, adding any Cells that are not the Cell itself to its column peer array
        if(9 * i + c != cellNum) {
            this->colPeers[colInd] = 9 * i + c;
            this->peers[peersInd] = 9 * i + c;
            peersInd++;
            colInd++; }
        // Iteration through the Cell's block, adding any Cells that are not the Cell itself to its block peer array
        if(9 * (r1 + (i / 3)) + (c1 + (i % 3)) != cellNum) {
            this->blockPeers[blockInd] = 9 * (r1 + (i / 3)) + (c1 + (i % 3));
            blockInd++;
            if((r1 + (i / 3)) != r && (c1 + (i % 3)) != c) {
                this->peers[peersInd] = 9 * (r1 + (i / 3)) + (c1 + (i % 3));
                peersInd++; } } }
    // Initialize all note values to true unless an answer is already given
    if(this->answer >= 10 || this->answer <= 0) {
        for(int i = 0; i < 9; i++) {
            this->notes[i] = true;
        }
    } else {
        for(int i = 0; i < 9; i++) {
            this->notes[i] = false;
        }
        this->notes[this->answer - 1] = true;
    }
}

// Getter function for the Cell's number 0 - 80
int Cell::getCellNum() { return this->cellNum; }
// Getter function for the Cell's row 0 - 8
int Cell::getRow() { return this->row; }
// Getter function for the Cell's column 0 - 8
int Cell::getCol() { return this->col; }
// Getter function for the Cell's block 0 - 8
int Cell::getBlock() { return this->block; }
// Getter function for the Cell's answer 1 - 9
int Cell::getAnswer() { return this->answer; }
// A function that returns an array of booleans denoting whether or not the numbers 1 - 9 are viable answers for said Cell
bool* Cell::getNotes() { return this->notes; }
// Function that checks if the given number i is a viable answer to the Cell
bool Cell::getNotes(int i) { return this->notes[i]; }
// Function that tells us if a Cell is part of the given answers within the Sudoku puzzle
bool Cell::getIsHint() { return this->isHint; }
// Getter function for the Cell's row peers
int* Cell::getRowPeers() { return this->rowPeers; }
// Getter function for the Cell's column peers
int* Cell::getColPeers() { return this->colPeers; }
// Getter function for the Cell's block peers
int* Cell::getBlockPeers() { return this->blockPeers; }
// Getter function for all of the Cell's peers
int* Cell::getPeers() { return this->peers; }
// Setter function for the Cell's answer value
void Cell::setAnswer(int ans) { 
    this->answer = ans;
    // Update all notes to reflect the answer input
    if(ans < 10 && ans > 0) {
        for(int i = 0; i < 9; i++)
            this->notes[i] = false;
        this->notes[ans - 1] = true;
    }
}
// Setter function for the Cell's isHint value
void Cell::setIsHint(bool b) { this->isHint = b; }
// Setter function for the Cell's notes value
void Cell::setNotes(bool *note) {
    for(int i = 0; i < 9; i++)
        this->notes[i] = note[i];
}
// Takes a number 1 - 9 and changes the Cell's notes to reflect that this is a viable answer to the Cell
void Cell::addNote(int note) {
    this->notes[note - 1] = true;
}
// Takes a number 1 - 9 and changes the Cell's notes to reflect that this is not a viable answer to this Cell
void Cell::removeNote(int note) {
    this->notes[note - 1] = false;
}
