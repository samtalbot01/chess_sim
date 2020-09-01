#include "engine.h"
#include "chess.h"
#include <iostream>

int main()
{
    Board b(STANDARD);
    eng::ChessEngine ce(&b,W,3);

    std::cout<<ce.get_move()<<std::endl;

    return 0;
}