#include "pieces.h"

Pawn::Pawn(int c): Piece(c)
{
    type="Pawn";
}

std::vector<Move> Pawn::moves(Position* p,Board* b) const
{
    //stub
    return {};
}