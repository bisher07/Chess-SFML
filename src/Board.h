#pragma once
#include "Piece.h"

class Board
{
public:
    Board();

    Piece getPiece(int row, int col);

    void movePiece(int fromRow, int fromCol, int toRow, int toCol);

    bool isEmpty(int row, int col);

private:
    Piece grid[8][8];
};