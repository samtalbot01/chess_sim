#include "chess.h"
#include "pieces.h"
#include <iostream>

int main(int argc,char** argv)
{
    Board b(STANDARD);
    Piece* k = new Knight(B);
    b.add_piece(k,"B6");
    auto mvs = k->moves(b.find(k),&b);
    for(Move& m:mvs)
    {
        std::cout << m.end->token <<": " << m.value << std::endl;
    }
    return 0;
}
