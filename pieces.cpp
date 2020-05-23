#include "pieces.h"

//Pawn
Pawn::Pawn(int c): Piece(c)
{
    type="Pawn";
    value = 1;
}

std::vector<Move> Pawn::moves(Position* p,Board* b) const
{
    //stub
    return {};
}

//Rook
Rook::Rook(int c): Piece(c)
{
    type="Rook";
    value = 5;
}

std::vector<Move> Rook::moves(Position* p,Board* b) const
{
    //stub
    return {};
}

//Knight
Knight::Knight(int c): Piece(c)
{
    type="Knight";
    value = 3;
}

std::vector<Move> Knight::moves(Position* p,Board* b) const
{
    //stub
    return {};
}

//Bishop
Bishop::Bishop(int c): Piece(c)
{
    type="Bishop";
    value = 3;
}

std::vector<Move> Bishop::moves(Position* p,Board* b) const
{
    //stub
    return {};
}

//Queen
Queen::Queen(int c): Piece(c)
{
    type="Queen";
    value = 9;
}

std::vector<Move> Queen::moves(Position* p,Board* b) const
{
    //stub
    return {};
}

//King
King::King(int c): Piece(c)
{
    type="King";
    value = 1000;
}

std::vector<Move> King::moves(Position* p,Board* b) const
{
    //stub
    return {};
}