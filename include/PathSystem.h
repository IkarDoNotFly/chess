#pragma once

#include "Figure.h"
#include "Point.h"

#include <list>
#include <map>
#include <memory>

class PathSystem {
    PFigures board;
    PFigure at(const PPoint& point) const;
    PPoint addOrDie(const PPoint& point, FigurePlayer side, bool pawnMode) const;
    PPoints buildPawnPath(const PFigure& figure) const;
    PPoints buildKnightPath(const PFigure& figure) const;
    PPoints buildRookPath(const PFigure& figure) const;
    PPoints buildBishopPath(const PFigure& figure) const;
    PPoints buildKingPath(const PFigure& figure) const;
    std::multimap<PFigure, PPoint> getRawListOfMoves(FigurePlayer side) const;
    PFigure getKing(FigurePlayer side) const;

public:
    PathSystem();
    explicit PathSystem(const PFigures& board);
    PPoints buildPath(const PFigure& figure) const;
    const PFigures& getBoard() const;
    void setBoard(const PFigures& list);
    // returns true if move can be made
    bool checkForMovement(const PFigure& from, const PPoint& to) const;
    PPoints checkForAnyMovement(const PFigure& from) const;
    std::multimap<PFigure, PPoint> getListOfAvailableMoves(FigurePlayer side) const;
    bool checkCastling(const PFigure& one, const PFigure& two) const;
};

typedef std::shared_ptr<PathSystem> PPathSystem;
