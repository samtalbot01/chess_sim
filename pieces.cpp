#include "pieces.h"
#include <sstream>
//Pawn
Pawn::Pawn(int c): Piece(c)
{
    type="Pawn";
    value = 1;
}

std::vector<Move> Pawn::moves(Position* p,Board* b) const
{
    std::vector<Move> m;
    //White side movements (this is only for pawns) 
    if(get_colour()==W)
    {
        //forward moves
        auto e0 = b->traverse(p,0,1);
        if(e0)
            if(!e0->occupier)
            {
                Move mv0(p,e0);
                m.push_back(mv0);
                if(p->rank==2)
                {
                    auto e1 = b->traverse(p,0,2);
                    if(!e1->occupier)
                    {
                        Move mv1(p,e1);
                        m.push_back(mv1);
                    }
                }
            }
        
        //takes
        auto e2 = b->traverse(p,1,1);
        auto e3 = b->traverse(p,-1,1);
        if(e2)
            if(e2->occupier)
                if(e2->occupier->get_colour()!=get_colour())
                {
                    Move mv2(p,e2);
                    m.push_back(mv2);
                }
        if(e3)
            if(e3->occupier)
                if(e3->occupier->get_colour()!=get_colour())
                {
                    Move mv3(p,e3);
                    m.push_back(mv3);
                }
    }
    else
    {
        //BLACK MOVEMENTS
        auto e0 = b->traverse(p,0,-1);
        if(e0)
            if(!e0->occupier)
            {
                Move mv0(p,e0);
                m.push_back(mv0);
                if(p->rank==7)
                {
                    auto e1 = b->traverse(p,0,-2);
                    if(!e1->occupier)
                    {
                        Move mv1(p,e1);
                        m.push_back(mv1);
                    }
                }
            }
        
        //takes
        auto e2 = b->traverse(p,1,-1);
        auto e3 = b->traverse(p,-1,-1);
        if(e2)
            if(e2->occupier)
                if(e2->occupier->get_colour()!=get_colour())
                {
                    Move mv2(p,e2);
                    m.push_back(mv2);
                }
        if(e3)
            if(e3->occupier)
                if(e3->occupier->get_colour()!=get_colour())
                {
                    Move mv3(p,e3);
                    m.push_back(mv3);
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

std::vector<Move> Rook::moves(Position* p,Board* b) const
{
    std::vector<Move> m;

    //upwards traverse
    int increment = 1;
    while (b->traverse(p,0,increment))
    {
        Position* endp = b->traverse(p,0,increment);
        if (Board::process_move(p, endp, m))
            break;
        increment++;
    }
    
    //Downwards
    increment = -1;
    while (b->traverse(p,0,increment))
    {
        Position* endp = b->traverse(p,0,increment);
        if (Board::process_move(p, endp, m))
            break;
        increment--;
    }

    //Right
    increment=1;
    while (b->traverse(p,increment,0))
    {
        Position* endp = b->traverse(p,increment,0);
        if (Board::process_move(p, endp, m))
            break;
        increment++;
    }

    //Left
    increment = -1;
    while (b->traverse(p,increment,0))
    {
        Position* endp = b->traverse(p,increment,0);
        if (Board::process_move(p, endp, m))
            break;
        increment--;
    }
    return m;
}

//Knight
Knight::Knight(int c): Piece(c)
{
    type="Knight";
    value = 3;
}

std::vector<Move> Knight::moves(Position* p,Board* b) const
{
    std::vector<Move> m;

    //top fork
    auto endpu = b->traverse(p,1,2);
    Board::process_move(p,endpu,m);
    auto endpu2 = b->traverse(p,-1,2);
    Board::process_move(p,endpu2,m);

    //down
    auto endpd = b->traverse(p,1,-2);
    Board::process_move(p,endpd,m);
    auto endpd2 = b->traverse(p,-1,-2);
    Board::process_move(p,endpd2,m);

    //Left
    auto endpl = b->traverse(p,-2,1);
    Board::process_move(p,endpl,m);
    auto endpl2 = b->traverse(p,-2,-1);
    Board::process_move(p,endpl2,m);

    //Right
    auto endpr = b->traverse(p,2,1);
    Board::process_move(p,endpr,m);
    auto endpr2 = b->traverse(p,2,-1);
    Board::process_move(p,endpr2,m);

    return m;
}

//Bishop
Bishop::Bishop(int c): Piece(c)
{
    type="Bishop";
    value = 3;
}

std::vector<Move> Bishop::moves(Position* p,Board* b) const
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

std::vector<Move> Queen::moves(Position* p,Board* b) const
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

std::vector<Move> King::moves(Position* p,Board* b) const
{
    //stub
    return {};
}

//Extra
