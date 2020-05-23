#include "chess.h"
#include "pieces.h"
#include <algorithm>
#include <iostream>
#include <sstream>
using std::vector;

/*
Piece methods
*/
Piece::Piece(int c)
{
    colour = c;
}

std::string Piece::get_full_name() const
{
    if(colour==B)
        return "Black "+type;
    else
        return "White "+type;
}
/*
End piece methods
*/

/**
 * Board methods
 * 
 * 
 * mode is either STANDARD or EMPTY
 * sets how to lay out the pieces
 * 
 **/
Board::Board(int mode)
{
    for(char c='A';c<='H';c++)
        for(int i=1;i<=8;i++)
        {
            Position p(c,i);
            positions.push_back(p);
        }

    if(mode==STANDARD)
    {
        //make board
        
    }
    else if(mode==EMPTY)
    {
        //don't add any pieces
    }
}

const vector<Position> &Board::get_positions() const
{
    const vector<Position>& p = positions;
    return p;
}

std::string Board::to_string() const
{
    //unsure what to make the final version of this. Maybe an 8x8 representation of the board?
    //mainly will be used for testing

    std::ostringstream oss;
    for(const Position& p:positions)
        if(p.occupier!=0)
            oss << p.token << ": "<< p.occupier->get_full_name() << std::endl;
        else
            oss << p.token << ": Empty" << std::endl;
    return oss.str();
}

Position* Board::get_from_token(std::string s)
{
    if(s.length()!=2)
        return 0;
    for(int i=0;i<positions.size();i++)
        if(positions[i]==s)
            return &positions[i];
    return 0;
}

Position* Board::find(Piece* p)
{
    for(int i=0;i<positions.size();i++)
        if(positions[i].occupier==p)
            return &positions[i];
    return 0;
}

void Board::add_piece(Piece* p,Position* pos)
{
    if(!find(p))
    {
        pos->occupier=p;
        pieces.push_back(p);
    }
}

void Board::add_piece(Piece*p,std::string s)
{
    Position* pos = get_from_token(s);
    if(pos&&!find(p))
    {
        pos->occupier=p;
        pieces.push_back(p);
    }
    //do fuck all if its 0 since the position doesn't exist
}
/*
End board methods

Struct methods
*/
Position::Position(char c,int i)
{
    file = c;
    rank = i;
    occupier = 0;
    std::ostringstream o;
    o<<file<<rank;
    token = o.str();
}

bool Position::operator== (const Position& p) const
{
    if(rank==p.rank&&file==p.file)
        return true;
    else
        return false;
}

bool Position::operator== (const std::string& s) const
{ 
    int srank;
    if(s.length()==2&&s.at(0)==file)
    {
        srank = (int)s.at(1)-'0';
        if(srank==rank)
            return true;
    }
    else
        return false;
    return false;
}

Move::Move(Position* s,Position* e,int v)
{
    start=s;
    end=e;
    value=v;
}
/*
End struct methods
*/
