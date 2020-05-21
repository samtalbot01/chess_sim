#include "chess.h"
#include "pieces.h"
#include <algorithm>
#include <iostream>
#include <sstream>
using std::vector;

Piece::Piece(Position* p,Board* b,int c)
{
    board = b;
    colour = c;
    vector<Position>::iterator it;
    it = std::find(b->positions.begin(),b->positions.end(),*p);
    it->occupier = this;
}


/**
 * mode is either STANDARD or EMPTY
 * sets how to lay out the pieces
 * 
 **/
Board::Board(int mode)
{
    for(char c='A';c<='H';c++)
        for(int i=1;i<=8;i++)
        {
            Position p;
            p.file = c;
            p.rank = i;
            p.occupier = 0;
            positions.push_back(p);
        }

    if(mode==STANDARD)
    {
        Pawn p(&positions[1],this,B);
        pieces.push_back(p);
    }
    else if(mode==EMPTY)
    {
        //don't add any pieces
    }
}

std::string Board::to_string()
{
    std::ostringstream o;
    for(Position p:positions)
    {
        std::string piece;
        if(!p.occupier)
            piece="empty";
        else
            piece = p.occupier->get_type();
        o << p.file << p.rank << ": " << piece << std::endl;   
    }
    return o.str();
}

bool operator==(Position p,Position q)
{
    if(p.file==q.file&&p.rank==q.rank)
        return true;
    else
        return false;    
}

