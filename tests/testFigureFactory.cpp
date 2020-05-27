

#include <Figure.h>
#include <FigureFactory.h>
#include <Point.h>
#include <gtest/gtest.h>

using namespace std;

TEST(FigureFactory, Creates8Pawns)
{
    auto whitePawns = FigureFactory::buildPawns(FigurePlayer::Whites);
    auto blackPawns = FigureFactory::buildPawns(FigurePlayer::Blacks);

    ASSERT_EQ(whitePawns.size(), 8);
    ASSERT_EQ(blackPawns.size(), 8);
}

TEST(FigureFactory, CorrectWhitePawnPlacement)
{
    auto whitePawns = FigureFactory::buildPawns(FigurePlayer::Whites);

    int x = 0;
    for (auto i : whitePawns) {
        ASSERT_EQ(i->getPoint()->getX(), x);
        ASSERT_EQ(i->getPoint()->getY(), 1);
        ASSERT_EQ(i->getMovesCount(), 0);
        ASSERT_EQ(i->getPlayer(), FigurePlayer::Whites);
        ASSERT_EQ(i->getType(), FigureType::Pawn);
        ASSERT_EQ(i->getKilledBy(), nullptr);
        x++;
    }
}

TEST(FigureFactory, CorrectBlackPawnPlacement)
{
    auto blackPawns = FigureFactory::buildPawns(FigurePlayer::Blacks);

    int x = 0;
    for (auto i : blackPawns) {
        ASSERT_EQ(i->getPoint()->getX(), x);
        ASSERT_EQ(i->getPoint()->getY(), 6);
        ASSERT_EQ(i->getMovesCount(), 0);
        ASSERT_EQ(i->getPlayer(), FigurePlayer::Blacks);
        ASSERT_EQ(i->getType(), FigureType::Pawn);
        ASSERT_EQ(i->getKilledBy(), nullptr);
        x++;
    }
}
