#include <Figure.h>
#include <PathSystem.h>
#include <Point.h>

#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <stdexcept>

using namespace std;

PathSystem::PathSystem(const PFigures& b)
    : board(b)
{
}

PathSystem::PathSystem(){};

PPoints PathSystem::buildPath(const PFigure& figure) const
{
    if (!figure)
        throw invalid_argument("Cannot build path for nullptr");

    PPoints rawMoves;

    // build possible path for different figure types
    if (figure->isPawn())
        rawMoves.splice(rawMoves.end(), buildPawnPath(figure));

    if (figure->isRook() || figure->isQueen())
        rawMoves.splice(rawMoves.end(), buildRookPath(figure));

    if (figure->isKnight())
        rawMoves.splice(rawMoves.end(), buildKnightPath(figure));

    if (figure->isBishop() || figure->isQueen())
        rawMoves.splice(rawMoves.end(), buildBishopPath(figure));

    if (figure->isKing()) {
        rawMoves.splice(rawMoves.end(), buildKingPath(figure));
    }

    /// there may be so many of them, not really want to break any iterators
    PPoints possibleMoves;
    for (const auto& i : rawMoves)
        if (i)
            possibleMoves.push_back(i);

    return possibleMoves;
}

PPoint PathSystem::addOrDie(const PPoint& p, FigurePlayer side, bool pawnMode) const
{
    if (!p)
        return nullptr;

    auto fig = at(p);
    bool differentSides = fig && fig->getPlayer() != side;
    // pawns can capture on diagonals but not vertically
    bool allowNext
        = p->inBounds() && (pawnMode ? (fig && differentSides) : (!fig || differentSides));

    return allowNext ? p : nullptr;
}

PPoints PathSystem::buildPawnPath(const PFigure& figure) const
{
    PPoints path;
    int x = figure->getPoint()->getX(), y = figure->getPoint()->getY();
    auto side = figure->getPlayer();

    auto pawnY = side == FigurePlayer::Whites ? 1 : -1;

    auto p = addOrDie(make_shared<Point>(x, y + pawnY), side,
                      false); // cannot attack forward
    if (p && !at(p)) {
        path.push_back(p);
        if (figure->getMovesCount() == 0)
            path.push_back(addOrDie(make_shared<Point>(x, y + 2 * pawnY), side, false));
    }

    path.push_back(addOrDie(make_shared<Point>(x + 1, y + pawnY), side, true));
    path.push_back(addOrDie(make_shared<Point>(x - 1, y + pawnY), side, true));

    return path;
}

PPoints PathSystem::buildKnightPath(const PFigure& figure) const
{
    PPoints path;
    int x = figure->getPoint()->getX(), y = figure->getPoint()->getY();
    auto side = figure->getPlayer();

    /// to the right
    path.push_back(addOrDie(make_shared<Point>(x + 2, y + 1), side, false));
    path.push_back(addOrDie(make_shared<Point>(x + 2, y - 1), side, false));

    /// to the left
    path.push_back(addOrDie(make_shared<Point>(x - 2, y + 1), side, false));
    path.push_back(addOrDie(make_shared<Point>(x - 2, y - 1), side, false));

    /// to the top
    path.push_back(addOrDie(make_shared<Point>(x + 1, y + 2), side, false));
    path.push_back(addOrDie(make_shared<Point>(x - 1, y + 2), side, false));

    /// to the bottom
    path.push_back(addOrDie(make_shared<Point>(x + 1, y - 2), side, false));
    path.push_back(addOrDie(make_shared<Point>(x - 1, y - 2), side, false));

    return path;
}

PPoints PathSystem::buildRookPath(const PFigure& figure) const
{
    PPoints path;
    int x = figure->getPoint()->getX(), y = figure->getPoint()->getY();
    auto side = figure->getPlayer();
    /// to the right
    for (int i = x + 1; i < 8; ++i) {
        auto p = addOrDie(make_shared<Point>(i, y), side, false);
        if (!p)
            break;
        path.push_back(p);
        auto f = at(p);
        if (f)
            break; // we cannot move through figures
    }

    /// to the left
    for (int i = x - 1; i >= 0; --i) {
        auto p = addOrDie(make_shared<Point>(i, y), side, false);
        if (!p)
            break;
        path.push_back(p);
        auto f = at(p);
        if (f)
            break; // we cannot move through figures
    }

    /// to the top
    for (int i = y + 1; i < 8; ++i) {
        auto p = addOrDie(make_shared<Point>(x, i), side, false);
        if (!p)
            break;
        path.push_back(p);
        auto f = at(p);
        if (f)
            break; // we cannot move through figures
    }

    /// to the bottom
    for (int i = y - 1; i >= 0; --i) {
        auto p = addOrDie(make_shared<Point>(x, i), side, false);
        if (!p)
            break;
        path.push_back(p);
        auto f = at(p);
        if (f)
            break; // we cannot move through figures
    }

    /// check castling

    auto king = side == FigurePlayer::Whites ? at(make_shared<Point>(4, 0))
                                             : at(make_shared<Point>(4, 7));

    if (checkCastling(figure, king))
        path.push_back(make_shared<Point>(king->getX(), y));

    // return
    return path;
}

PPoints PathSystem::buildBishopPath(const PFigure& figure) const
{
    PPoints path;
    int x = figure->getPoint()->getX(), y = figure->getPoint()->getY();
    auto side = figure->getPlayer();

    bool good = true;
    /// to the right-top
    for (int i = x + 1, j = y + 1; j < 8 && i < 8 && good; ++i, ++j) {
        auto p = addOrDie(make_shared<Point>(i, j), side, false);
        path.push_back(p);
        good = !!p ? !at(p) : false; // we cannot move through figures
    }

    good = true;
    /// to the left-top
    for (int i = x - 1, j = y + 1; j < 8 && i >= 0 && good; --i, ++j) {
        auto p = addOrDie(make_shared<Point>(i, j), side, false);
        path.push_back(p);
        good = !!p ? !at(p) : false; // we cannot move through figures
    }

    good = true;
    /// to the right-bottom
    for (int i = x + 1, j = y - 1; j >= 0 && i < 8 && good; ++i, --j) {
        auto p = addOrDie(make_shared<Point>(i, j), side, false);
        path.push_back(p);
        good = !!p ? !at(p) : false; // we cannot move through figures
    }

    good = true;
    /// to the left-bottom
    for (int i = x - 1, j = y - 1; j >= 0 && i >= 0 && good; --i, --j) {
        auto p = addOrDie(make_shared<Point>(i, j), side, false);
        path.push_back(p);
        good = !!p ? !at(p) : false; // we cannot move through figures
    }

    return path;
}

PPoints PathSystem::buildKingPath(const PFigure& figure) const
{
    PPoints path;
    int x = figure->getPoint()->getX(), y = figure->getPoint()->getY();
    auto side = figure->getPlayer();

    path.push_back(addOrDie(make_shared<Point>(x + 1, y), side, false));
    path.push_back(addOrDie(make_shared<Point>(x - 1, y), side, false));

    path.push_back(addOrDie(make_shared<Point>(x + 1, y + 1), side, false));
    path.push_back(addOrDie(make_shared<Point>(x - 1, y + 1), side, false));
    path.push_back(addOrDie(make_shared<Point>(x - 1, y - 1), side, false));
    path.push_back(addOrDie(make_shared<Point>(x + 1, y - 1), side, false));

    path.push_back(addOrDie(make_shared<Point>(x, y + 1), side, false));
    path.push_back(addOrDie(make_shared<Point>(x, y - 1), side, false));

    auto rook1 = side == FigurePlayer::Whites ? at(make_shared<Point>(0, 0))
                                              : at(make_shared<Point>(0, 7));
    auto rook2 = side == FigurePlayer::Whites ? at(make_shared<Point>(7, 0))
                                              : at(make_shared<Point>(7, 7));

    if (rook1 && checkCastling(figure, rook1))
        path.push_back(make_shared<Point>(x - 2, y));

    if (rook2 && checkCastling(figure, rook2))
        path.push_back(make_shared<Point>(x + 2, y));

    return path;
}

bool PathSystem::checkCastling(const PFigure& one, const PFigure& two) const
{
    if (!one || !one->isReadyForCastling() || !two
        || !two->isReadyForCastling() /// not ready for castling
        || one->getPlayer() != two->getPlayer() || /// different sides
        (*one == *two && *one->getPoint() == *two->getPoint())) /// two same figures
        return false; /// no castling
    PFigure rook;
    PFigure king;

    if (one->isRook() && two->isKing()) {
        rook = one;
        king = two;
    } else if (two->isRook() && one->isKing()) {
        king = one;
        rook = two;
    } else
        return false; /// no rook & king - no castling

    bool castlingPathClear = true;

    auto kingX = king->getX();
    auto rookX = rook->getX();

    auto point = make_shared<Point>(0, king->getY());
    for (auto i = min(kingX + 1, rookX + 1); i < max(kingX, rookX); ++i) {
        point->setX(i);
        if (!at(point))
            continue;
        castlingPathClear = false;
        /// tmp is an obstacle for castling
        break;
    }

    return castlingPathClear;
}

PFigure PathSystem::at(const PPoint& point) const
{
    if (!point || !point->inBounds())
        return nullptr;

    for (const auto& item : board)
        if (*(item->getPoint()) == *point)
            return item;
    return nullptr;
}

const PFigures& PathSystem::getBoard() const
{
    return board;
}

void PathSystem::setBoard(const PFigures& list)
{
    board = list;
}

PPoints PathSystem::checkForAnyMovement(const PFigure& from) const
{
    if (!from)
        return {};
    return buildPath(from);
}

bool PathSystem::checkForMovement(const PFigure& figure, const PPoint& to) const
{
    if (!figure || !to)
        return false;

    auto possibleMoves = checkForAnyMovement(figure);

    // after we got path we perform actual movement if final point is on path
    bool finalOnPath = false;
    for (const auto& i : possibleMoves)
        if (*to == *i) {
            finalOnPath = true;
            break;
        }
    if (!finalOnPath)
        return false;

    auto possibleFigure = at(to);
    if (possibleFigure && possibleFigure->isKing()) // king cannot be killed
        return false;

    auto moves = getListOfAvailableMoves(figure->getPlayer());

    for (const auto& i : moves)
        if (*i.first == *figure)
            if (*i.second == *to)
                return true;

    return false;
}

multimap<PFigure, PPoint> PathSystem::getRawListOfMoves(FigurePlayer side) const
{
    // ally & enemy figures
    set<PFigure> allies, enemies;
    PFigure ourKing;

    for (const auto& i : board) {
        if (!i->isAlive())
            continue;
        if (i->getPlayer() == side) {
            allies.insert(i);
            if (i->isKing())
                ourKing = i;
        } else
            enemies.insert(i);
    }

    if (!ourKing) { // Are we in testing mode?
        throw runtime_error("two kings must be at board!");
    }

    // build moves map
    set<PPoint> interceptionPoint;
    multimap<PFigure, PPoint> allyForces;

    // trace back method
    auto traceBack = [&](const PFigure& figure) -> PPoints {
        auto destinyPoint = figure->getPoint();
        if (figure->isKnight())
            return {destinyPoint}; // we cannot block knight's checkmate

        long dx = (long)ourKing->getPoint()->getX() - destinyPoint->getX(),
             dy = (long)ourKing->getPoint()->getY() - destinyPoint->getY();

        int enemyAboveKing = dy < 0 ? 1 : dy == 0 ? 0 : -1;
        int enemyOnTheRight = dx < 0 ? 1 : dx == 0 ? 0 : -1;

        PPoints tracedPath;
        PPoint point = make_shared<Point>(ourKing->getPoint()->getX(), ourKing->getPoint()->getY());
        while (*point != *destinyPoint) {
            point->shift(enemyOnTheRight, enemyAboveKing);
            tracedPath.push_back(make_shared<Point>(*point));
        }
        return tracedPath;
    };

    for (const auto& i : enemies)
        // look for our king's position
        for (const auto& pos : buildPath(i))
            if (*pos == *ourKing->getPoint()) {
                // trace back path from king to attacker
                auto tracedPoints = traceBack(i);
                interceptionPoint.insert(tracedPoints.begin(), tracedPoints.end());
                break;
            }

    for (const auto& i : allies) {
        auto path = buildPath(i); // look for protection

        for (const auto& pos : path) {
            bool isInWanted
                = interceptionPoint.empty(); // if no checkmate set - we want all the moves
            // look for 'pos' in interceptionPoints
            if (!isInWanted) {
                for (const auto& want : interceptionPoint) {
                    isInWanted = i->isKing() ? (!!at(want)) : (*want == *pos);
                    if (isInWanted)
                        break;
                }
            }

            if (isInWanted)
                allyForces.insert({i, pos});
        }
    }
    return allyForces;
}

multimap<PFigure, PPoint> PathSystem::getListOfAvailableMoves(FigurePlayer side) const
{
    auto oppositeSide = side == Whites ? Blacks : Whites;
    auto allyForces = getRawListOfMoves(side);

    // simulation of one turn

    auto king = getKing(side);
    if (!king)
        throw runtime_error("two kings must be at board!");

    multimap<PFigure, PPoint> filteredAllies, doubleFilteredAllies;

    for (const auto& i : allyForces) {
        const auto& figure = i.first;
        const auto& spot = i.second;
        const auto figurePos = make_shared<Point>(*figure->getPoint());

        auto possibleFigure = at(spot);
        if (possibleFigure)
            possibleFigure->isCapturedBy(figure);

        figure->getPoint()->setX(spot->getX());
        figure->getPoint()->setY(spot->getY());

        bool futureBlock = false;
        auto enemyTurns = getRawListOfMoves(oppositeSide);

        for (const auto& enemyPair : enemyTurns) {
            auto enemyFigure = enemyPair.first;
            auto enemyTurn = enemyPair.second;
            if (*enemyTurn == *king->getPoint()) {
                futureBlock = true;
                break;
            }
        }

        if (!futureBlock)
            filteredAllies.insert({figure, spot});

        if (possibleFigure)
            possibleFigure->revive();
        figure->getPoint()->setX(figurePos->getX());
        figure->getPoint()->setY(figurePos->getY());
    }

    const auto leftCastlePoint = Point(king->getX() - 2, king->getY());
    const auto rightCastlePoint = Point(king->getX() + 2, king->getY());
    bool kingCanCastleLeft = false, kingCanCastleRight = false;

    for (const auto& i : filteredAllies)
        if (*i.first == *king && *(i.first->getPoint()) == *king->getPoint()) {
            if (*i.second == rightCastlePoint)
                kingCanCastleRight = true;
            else if (*i.second == leftCastlePoint)
                kingCanCastleLeft = true;
        }

    for (const auto& i : filteredAllies) {
        const auto& figure = i.first;
        const bool kingCanCastle
            = figure->getX() < king->getX() ? kingCanCastleLeft : kingCanCastleRight;
        const bool isKingNow = *i.first == *king && *(i.first->getPoint()) == *(king->getPoint());
        const bool toInsert = isKingNow
            || (figure->isReadyForCastling() ? checkCastling(figure, king) && kingCanCastle : true);
        if (i.second && toInsert)
            doubleFilteredAllies.insert(i);
    }

    return doubleFilteredAllies;
}

PFigure PathSystem::getKing(FigurePlayer side) const
{
    for (const auto& i : board)
        if (i->getPlayer() == side)
            if (i->isKing())
                return i;
    return nullptr;
}
