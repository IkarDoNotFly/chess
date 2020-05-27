#include <Figure.h>
#include <Point.h>

#include <stdexcept>

using namespace std;

Figure::Figure(const Figure& figure)
    : Figure(
          *figure.getPoint(),
          figure.getType(),
          figure.getPlayer(),
          figure.getMovesCount(),
          figure.getKilledBy())
{
}

Figure::Figure(Point a, FigureType b, FigurePlayer c, unsigned int moves, PFigure k)
    : position(make_shared<Point>(a))
    , killedBy(std::move(k))
    , player(c)
    , type(b)
    , movesMade(moves)
{
}

Figure& Figure::operator=(const Figure& b)
{
    position = make_shared<Point>(*b.position.get());
    killedBy = b.killedBy;
    player = b.player;
    type = b.type;
    movesMade = b.movesMade;
    return *this;
}

Figure::~Figure()
{
    killedBy = nullptr;
    position = nullptr;
}

bool Figure::isAlive() const
{
    return killedBy == nullptr;
}

FigureType Figure::getType() const
{
    return type;
}

FigurePlayer Figure::getPlayer() const
{
    return player;
}

PPoint Figure::getPoint() const
{
    return position;
}

PFigure Figure::getKilledBy() const
{
    return killedBy;
}

char Figure::asChar() const
{
    char out = ' ';
    switch (type) {
    case Pawn:
        out = 'p';
        break;
    case Rook:
        out = 'r';
        break;
    case Knight:
        out = 'n';
        break;
    case Bishop:
        out = 'b';
        break;
    case Queen:
        out = 'q';
        break;
    case King:
        out = 'k';
        break;
    }

    return player == Whites ? (char)toupper(out) : out;
}

void Figure::revive()
{
    killedBy = nullptr;
}

unsigned int Figure::getMovesCount() const
{
    return movesMade;
}

void Figure::moved()
{
    ++movesMade;
}

bool Figure::isReadyForCastling() const
{
    return isAlive() && movesMade == 0 && (type == Rook || type == King);
}

bool Figure::isPawn() const
{
    return type == FigureType::Pawn;
}

bool Figure::isRook() const
{
    return type == FigureType::Rook;
}

bool Figure::isKnight() const
{
    return type == FigureType::Knight;
}

bool Figure::isBishop() const
{
    return type == FigureType::Bishop;
}

bool Figure::isQueen() const
{
    return type == FigureType::Queen;
}

bool Figure::isKing() const
{
    return type == FigureType::King;
}

void Figure::isCapturedBy(const PFigure& by)
{
    if (!killedBy)
        killedBy = by;
    else
        throw std::invalid_argument("What is dead may never die");
}

bool Figure::operator==(const Figure& figure) const
{
    return movesMade == figure.getMovesCount() && type == figure.getType()
        && player == figure.getPlayer();
}

bool Figure::operator!=(const Figure& figure) const
{
    return !(*this == figure);
}

int Figure::getX() const
{
    if (!position)
        return -1;
    return (int)position->getX();
}

int Figure::getY() const
{
    if (!position)
        return -1;
    return (int)position->getY();
}
