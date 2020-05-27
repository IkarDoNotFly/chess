

#include <Chessboard.h>
#include <Figure.h>
#include <FigureFactory.h>
#include <Point.h>
#include <gtest/gtest.h>

using namespace std;

typedef PFigure fig;

TEST(Chessboard, Initialize16Pawns)
{
    Chessboard c;

    c.initialize();

    int blackPawn = 0;
    int whitePawn = 0;

    for (const auto& i : c.getBoard()) {
        if (!i->isPawn())
            continue;
        if (i->getPlayer() == FigurePlayer::Whites)
            whitePawn++;
        else
            blackPawn++;
    }

    ASSERT_EQ(blackPawn, 8);
    ASSERT_EQ(whitePawn, 8);
}

TEST(Chessboard, Initialize4Rooks)
{
    Chessboard c;

    c.initialize();

    int blackRook = 0;
    int whiteRook = 0;

    for (const auto& i : c.getBoard()) {
        if (!i->isRook())
            continue;
        if (i->getPlayer() == FigurePlayer::Whites)
            whiteRook++;
        else
            blackRook++;
    }

    ASSERT_EQ(blackRook, 2);
    ASSERT_EQ(whiteRook, 2);
}

TEST(Chessboard, Initialize4Knights)
{
    Chessboard c;

    c.initialize();

    int blackKnight = 0;
    int whiteKnight = 0;

    for (const auto& i : c.getBoard()) {
        if (!i->isKnight())
            continue;
        if (i->getPlayer() == FigurePlayer::Whites)
            whiteKnight++;
        else
            blackKnight++;
    }

    ASSERT_EQ(blackKnight, 2);
    ASSERT_EQ(whiteKnight, 2);
}

TEST(Chessboard, Initialize4Bishops)
{
    Chessboard c;

    c.initialize();

    int blackBishops = 0;
    int whiteBishops = 0;

    for (const auto& i : c.getBoard()) {
        if (!i->isBishop())
            continue;
        if (i->getPlayer() == FigurePlayer::Whites)
            whiteBishops++;
        else
            blackBishops++;
    }

    ASSERT_EQ(blackBishops, 2);
    ASSERT_EQ(whiteBishops, 2);
}

TEST(Chessboard, Initialize2Queens)
{
    Chessboard c;

    c.initialize();

    bool blackQueen = false;
    bool whiteQueen = false;

    for (const auto& i : c.getBoard()) {
        if (!i->isQueen())
            continue;
        if (i->getPlayer() == FigurePlayer::Whites)
            whiteQueen = true;
        else
            blackQueen = true;
    }

    ASSERT_TRUE(whiteQueen);
    ASSERT_TRUE(blackQueen);
}

TEST(Chessboard, Initialize2Kings)
{
    Chessboard c;

    c.initialize();

    bool blackKing = false;
    bool whiteKing = false;

    for (const auto& i : c.getBoard()) {
        if (!i->isQueen())
            continue;
        if (i->getPlayer() == FigurePlayer::Whites)
            whiteKing = true;
        else
            blackKing = true;
    }

    ASSERT_TRUE(whiteKing);
    ASSERT_TRUE(blackKing);
}

TEST(Chessboard, TryReachFigureByPoint)
{
    Chessboard c;

    c.initialize();

    auto blackPawnSpot = make_shared<Point>(0, 6);
    auto blackPawn = c.at(blackPawnSpot);
    ASSERT_NE(blackPawn, nullptr);
}

TEST(Chessboard, TryReachNonExistingFigureByPoint)
{
    Chessboard c;

    c.initialize();

    auto uselessSpot = make_shared<Point>(4, 4);
    auto nothing = c.at(uselessSpot);
    ASSERT_EQ(nothing, nullptr);
}

class PawnReachesEndOfBoard : public ::testing::Test {
public:
    FigurePlayer allySide;
    FigurePlayer enemySide;
    Chessboard c;
    PPoint destinationPoint;
    fig pawn;
    fig deadQueen;
    fig deadRook;

    void SetUp() override
    {
        allySide = Blacks;
        enemySide = Whites;
        c.addFigure(FigureFactory::buildKing(allySide));
        c.addFigure(FigureFactory::buildKing(enemySide));

        pawn = make_shared<Figure>(Point(2, 1), Pawn, allySide);
        destinationPoint = make_shared<Point>(2, 0);
        c.addFigure(pawn);
        deadQueen = make_shared<Figure>(Point(1, 1), Queen, allySide);
        deadRook = make_shared<Figure>(Point(1, 2), Rook, allySide);

        deadQueen->isCapturedBy(pawn);
        deadRook->isCapturedBy(pawn);
    }
};

TEST_F(PawnReachesEndOfBoard, GetQueenIfOnlyQueenIsDead)
{
    c.addDeadFigure(deadQueen);
    ASSERT_TRUE(c.prepareMove(pawn->getPoint(), destinationPoint));
    ASSERT_FALSE(pawn->isAlive());
    ASSERT_TRUE(deadQueen->isAlive());
    ASSERT_EQ(*deadQueen->getPoint(), *destinationPoint);
}

TEST_F(PawnReachesEndOfBoard, GetQueenIfQueenAndRookAreDead)
{
    c.addDeadFigure(deadQueen);
    c.addDeadFigure(deadRook);
    ASSERT_TRUE(pawn->isAlive());

    ASSERT_TRUE(c.prepareMove(pawn->getPoint(), destinationPoint));

    ASSERT_FALSE(pawn->isAlive());
    ASSERT_EQ(*pawn->getKilledBy(), *deadQueen);
    ASSERT_TRUE(deadQueen->isAlive());
    ASSERT_FALSE(deadRook->isAlive());
    ASSERT_EQ(*deadQueen->getPoint(), *destinationPoint);
}

TEST_F(PawnReachesEndOfBoard, GetQueenIfNoneAllyIsDead)
{
    c.addDeadFigure(make_shared<Figure>(Point(1, 1), Knight, enemySide));
    ASSERT_TRUE(c.prepareMove(pawn->getPoint(), destinationPoint));
    auto newCreature = c.getBoard().back();
    ASSERT_FALSE(pawn->isAlive());
    ASSERT_EQ(c.getBoard().size(), 3); // new queen + 2 kings
    ASSERT_TRUE(newCreature->isAlive());
    ASSERT_EQ(*newCreature->getPoint(), *destinationPoint);
    ASSERT_TRUE(newCreature->isQueen());
}

TEST_F(PawnReachesEndOfBoard, GetQueenIfNobodyIsDead)
{
    ASSERT_TRUE(c.prepareMove(pawn->getPoint(), destinationPoint));
    auto newCreature = c.getBoard().back();
    ASSERT_FALSE(pawn->isAlive());
    ASSERT_EQ(c.getBoard().size(), 3);
    ASSERT_TRUE(newCreature->isAlive());
    ASSERT_EQ(*newCreature->getPoint(), *destinationPoint);
    ASSERT_TRUE(newCreature->isQueen());
}

TEST(PawnReachesTheEnd, AndCapturesEnemy)
{
    auto allySide = Blacks, enemySide = Whites;
    Chessboard c;
    c.addFigure(FigureFactory::buildKing(allySide));
    c.addFigure(FigureFactory::buildKing(enemySide));

    auto pawn = make_shared<Figure>(Point(2, 1), Pawn, allySide);
    auto destinationPoint = make_shared<Point>(1, 0);
    auto enemyRook = make_shared<Figure>(*destinationPoint, Rook, enemySide);

    c.addFigure(enemyRook);
    c.addFigure(pawn);

    ASSERT_TRUE(c.prepareMove(pawn->getPoint(), destinationPoint));
    auto newCreature = c.getBoard().back();
    ASSERT_FALSE(pawn->isAlive());
    ASSERT_FALSE(enemyRook->isAlive());
    ASSERT_EQ(c.getBoard().size(), 3);
    ASSERT_TRUE(newCreature->isAlive());
    ASSERT_EQ(*newCreature->getPoint(), *destinationPoint);
    ASSERT_TRUE(newCreature->isQueen());
    ASSERT_EQ(newCreature->getPlayer(), allySide);
}
