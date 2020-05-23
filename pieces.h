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

class Rook: public Piece
{
    public:
        Rook(int);
        std::vector<Move> moves(Position*,Board*) const; //todo
};

class Bishop: public Piece
{
    public:
        Bishop(int);
        std::vector<Move> moves(Position*,Board*) const; //todo
};

class Knight: public Piece
{
    public:
        Knight(int);
        std::vector<Move> moves(Position*,Board*) const; //todo
};

class Queen: public Piece
{
    public:
        Queen(int);
        std::vector<Move> moves(Position*,Board*) const; //todo
};

class King: public Piece
{
    public:
        King(int);
        std::vector<Move> moves(Position*,Board*) const; //todo
};
#endif