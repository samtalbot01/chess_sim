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

struct Position
{
    char file;
    int rank;
    Piece* occupier;
    std::string token;
    Position(char,int);
    bool operator== (const Position&) const; //equality given pos struct
    bool operator== (const std::string&) const; //equality given token string
};


struct Move
{
    Position* end;
    Position* start;
    int value;
    Move(Position*,Position*,int);
};

class Piece
{
    public:
        Piece(int);
        virtual std::vector<Move> moves(Position*,Board*) const {return {};};
        std::string get_type() const {return type;};
        std::string get_full_name() const;
        int get_colour() const {return colour;};
        int get_value() const {return value;};
    protected:
        std::string type;
        Board* board;
        int value;
    private:
        int colour;
};

class Board
{
    private:
        std::vector<Position> positions;
        std::vector<Piece*> pieces;
        Position* get_from_token(std::string);
    public:
        Board(int);
        Position* find(Piece*); //todo
        const std::vector<Position> &get_positions() const;
        std::string to_string() const;
        void add_piece(Piece*,Position*); //todo
        void add_piece(Piece*,std::string); //todo
       // void make_move(Move);
        
};


#endif