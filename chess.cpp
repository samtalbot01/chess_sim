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
        //WHITE
        //PAWNS
        for(char c='A';c<='H';c++)
        {
            std::ostringstream oss;
            oss<<c<<"2";
            add_piece(new Pawn(W),oss.str());
        }
        
        //BLACK PAWNS
        for(char c='A';c<='H';c++)
        {
            std::ostringstream oss;
            oss<<c<<"7";
            add_piece(new Pawn(B),oss.str());
        }

        //ROOKS
        add_piece(new Rook(W),"A1");
        add_piece(new Rook(W),"H1");

        add_piece(new Rook(B),"A8");
        add_piece(new Rook(B),"H8");

        //KNIGHTS
        add_piece(new Knight(W),"B1");
        add_piece(new Knight(W),"G1");

        add_piece(new Knight(B),"B8");
        add_piece(new Knight(B),"G8");

        //BISHOPS
        add_piece(new Bishop(W),"C1");
        add_piece(new Bishop(W),"F1");

        add_piece(new Bishop(B),"C8");
        add_piece(new Bishop(B),"F8");

        //QUEENS
        add_piece(new Queen(W),"D1");

        add_piece(new Queen(B),"D8");

        //KINGS
        add_piece(new King(W),"E1");

        add_piece(new King(B),"E8");
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

int Board::add_piece(Piece* p,Position* pos)
{
    if(!find(p))
    {
        pos->occupier=p;
        pieces.push_back(p);
        return 1;
    }

    return 0;
}

int Board::add_piece(Piece* p,std::string s)
{
    Position* pos = get_from_token(s);
    if(pos&&!find(p))
    {
        pos->occupier=p;
        pieces.push_back(p);
        return 1;
    }
    
    return 0;
    
    //do fuck all if its 0 since the position doesn't exist
}

//self explanatory
Board::~Board()
{
    for(auto& p:pieces)
        delete p;
}

//minimal validation(only checks that origin pos actually has a piece in it) just edits the board given the move
int Board::make_move(Move m)
{
    if(m.start->occupier)
    {
        m.end->occupier = m.start->occupier;
        m.start->occupier=0;
        return 1;
    }
    return 0;
}

Position* Board::traverse(Position* origin,int df,int dr)
{
    Position tdest(origin->file+df,origin->rank+dr);
    Position* dest = find(tdest);
    if(dest)
        return dest;
    return 0;
}

Position* Board::find(Position& p)
{
    for(auto& pos:positions)
        if(p==pos)
            return &pos;
    return 0;
}

int Board::process_move(Position* o, Position* e, std::vector<Move>& l)
{
    int stop=0;
    if(e)
    {
        if(e->occupier)
        {
            stop = 1; //stop run
            if(e->occupier->get_colour()!=o->occupier->get_colour())
            {
                Move mv(o,e);
                l.push_back(mv);
            }
        }
        else
        {
            //unoccupied add move no stop
            Move mv(o,e);
            l.push_back(mv);
        }
    }
    return stop;
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

Move::Move(Position* s,Position* e)
{
    start=s;
    end=e;
    if(end->occupier)
        value = end->occupier->get_value();
    else
        value = 0;
}
/*
End struct methods
*/
