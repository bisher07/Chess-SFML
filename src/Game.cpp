#include "Game.h"

Game::Game()
{
    currentTurn = PieceColor::White;
    pieceSelected = false;
    selectedRow = -1;
    selectedCol = -1;
}

Board &Game::getBoard()
{
    return board;
}

PieceColor Game::getCurrentTurn()
{
    return currentTurn;
}

void Game::handleClick(int row, int col)
{
    if (!pieceSelected)
    {
        if (board.getPiece(row, col).color == currentTurn && !board.isEmpty(row, col))
        {
            selectedRow = row;
            selectedCol = col;
            pieceSelected = true;
        }
    }

    else if (pieceSelected)
    {
        if (board.isValidMove(selectedRow, selectedCol, row, col))
        {
            board.movePiece(selectedRow, selectedCol, row, col);
            if (currentTurn == PieceColor::White)
                currentTurn = PieceColor::Black;
            else
                currentTurn = PieceColor::White;
        }

        selectedRow = -1;
        selectedCol = -1;
        pieceSelected = false;
    }
}