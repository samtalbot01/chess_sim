#include "chess.h"
#include "pieces.h"
#include <iostream>

int main(int argc,char** argv)
{
    Board b(STANDARD);
    std::cout << b.to_string();;
    return 0;
}