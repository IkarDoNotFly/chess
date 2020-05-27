
#pragma once

#include "Figure.h"
#include "PathSystem.h"
#include "Point.h"

#include <list>
#include <map>
#include <memory>

class Chessboard {
protected:
    PFigures m_board;
    PFigures m_deadFigures;
    PPathSystem m_pathSystem;
    bool whitesTurn = true;
    void destroy();
    void performMovement(
        const PFigure& figure, const PPoint& toPlace);

public:
    Chessboard();
    ~Chessboard();
    PFigure at(const PPoint& point) const;
    /// returns true if move was successfully made
    bool prepareMove(const PPoint& from, const PPoint& to);
    /// create fresh figures and place them on board
    void initialize();
    void setTurn(bool whitesTurn);
    bool getWhitesTurn() const;
    bool onePlayerLeft() const;
    std::multimap<PFigure, PPoint> canMoveFrom(
        FigurePlayer side) const;
    // save-load needed functions
    explicit Chessboard(const PFigures& figures);
    PFigures getAllFigures() const;
    PFigures getBoard() const;
    void addFigure(PFigure fig);
    void addDeadFigure(PFigure fig);
};

typedef std::shared_ptr<Chessboard> PChessboard;