#ifndef PIECES_HEADER
#define PIECES_HEADER

#include "chess.h"
#include <vector>

class Pawn: public Piece
{
    public:
        Pawn(int);
        std::vector<Move> moves(Position*,Board*) const; //todo
};

#endif