#pragma once
#include "Board.h"

class Game
{
public:
    Game();

    void handleClick(int row, int col);

    Board &getBoard();

    PieceColor getCurrentTurn();

private:
    Board board;

    PieceColor currentTurn;

    int selectedRow, selectedCol;

    bool pieceSelected;
};