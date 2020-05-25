#include "pieces.h"
#include <sstream>
//Pawn
Pawn::Pawn(int c): Piece(c)
{
    type="Pawn";
    value = 1;
}

//BIG VOODOO REMAKE THIS IT IS AN ABOMINATION
std::vector<Move> Pawn::moves(Position* p,Board* b) const
{
    std::vector<Move> m;
    if(get_colour()==W)
    {
        std::ostringstream o;

        //forward moves
        int nrank = p->rank + 1;
        o<<p->file<<nrank;
        auto pos1 = b->get_from_token_const(o.str());
        if(!pos1->occupier)
        {
            Move mv(p,(Position*)pos1); //VOODOO DONT JUDGE ME
            m.push_back(mv);
            //Double move
            if(p->rank==2)
            {
                o.str("");
                nrank++;
                o<<p->file<<nrank;
                auto pos2 = b->get_from_token_const(o.str());
                if(!pos2->occupier)
                {
                   Move mv2(p,(Position*)pos2); //VOODOO
                   m.push_back(mv2); 
                }
            }
        }
        o.str("");

        //Diagonal takes
        char nfile = p->file;
        nrank = p->rank + 1;
        if(nfile-1>='A')
        {
            o<<nfile-1<<nrank;
            auto takepos = b->get_from_token_const(o.str());
            if(takepos->occupier)
            {
                Move mv(p,(Position*) takepos);
                m.push_back(mv);
            }
        }
        o.str("");
        if(nfile+1<='H')
        {
            o<<nfile+1<<nrank;
            auto takepos = b->get_from_token_const(o.str());
            if(takepos->occupier)
            {
                Move mv(p,(Position*) takepos);
                m.push_back(mv);
            }
        }
    }
    return m;
}

//Rook
Rook::Rook(int c): Piece(c)
{
    type="Rook";
    value = 5;
}

std::vector<Move> Rook::moves(Position* p,const std::vector<Position>& b) const
{
    //stub
    return {};
}

//Knight
Knight::Knight(int c): Piece(c)
{
    type="Knight";
    value = 3;
}

std::vector<Move> Knight::moves(Position* p,const std::vector<Position>& b) const
{
    //stub
    return {};
}

//Bishop
Bishop::Bishop(int c): Piece(c)
{
    type="Bishop";
    value = 3;
}

std::vector<Move> Bishop::moves(Position* p,const std::vector<Position>& b) const
{
    //stub
    return {};
}

//Queen
Queen::Queen(int c): Piece(c)
{
    type="Queen";
    value = 9;
}

std::vector<Move> Queen::moves(Position* p,const std::vector<Position>& b) const
{
    //stub
    return {};
}

//King
King::King(int c): Piece(c)
{
    type="King";
    value = 1000;
}

std::vector<Move> King::moves(Position* p,const std::vector<Position>& b) const
{
    //stub
    return {};
}