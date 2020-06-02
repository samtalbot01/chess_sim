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
        //add_piece(new King(W),"E1");

        //add_piece(new King(B),"E8");
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
void Board::destroy()
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
    bool pchk;
    if(e)
    {
        if(e->occupier)
        {
            stop = 1; //stop run
            if(e->occupier->get_colour()!=o->occupier->get_colour())
            {
                Move mv(o,e);
                pchk = check(o->occupier->get_colour(),mv);
                if(!pchk)
                    l.push_back(mv);
            }
        }
        else
        {
            //unoccupied add move no stop
            Move mv(o,e);
            pchk = check(o->occupier->get_colour(),mv);
            if(!pchk)
                l.push_back(mv);
        }
    }
    return stop;
}

bool Board::check(int c)
{
    //Checks all enemy pieces moves for king attacks 
    //***DOESNT ANYMORE THIS CAUSES GIGA BUG***
    
    //checks horse squares, ranks & files for pieces that take on such positions

    Position* pos = 0;
    for(Piece* p:pieces)
        if(p->get_colour()==c&&p->get_type()=="King")
        {
            pos = find(p);
            break;
        }
    Piece* k; //just for brevity
    if(!pos)
        return false; //no king so can't be in check
    else
        k = pos->occupier;

    //pawns
    int pawnrank = (c==W) ? 1 : -1;
    auto p1 = traverse(pos,1,pawnrank); 
    auto p2 = traverse(pos,-1,pawnrank);
    if(p1)
        if(p1->occupier)
        {
            if(p1->occupier->get_type()=="Pawn"&&p1->occupier->get_colour()!=c)
                return true;
        }
    if(p2)
        if(p2->occupier)
        {
            if(p2->occupier->get_type()=="Pawn"&&p2->occupier->get_colour()!=c)
                return true;
        }

    //Knight
    //top fork
    auto endpu = traverse(pos,1,2);
    auto endpu2 = traverse(pos,-1,2);
    if(endpu)
        if(endpu->occupier)
        {
            if(endpu->occupier->get_type()=="Knight"&&endpu->occupier->get_colour()!=c)
                return true;
        }
    if(endpu2)
        if(endpu2->occupier)
        {
            if(endpu2->occupier->get_type()=="Knight"&&endpu2->occupier->get_colour()!=c)
                return true;
        }

    //Individually check for king on close square
    auto k1 = traverse(pos,1,0);
    auto k2 = traverse(pos,-1,0);
    auto k3 = traverse(pos,0,1);
    auto k4 = traverse(pos,0,-1);
    auto k5 = traverse(pos,1,1);
    auto k6 = traverse(pos,1,-1);
    auto k7 = traverse(pos,-1,1);
    auto k8 = traverse(pos,-1,-1);
    if(k1)
    {
        if(k1->occupier)
            if(k1->occupier->get_type()=="King"&&k1->occupier->get_colour()!=c)
                return true;
    }
    if(k2)
    {
        if(k2->occupier)
            if(k2->occupier->get_type()=="King"&&k2->occupier->get_colour()!=c)
                return true;
    }
    if(k3)
    {
        if(k3->occupier)
            if(k3->occupier->get_type()=="King"&&k3->occupier->get_colour()!=c)
                return true;
    }
    if(k4)
    {
        if(k4->occupier)
            if(k4->occupier->get_type()=="King"&&k4->occupier->get_colour()!=c)
                return true;
    }
    if(k5)
    {
        if(k5->occupier)
            if(k5->occupier->get_type()=="King"&&k5->occupier->get_colour()!=c)
                return true;
    }
    if(k6)
    {
        if(k6->occupier)
            if(k6->occupier->get_type()=="King"&&k6->occupier->get_colour()!=c)
                return true;
    }
    if(k7)
    {
        if(k7->occupier)
            if(k7->occupier->get_type()=="King"&&k7->occupier->get_colour()!=c)
                return true;
    }
    if(k8)
    {
        if(k8->occupier)
            if(k8->occupier->get_type()=="King"&&k8->occupier->get_colour()!=c)
                return true;
    }


    //down
    auto endpd = traverse(pos,1,-2);
    auto endpd2 = traverse(pos,-1,-2);
    if(endpd)
        if(endpd->occupier)
        {
            if(endpd->occupier->get_type()=="Knight"&&endpd->occupier->get_colour()!=c)
                return true;
        }
    if(endpd2)
        if(endpd2->occupier)
        {
            if(endpd2->occupier->get_type()=="Knight"&&endpd2->occupier->get_colour()!=c)
                return true;
        }
    
    //Left
    auto endpl = traverse(pos,-2,1);
    auto endpl2 = traverse(pos,-2,-1);
    if(endpl)
        if(endpl->occupier)
        {
            if(endpl->occupier->get_type()=="Knight"&&endpl->occupier->get_colour()!=c)
                return true;
        }
    if(endpl2)
        if(endpl2->occupier)
        {
            if(endpl2->occupier->get_type()=="Knight"&&endpl2->occupier->get_colour()!=c)
                return true;
        }

    //Right
    auto endpr = traverse(pos,2,1);
    auto endpr2 = traverse(pos,2,-1);
    if(endpr)
        if(endpr->occupier)
        {
            if(endpr->occupier->get_type()=="Knight"&&endpr->occupier->get_colour()!=c)
                return true;
        }
    if(endpr2)
        if(endpr2->occupier)
        {
            if(endpr2->occupier->get_type()=="Knight"&&endpr2->occupier->get_colour()!=c)
                return true;
        }


    //Rook
    //upward
    int increment = 1;
    while(traverse(pos,0,increment))
    {
        auto tp = traverse(pos,0,increment);
        if(endpr)
            if(endpr->occupier)
            {
                if(endpr->occupier->get_type()=="Rook"||endpr->occupier->get_type()=="Queen")
                    if(endpr->occupier->get_colour()!=c)
                        return true;
                break;
            }
        increment++;
    }

    //down
    increment = 1;
    while(traverse(pos,0,-increment))
    {
        auto tp = traverse(pos,0,-increment);
        if(endpr)
            if(endpr->occupier)
            {
                if(endpr->occupier->get_type()=="Rook"||endpr->occupier->get_type()=="Queen")
                    if(endpr->occupier->get_colour()!=c)
                        return true;
                break;
            }
        increment++;
    }

    //right
    increment = 1;
    while(traverse(pos,increment,0))
    {
        auto tp = traverse(pos,increment,0);
        if(endpr)
            if(endpr->occupier)
            {
                if(endpr->occupier->get_type()=="Rook"||endpr->occupier->get_type()=="Queen")
                    if(endpr->occupier->get_colour()!=c)
                        return true;
                break;
            }
        increment++;
    }

    increment = 1;
    while(traverse(pos,-increment,0))
    {
        auto tp = traverse(pos,-increment,0);
        if(endpr)
            if(endpr->occupier)
            {
                if(endpr->occupier->get_type()=="Rook"||endpr->occupier->get_type()=="Queen")
                    if(endpr->occupier->get_colour()!=c)
                        return true;
                break;
            }
        increment++;
    }

    
    return false;
}

/*
cpy will drop out of scope and dealloc the position data but leave the pieces

*/
bool Board::check(int c,Move mv)
{
    Board cpy(*this);

    //turn move on board b into move on board cpy
    Move cpymove(cpy.find(*mv.start),cpy.find(*mv.end));

    cpy.make_move(cpymove);
    bool rt = cpy.check(c);
    return rt;
}

Board::Board(const Board& orig)
{
    pieces = orig.pieces;
    positions = orig.positions;
}

std::vector<std::vector<Move>> Board::all_moves(int c)
{
    std::vector<std::vector<Move>> mvecs = {};
    for(Piece* p:pieces)
        if(p->get_colour()==c)
        {
            Position* pos = find(p);
            if(pos)
                mvecs.push_back(p->moves(pos,this));
        }
    return mvecs;
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

Move Move::inv()
{
    Move mv(end,start);
    mv.value = -value;
    return mv;
}
/*
End struct methods
*/
