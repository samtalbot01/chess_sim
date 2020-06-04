#ifndef CHESS_ENGINE_H
#define CHESS_ENGINE_H

#include "chess.h"


struct MovePair
{
    Move f;
    Move s;
    int value;
    MovePair(Move,Move);
};

class ChessEngine
{
    public:
        ChessEngine(Board*,int,int);
        Move get_move();
    private:
        Board* board;
        int depth;
        int colour;
        int branch(Move,int);
        int branch(MovePair,int,Board&);
};

#endif