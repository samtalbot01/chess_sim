#ifndef CHESS_ENGINE_H
#define CHESS_ENGINE_H

#include "chess.h"
#include <list>

namespace eng
{

struct MovePair
{
    Move f;
    Move s;
    int value;
    MovePair(Move,Move);
};

class Line
{
    public:
        Line(): val(0){};
        Line(MovePair mp):val(0){add_pair(mp);};
        void add_pair(MovePair&);
        int eval();
    private:
        std::list<MovePair> mps;
        int val;
};

class Branch
{
    public:
        Branch(): val(0){};
        ~Branch();
        void add_line(Line*);
        double eval();
        std::vector<Line*> lines;
    private:
        int val;
        
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
        double branch(Move,int); //init the recursion
        void branch(Branch*,int,Board&); //recursive branch builder
        std::vector<MovePair> make_pairs(Move&,Board&);
};

};
#endif