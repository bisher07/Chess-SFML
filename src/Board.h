#pragma once
#include "Piece.h"

class Board
{
public:
    Board();

    Piece getPiece(int row, int col);

    void movePiece(int fromRow, int fromCol, int toRow, int toCol);

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol);

    bool isEmpty(int row, int col);

    bool isInCheck(PieceColor color);

    void setPiece(int row, int col, Piece piece);

    bool hasAnyValidMove(PieceColor color);

private:
    Piece grid[8][8];
};