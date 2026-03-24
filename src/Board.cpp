#include "Board.h"
#include <cmath>

Board::Board()
{
    // step 1: set every square to empty
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            grid[row][col].type = PieceType::empty;
            grid[row][col].color = PieceColor::empty;
        }
    }

    grid[0][0].type = PieceType::Rook;
    grid[0][0].color = PieceColor::Black;
    grid[0][1].type = PieceType::Knight;
    grid[0][1].color = PieceColor::Black;
    grid[0][2].type = PieceType::Bishop;
    grid[0][2].color = PieceColor::Black;
    grid[0][3].type = PieceType::Queen;
    grid[0][3].color = PieceColor::Black;
    grid[0][4].type = PieceType::King;
    grid[0][4].color = PieceColor::Black;
    grid[0][5].type = PieceType::Bishop;
    grid[0][5].color = PieceColor::Black;
    grid[0][6].type = PieceType::Knight;
    grid[0][6].color = PieceColor::Black;
    grid[0][7].type = PieceType::Rook;
    grid[0][7].color = PieceColor::Black;

    for (int col = 0; col < 8; col++)
    {
        grid[1][col].type = PieceType::Pawn;
        grid[1][col].color = PieceColor::Black;
    }

    grid[7][0].type = PieceType::Rook;
    grid[7][0].color = PieceColor::White;
    grid[7][1].type = PieceType::Knight;
    grid[7][1].color = PieceColor::White;
    grid[7][2].type = PieceType::Bishop;
    grid[7][2].color = PieceColor::White;
    grid[7][3].type = PieceType::Queen;
    grid[7][3].color = PieceColor::White;
    grid[7][4].type = PieceType::King;
    grid[7][4].color = PieceColor::White;
    grid[7][5].type = PieceType::Bishop;
    grid[7][5].color = PieceColor::White;
    grid[7][6].type = PieceType::Knight;
    grid[7][6].color = PieceColor::White;
    grid[7][7].type = PieceType::Rook;
    grid[7][7].color = PieceColor::White;

    for (int col = 0; col < 8; col++)
    {
        grid[6][col].type = PieceType::Pawn;
        grid[6][col].color = PieceColor::White;
    }
}

Piece Board::getPiece(int row, int col)
{
    return grid[row][col];
}

void Board::movePiece(int fromRow, int fromCol, int toRow, int toCol)
{
    grid[toRow][toCol].type = grid[fromRow][fromCol].type;
    grid[toRow][toCol].color = grid[fromRow][fromCol].color;
    grid[fromRow][fromCol].type = PieceType::empty;
    grid[fromRow][fromCol].color = PieceColor::empty;
}

bool Board::isEmpty(int row, int col)
{
    if (grid[row][col].type == PieceType::empty && grid[row][col].color == PieceColor::empty)
        return true;
    else
        return false;
}

bool Board::isValidMove(int fromRow, int fromCol, int toRow, int toCol)
{
    Piece piece = grid[fromRow][fromCol];

    if (toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8)
        return false;

    if (grid[toRow][toCol].color == piece.color)
        return false;

    if (piece.type == PieceType::Pawn)
    {
        int direction = (piece.color == PieceColor::White) ? -1 : 1;

        if (!(toRow == fromRow + direction && toCol == fromCol))
        {
            if (toRow == fromRow + direction && (toCol == fromCol + 1 || toCol == fromCol - 1) && !isEmpty(toRow, toCol) && grid[toRow][toCol].color != piece.color)
                return true;

            return false;
        }

        if (!isEmpty(toRow, toCol))
            return false;

        return true;
    }

    else if (piece.type == PieceType::Rook)
    {
        if (fromRow != toRow && fromCol != toCol)
            return false;

        if (fromRow == toRow)
        {
            int step = (toCol > fromCol) ? 1 : -1;
            for (int col = fromCol + step; col != toCol; col += step)
            {
                if (!isEmpty(fromRow, col))
                    return false;
            }
        }
        else
        {
            int step = (toRow > fromRow) ? 1 : -1;
            for (int row = fromRow + step; row != toRow; row += step)
            {
                if (!isEmpty(row, fromCol))
                    return false;
            }
        }

        return true;
    }

    else if (piece.type == PieceType::Knight)
    {
        if (!(abs(toRow - fromRow) == 2 && abs(toCol - fromCol) == 1) && !(abs(toCol - fromCol) == 2 && abs(toRow - fromRow) == 1))
            return false;
        else if (grid[toRow][toCol].color == piece.color)
            return false;

        return true;
    }

    else if (piece.type == PieceType::Bishop)
    {
        if (!(abs(toRow - fromRow) == abs(toCol - fromCol)))
            return false;
        else
        {
            if (toRow > fromRow && toCol > fromCol)
            {
                for (int row = fromRow + 1, col = fromCol + 1; row < toRow; row++, col++)
                {
                    if (!isEmpty(row, col))
                        return false;
                }
            }

            else if (toRow > fromRow && toCol < fromCol)
            {
                for (int row = fromRow + 1, col = fromCol - 1; row < toRow; row++, col--)
                {
                    if (!isEmpty(row, col))
                        return false;
                }
            }

            else if (toRow < fromRow && toCol > fromCol)
            {
                for (int row = fromRow - 1, col = fromCol + 1; row > toRow; row--, col++)
                {
                    if (!isEmpty(row, col))
                        return false;
                }
            }

            else if (toRow < fromRow && toCol < fromCol)
            {
                for (int row = fromRow - 1, col = fromCol - 1; row > toRow; row--, col--)
                {
                    if (!isEmpty(row, col))
                        return false;
                }
            }
        }

        if (grid[toRow][toCol].color == piece.color)
            return false;

        return true;
    }

    else if (piece.type == PieceType::Queen)
    {
        if (grid[toRow][toCol].color == piece.color)
            return false;

        if (fromRow == toRow)
        {
            int step = (toCol > fromCol) ? 1 : -1;
            for (int col = fromCol + step; col != toCol; col += step)
            {
                if (!isEmpty(fromRow, col))
                    return false;
            }
        }

        else if (fromCol == toCol)
        {
            int step = (toRow > fromRow) ? 1 : -1;
            for (int row = fromRow + step; row != toRow; row += step)
            {
                if (!isEmpty(row, fromCol))
                    return false;
            }
        }

        if (toRow > fromRow && toCol > fromCol)
        {
            for (int row = fromRow + 1, col = fromCol + 1; row < toRow; row++, col++)
            {
                if (!isEmpty(row, col))
                    return false;
            }
        }

        else if (toRow > fromRow && toCol < fromCol)
        {
            for (int row = fromRow + 1, col = fromCol - 1; row < toRow; row++, col--)
            {
                if (!isEmpty(row, col))
                    return false;
            }
        }

        else if (toRow < fromRow && toCol > fromCol)
        {
            for (int row = fromRow - 1, col = fromCol + 1; row > toRow; row--, col++)
            {
                if (!isEmpty(row, col))
                    return false;
            }
        }

        else if (toRow < fromRow && toCol < fromCol)
        {
            for (int row = fromRow - 1, col = fromCol - 1; row > toRow; row--, col--)
            {
                if (!isEmpty(row, col))
                    return false;
            }
        }

        return true;
    }

    else if (piece.type == PieceType::King)
    {
        if (abs(toRow - fromRow) > 1 || abs(toCol - fromCol) > 1)
            return false;

        else if (grid[toRow][toCol].color == piece.color)
            return false;

        return true;
    }

    return false;
}
