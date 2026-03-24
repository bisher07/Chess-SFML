#pragma once

enum class PieceType
{
    King,
    Queen,
    Rook,
    Bishop,
    Knight,
    Pawn,
    empty
};

enum class PieceColor
{
    Black,
    White,
    empty
};

struct Piece
{
    PieceType type;

    PieceColor color;
};