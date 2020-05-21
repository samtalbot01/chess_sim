#ifndef CHESS_HEADER
#define CHESS_HEADER

#include <string>
#include <vector>
#define B 1
#define W -1
#define STANDARD 0
#define EMPTY -1

class Piece;
class Board;

typedef struct
{
    char file;
    int rank;
    Piece* occupier;
} Position;

bool operator==(Position,Position);

typedef struct
{
    Position* end;
    Piece* mover;
    int value;
} Move;

class Piece
{
    public:
        Piece(Position*,Board*,int);
        //virtual std::vector<Move> moves();
        std::string get_type(){return type;};
    protected:
        std::string type;
        Board* board;
    private:
        int colour;
};

class Board
{
    public:
        Board(int);
        //Position* find(Piece*);
        std::vector<Position> positions;
        std::vector<Piece> pieces;
        std::string to_string();
};


#endif