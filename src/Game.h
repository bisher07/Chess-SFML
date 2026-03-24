#pragma once
#include "Board.h"

class Game
{
public:
    Game();

    void handleClick(int row, int col);

    Board &getBoard();

    PieceColor getCurrentTurn();

    void checkForWin();

    bool isGameOver()
    {
        return gameOver;
    }

    PieceColor getWinner()
    {
        return winner;
    }

private:
    Board board;

    PieceColor currentTurn;

    int selectedRow, selectedCol;

    bool pieceSelected;

    bool gameOver;

    PieceColor winner;
};