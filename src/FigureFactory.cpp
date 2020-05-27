#include <Figure.h>
#include <FigureFactory.h>
#include <Point.h>

using namespace std;

PFigures FigureFactory::buildSide(FigurePlayer side)
{
    PFigures figures; // chessboard consists of 8x8 squares

    figures.splice(figures.end(), buildPawns(side)); /// 8 pawns
    figures.splice(figures.end(), buildRooks(side)); /// 2 rooks
    figures.splice(figures.end(), buildKnights(side)); /// 2 knights
    figures.splice(figures.end(), buildBishops(side)); /// 2 bishops
    figures.push_back(buildQueen(side)); /// one queen
    figures.push_back(buildKing(side)); /// one king

    return figures;
}

PFigures FigureFactory::buildPawns(FigurePlayer side)
{
    PFigures pawns;
    auto pawnY = side == FigurePlayer::Whites ? 1 : 6;
    for (int i = 0; i < 8; i++)
        pawns.push_back(make_shared<Figure>(Point(i, pawnY), FigureType::Pawn, side));

    return pawns;
}

#define BUILD_FIGURES_Y                                                                            \
    ;                                                                                              \
    auto y = side == FigurePlayer::Whites ? 7 : 0; // 7 for whites, 0 for blacks

PFigures FigureFactory::buildRooks(FigurePlayer side)
{
    BUILD_FIGURES_Y;

    return {make_shared<Figure>(Point(0, 7 - y), FigureType::Rook, side),
            make_shared<Figure>(Point(7, 7 - y), FigureType::Rook, side)};
}

PFigures FigureFactory::buildKnights(FigurePlayer side)
{
    BUILD_FIGURES_Y;

    return {make_shared<Figure>(Point(1, 7 - y), FigureType::Knight, side),
            make_shared<Figure>(Point(6, 7 - y), FigureType::Knight, side)};
}

PFigures FigureFactory::buildBishops(FigurePlayer side)
{
    BUILD_FIGURES_Y;

    return {make_shared<Figure>(Point(2, 7 - y), FigureType::Bishop, side),
            make_shared<Figure>(Point(5, 7 - y), FigureType::Bishop, side)};
}

PFigure FigureFactory::buildQueen(FigurePlayer side)
{
    BUILD_FIGURES_Y;

    return make_shared<Figure>(Point(3, 7 - y), FigureType::Queen, side);
}

PFigure FigureFactory::buildKing(FigurePlayer side)
{
    BUILD_FIGURES_Y;

    return make_shared<Figure>(Point(4, 7 - y), FigureType::King, side);
}
