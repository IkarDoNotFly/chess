#pragma once

#include "Point.h"

#include <memory>

enum FigureType : int { Pawn = 0, Rook, Knight, Bishop, Queen, King };

enum FigurePlayer : int { Whites = 0, Blacks };

class Figure;

typedef std::shared_ptr<Figure> PFigure;
typedef std::list<PFigure> PFigures;

/// Figure class
class Figure {
    PPoint position;
    PFigure killedBy;
    FigurePlayer player;
    FigureType type;
    unsigned int movesMade;

public:
    Figure(
        Point point,
        FigureType type,
        FigurePlayer player,
        unsigned int movesMade = 0,
        PFigure killedBy = nullptr);
    Figure(const Figure& figure);
    Figure& operator=(const Figure& b);
    ~Figure();
    void isCapturedBy(const PFigure& by);
    void revive();
    char asChar() const;
    bool isAlive() const;
    bool isReadyForCastling() const;
    bool isPawn() const;
    bool isRook() const;
    bool isKnight() const;
    bool isBishop() const;
    bool isQueen() const;
    bool isKing() const;
    FigureType getType() const;
    FigurePlayer getPlayer() const;
    PPoint getPoint() const;
    int getX() const; // point alias
    int getY() const; // point alias
    PFigure getKilledBy() const;
    void moved();
    unsigned int getMovesCount() const;
    bool operator==(const Figure& figure) const;
    bool operator!=(const Figure& figure) const;
};
