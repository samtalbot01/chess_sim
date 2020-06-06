#include "engine.h"
using namespace eng;

MovePair::MovePair(Move first,Move second)
{
    f=first;
    s=second;
    value = f.value-s.value;   
}

void Line::add_pair(MovePair& m)
{
    mps.push_back(m);
    val+=m.value;
}

int Line::eval()
{
    return val;
}

void Branch::add_line(Line* l)
{
    lines.push_back(l);
    val+=l->eval();
}

Branch::~Branch()
{
    for(auto& l:lines)
        delete l;
}

double Branch::eval()
{
    return (double) val/lines.size();
}



ChessEngine::ChessEngine(Board* b,int c,int d)
{
    board = b;
    colour = c;
    depth = d;
}

std::vector<MovePair> ChessEngine::make_pairs(Move& m,Board& b)
{
    std::vector<MovePair> mps;
    Board cpy(b);
    Move cmv = cpy.convert_move(m);
    cpy.make_move(cmv);
    std::vector<Move> r = cpy.all_moves(m.end->occupier->get_colour());

    for(auto& move:r)
        mps.push_back(MovePair(m,move));
    return mps;
}

double ChessEngine::branch(Move m,int dpth)
{
    Branch br;
    if(dpth!=0)
    {
        std::vector<MovePair> pairs = make_pairs(m,*board);
        for(MovePair& mp:pairs)
            br.add_line(new Line(mp));
        branch(&br,dpth-1,*board);
    }

    return br.eval();
}

void ChessEngine::branch(Branch* br,int dpth,Board& b)
{
    //for every line in br. copy board, make moves on board. then for all legal moves generate pairs and add lines
    if(dpth!=0)
    {
        
    }
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
    make new branch

    make list of move pairs;
    for each move pair. start a new line with that movepair add to branch.
    foreach line. 
    

    evaluate branch;
    return value of branch;
}

Branch b(Move,branch(Move,depth,b));


*/