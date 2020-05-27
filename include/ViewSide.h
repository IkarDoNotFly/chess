#pragma once

#include "Chessboard.h"
#include "Figure.h"
#include "Point.h"

#include <list>
#include <memory>
#include <set>
#include <string>

class ViewSide {
    int inputAction(int lowBounds, int highBounds) const;
public:
    void renderText(const std::string& str) const;
    void renderFigures(const PChessboard& checkboard) const;
    int askForAction(bool b, const std::list<std::string>& actions) const;
    PPoint getPoint(const std::string& message) const;
    void renderKillText(char victim, char killer) const;
    void renderSelectedInfo(const PFigure& Figure) const;
    void renderMayGoToPath(const PPoints& list) const;
    void renderFreeFigures(const std::set<PFigure>& set) const;
};

typedef std::shared_ptr<ViewSide> PViewSide;