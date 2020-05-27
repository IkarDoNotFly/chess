#pragma once

#include "Figure.h"
#include "Point.h"

#include <list>
#include <memory>

enum FigurePlayer : int;

class FigureFactory {
public:
    static PFigures buildSide(FigurePlayer side);
    static PFigures buildPawns(FigurePlayer side);
    static PFigures buildRooks(FigurePlayer side);
    static PFigures buildKnights(FigurePlayer side);
    static PFigures buildBishops(FigurePlayer side);
    static PFigure buildQueen(FigurePlayer side);
    static PFigure buildKing(FigurePlayer side);
};
