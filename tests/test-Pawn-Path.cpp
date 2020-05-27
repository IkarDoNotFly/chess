

#include <Figure.h>
#include <PathSystem.h>
#include <Point.h>
#include <gtest/gtest.h>
#include <memory>

using std::make_shared;

TEST(Pawn, HasNoMoves)
{
    auto ps = PathSystem();

    auto figure = make_shared<Figure>(Point(4, 1), FigureType::Pawn, FigurePlayer::Whites);

    ps.setBoard({ figure });
    auto path = ps.buildPath(figure);
    ASSERT_EQ(path.size(), 2); // top, x2Top
}

TEST(Pawn, HasSomeMoves)
{
    auto ps = PathSystem();

    auto figure = make_shared<Figure>(Point(4, 1), FigureType::Pawn, FigurePlayer::Whites);
    ps.setBoard({ figure });
    figure->moved();

    auto path = ps.buildPath(figure);
    ASSERT_EQ(path.size(), 1); // top
}

TEST(Pawn, AllyInFront)
{
    auto ps = PathSystem();

    auto point = Point(4, 1);
    auto figure = make_shared<Figure>(point, FigureType::Pawn, FigurePlayer::Whites),
         ally = make_shared<Figure>(
             Point(point.getX(), point.getY() + 1), figure->getType(), figure->getPlayer());

    ps.setBoard({ figure, ally });

    auto path = ps.buildPath(figure);

    ASSERT_TRUE(path.empty()); // no way
}

TEST(Pawn, EnemyInFront)
{
    auto ps = PathSystem();

    auto point = Point(4, 1);
    auto figure = make_shared<Figure>(point, FigureType::Pawn, FigurePlayer::Whites);
    auto enemySide = figure->getPlayer() == FigurePlayer::Whites ? FigurePlayer::Blacks
                                                                 : figure->getPlayer();
    auto enemy = make_shared<Figure>(
        Point(point.getX(), point.getY() + 1), figure->getType(), enemySide);

    ps.setBoard({ figure, enemy });

    auto path = ps.buildPath(figure);

    ASSERT_TRUE(path.empty()); // no way
}

TEST(Pawn, EnemyInFrontRight)
{
    auto ps = PathSystem();

    auto point = Point(4, 1);
    auto figure = make_shared<Figure>(point, FigureType::Pawn, FigurePlayer::Whites);
    auto enemySide = figure->getPlayer() == FigurePlayer::Whites ? FigurePlayer::Blacks
                                                                 : figure->getPlayer();
    auto enemy = make_shared<Figure>(
        Point(point.getX() + 1, point.getY() + 1), figure->getType(), enemySide);

    ps.setBoard({ figure, enemy });

    auto path = ps.buildPath(figure);

    ASSERT_EQ(path.size(), 3); // top and attack!
}

TEST(Pawn, EnemyInFrontLeft)
{
    auto ps = PathSystem();

    auto point = Point(4, 1);
    auto figure = make_shared<Figure>(point, FigureType::Pawn, FigurePlayer::Whites, 1);
    auto enemySide = figure->getPlayer() == FigurePlayer::Whites ? FigurePlayer::Blacks
                                                                 : figure->getPlayer();
    auto enemy = make_shared<Figure>(
        Point(point.getX() - 1, point.getY() + 1), figure->getType(), enemySide);

    ps.setBoard({ figure, enemy });

    auto path = ps.buildPath(figure);
    ASSERT_EQ(path.size(), 2); // top and attack!
}
