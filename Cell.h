#pragma once


class Cell {
    public:
        Cell();
        Cell(int r, int c, int ans);
        
        int getCellNum();
        int getRow();
        int getCol();
        int getBlock();
        int getAnswer();
        bool* getNotes();
        bool getNotes(int i);
        bool getIsHint();
        int* getRowPeers();
        int* getColPeers();
        int* getBlockPeers();
        int* getPeers();
        void setAnswer(int ans);
        void setIsHint(bool b);
        void setNotes(bool *note);
        void addNote(int note);
        void removeNote(int note);
    private:
        int cellNum;
        int row;
        int col;
        int block;
        int answer;
        bool notes[9];
        bool isHint;
        int rowPeers[8];
        int colPeers[8];
        int blockPeers[8];
        int peers[20];
};
