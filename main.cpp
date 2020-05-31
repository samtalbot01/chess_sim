#include "chess.h"
#include "pieces.h"
#include <iostream>

int main(int argc,char** argv)
{
    Board b(STANDARD);
    
    //auto mvs = b.all_moves(W);
    //std::cout << mvs.size() << "(number of vecs)" <<std::endl;
    //for(auto& m:mvs)
        //std::cout<<m.size()<<std::endl;
    
    b.destroy();
    return 0;
}
