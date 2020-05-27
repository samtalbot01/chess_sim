#ifndef PIECES_HEADER
#define PIECES_HEADER

#include "chess.h"
#include <vector>

class Pawn: public Piece
{
    public:
        Pawn(int);
        std::vector<Move> moves(Position*,Board* b) const; //todo
};

class Rook: public Piece
{
    public:
        Rook(int);
        std::vector<Move> moves(Position*,Board* b) const; //todo
};

class Bishop: public Piece
{
    public:
        Bishop(int);
        std::vector<Move> moves(Position*,const std::vector<Position>& board) const; //todo
};

class Knight: public Piece
{
    public:
        Knight(int);
        std::vector<Move> moves(Position*,const std::vector<Position>&) const; //todo
};

class Queen: public Piece
{
    public:
        Queen(int);
        std::vector<Move> moves(Position*,const std::vector<Position>& board) const; //todo
};

class King: public Piece
{
    public:
        King(int);
        std::vector<Move> moves(Position*,const std::vector<Position>& board) const; //todo
};
#endif