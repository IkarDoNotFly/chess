#pragma once

#include "Chessboard.h"
#include "Figure.h"
#include "Point.h"
#include "Saver.h"
#include "ViewSide.h"

#include <memory>
#include <set>

class Game {
    PViewSide view;
    PSaver saver;
    PChessboard checkboard;

    PFigure selectFigure(const std::set<PFigure>& set);

public:
    Game(PViewSide viewSide, PSaver saver);

    ~Game();

    bool run();
};
