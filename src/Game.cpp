#include "Game.h"

Game::Game()
{
    currentTurn = PieceColor::White;
    pieceSelected = false;
    selectedRow = -1;
    selectedCol = -1;
    gameOver = false;
    winner = PieceColor::empty;
    promotionRow = -1;
    promotionCol = -1;
    awaitingPromotion = false;
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
    if (awaitingPromotion)
        return;

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

            if (!board.isInCheck(currentTurn)) // move is safe
            {
                checkPawnPromotion(row, col);

                if (currentTurn == PieceColor::White)
                    currentTurn = PieceColor::Black;
                else
                    currentTurn = PieceColor::White;

                // only run expensive check when needed
                if (board.isInCheck(currentTurn) || !board.hasAnyValidMove(currentTurn))
                    checkForWin();
            }
            else
            {
                // undo - move puts own king in check
                board.movePiece(row, col, selectedRow, selectedCol);
                board.setPiece(row, col, temp);
            }
        }

        selectedRow = -1;
        selectedCol = -1;
        pieceSelected = false;
    }
}

void Game::checkForWin()
{
    if (board.isInCheck(currentTurn) && !board.hasAnyValidMove(currentTurn))
    {
        gameOver = true;
        winner = currentTurn == PieceColor::White ? PieceColor::Black : PieceColor::White;
    }

    else if (!board.isInCheck(currentTurn) && !board.hasAnyValidMove(currentTurn))
    {
        gameOver = true;
        winner = PieceColor::empty;
    }
}

void Game::checkPawnPromotion(int row, int col)
{
    if (board.getPiece(row, col).type == PieceType::Pawn)
    {
        if (row == 7 && board.getPiece(row, col).color == PieceColor::Black)
        {
            awaitingPromotion = true;
            promotionRow = row;
            promotionCol = col;
        }
        else if (row == 0 && board.getPiece(row, col).color == PieceColor::White)
        {
            awaitingPromotion = true;
            promotionRow = row;
            promotionCol = col;
        }
    }
}

void Game::promotePawn(PieceType type)
{
    Piece piece;
    piece.type = type;
    piece.color = board.getPiece(promotionRow, promotionCol).color;

    board.setPiece(promotionRow, promotionCol, piece);
    awaitingPromotion = false;
}

bool Game::isAwaitingPromotion()
{
    return awaitingPromotion;
}