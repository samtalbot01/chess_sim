#ifndef CHESS_ENGINE_H
#define CHESS_ENGINE_H

#include "chesslib.h"
#include <list>

namespace eng
{

class Line
{
    public:
        int eval() const;
        void add_move(Move&);
    private:
        std::list<Move> moves;
};


};
#endif