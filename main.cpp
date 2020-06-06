#include "chess.h"
#include "pieces.h"
#include <iostream>

int main(int argc,char** argv)
{
    Board b(STANDARD);

    std::string s;
    while(std::getline(std::cin,s))
    {
        auto mv = b.parse_move(s);
        if(!mv)
        {
            std::cout<<"not a move bro"<<std::endl;
        }
        else
            b.make_move(mv);
        std::cout<<b.to_string()<<std::endl;
    }
    //b.destroy();
    return 0;
}
