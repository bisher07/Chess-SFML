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
    else
    {
        if (board.isValidMove(selectedRow, selectedCol, row, col))
        {
            Piece temp = board.getPiece(row, col);
            board.movePiece(selectedRow, selectedCol, row, col);

            if (!board.isInCheck(currentTurn))
            {
                if (currentTurn == PieceColor::White)
                    currentTurn = PieceColor::Black;
                else
                    currentTurn = PieceColor::White;
            }
            else
            {
                // undo the move
                board.movePiece(row, col, selectedRow, selectedCol);
                board.setPiece(row, col, temp);
            }
        }

        selectedRow = -1;
        selectedCol = -1;
        pieceSelected = false;
    }
}