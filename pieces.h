#ifndef PIECES_HEADER
#define PIECES_HEADER

#include "chess.h"
#include <vector>

class Pawn: public Piece
{
    public:
        Pawn(Position*,Board*,int);
};

#endif