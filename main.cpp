#include "chess.h"
#include "pieces.h"
#include <iostream>

int main(int argc,char** argv)
{
    Board b(EMPTY);
    auto k = new King(W);
    auto r = new Rook(B);
    b.add_piece(k,"A7");
    b.add_piece(r,"A2");
    if(b.check(W))
        std::cout<<"check"<<std::endl;
    else
        std::cout<<"not"<< std::endl;
    
    /*
    std::vector<Move> mv = r->moves(b.find(r),&b);
    std::cout << "aaaaaa : "<<mv.size() << std::endl;
    for(auto m:mv)
        std::cout << m.end->token << std::endl;
    */
    return 0;
}
