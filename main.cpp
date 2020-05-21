#include "chess.h"
#include <iostream>
int main()
{
    Board b(STANDARD);
    std::cout << b.to_string();
    return 0;
}