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
    Move(Position*,Position*);
};

class Piece
{
    public:
        Piece(int);
        virtual std::vector<Move> moves(Position*,Board* b) const {return {};};
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
        Position* find(Position&);
    public:
        Board(int);
        ~Board();
        Position* find(Piece*);
        const std::vector<Position> &get_positions() const;
        std::string to_string() const;
        int add_piece(Piece*,Position*);
        int add_piece(Piece*,std::string); 
        int make_move(Move);
        //bool is_valid(Move);
        Position* traverse(Position* ,int,int);
        

};


#endif