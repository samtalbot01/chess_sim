#include "engine.h"

MovePair::MovePair(Move first,Move second)
{
    f=first;
    s=second;
    value = f.value-s.value;   
}

ChessEngine::ChessEngine(Board* b,int c,int d)
{
    board = b;
    colour = c;
    depth = d;
}

/*

int branch(MovePair m,int depth,Board& b)
{
    Board cpy(b);
    cpy.make_move(m.f);
    cpy.make_move(m.s);

    l = b.all_moves(c);
    //generate movepairs


    int total = m.value;
    if(depth !=0)
        for(lp)
            total += branch(mp,depth-1,cpy);
    return total;

}


int branch(Move,depth)
{
    Board cpy(*b);
    cpy.make(Move);
    lst = cpy.moves();
    for(lst)
        MovePair(Move,lst[i])

    int total = 
    for(Movepairs)
        total += branch(movepair,depth-1,cpy);

    return total;
}

Branch b(Move,branch(Move,depth,b));


*/