
#include <Figure.h>
#include <FigureFactory.h>
#include <PathSystem.h>
#include <Point.h>
#include <gtest/gtest.h>

#include <list>
#include <memory>

using std::list;
using std::make_shared;
using std::shared_ptr;

typedef PFigure fig;

class CastlingTest : public ::testing::Test {
public:
    fig king;
    fig enemyKing;
    fig leftRook;
    fig rightRook;
    Point kingLeftRookPoint;
    Point kingRightRookPoint;
    PathSystem ps;

public:
    void SetUp() override
    {
        king = FigureFactory::buildKing(FigurePlayer::Whites);
        enemyKing = FigureFactory::buildKing(FigurePlayer::Blacks);
        auto allyRooks = FigureFactory::buildRooks(FigurePlayer::Whites);
        leftRook = allyRooks.front();
        rightRook = allyRooks.back();

        kingLeftRookPoint = Point(king->getX() - 2, king->getY());
        kingRightRookPoint = Point(king->getX() + 2, king->getY());

        ps.setBoard({king, enemyKing, leftRook, rightRook});
    }
};

TEST_F(CastlingTest, BothSideCastling)
{
    ASSERT_TRUE(ps.checkCastling(
        leftRook,
        king)); // castling method doesn't count future enemy checks
    ASSERT_TRUE(ps.checkCastling(rightRook, king));
    auto moves = ps.getListOfAvailableMoves(Whites);
    bool kingCastleLeft = false, kingCastleRight = false, leftRookCastle = false,
         rightRookCastle = false;
    for (const auto& i : moves) {
        if (*i.first == *king && *(i.first->getPoint()) == *(king->getPoint())) {
            if (*i.second == kingLeftRookPoint)
                kingCastleLeft = true;
            if (*i.second == kingRightRookPoint)
                kingCastleRight = true;
        } else if (*i.first == *leftRook && *(i.first->getPoint()) == *(leftRook->getPoint())) {
            if (*i.second == *king->getPoint())
                leftRookCastle = true;
        } else if (*i.first == *rightRook && *(i.first->getPoint()) == *(rightRook->getPoint())) {
            if (*i.second == *king->getPoint())
                rightRookCastle = true;
        }
    }
    ASSERT_TRUE(kingCastleLeft);
    ASSERT_TRUE(kingCastleRight);
    ASSERT_TRUE(leftRookCastle);
    ASSERT_TRUE(rightRookCastle);
}

/*We add enemy rook right above king coordinate at the end of left*/
TEST_F(CastlingTest, EnemyRookAboveLeftKing)
{
    auto rook = make_shared<Figure>(Point(king->getX() - 2, 5), Rook, Blacks);
    ps.setBoard({king, enemyKing, leftRook, rightRook, rook});

    ASSERT_TRUE(ps.checkCastling(leftRook, king));
    ASSERT_TRUE(ps.checkCastling(rightRook, king));
    auto moves = ps.getListOfAvailableMoves(Whites);

    bool kingCastleLeft = false, kingCastleRight = false, leftRookCastle = false,
         rightRookCastle = false;
    for (const auto& i : moves) {
        if (*i.first == *king && *(i.first->getPoint()) == *(king->getPoint())) {
            if (*i.second == kingLeftRookPoint)
                kingCastleLeft = true;
            if (*i.second == kingRightRookPoint)
                kingCastleRight = true;
        } else if (*i.first == *leftRook && *(i.first->getPoint()) == *(leftRook->getPoint())) {
            if (*i.second == *king->getPoint())
                leftRookCastle = true;
        } else if (*i.first == *rightRook && *(i.first->getPoint()) == *(rightRook->getPoint())) {
            if (*i.second == *king->getPoint())
                rightRookCastle = true;
        }
    }
    ASSERT_FALSE(kingCastleLeft);
    ASSERT_TRUE(kingCastleRight);
    ASSERT_FALSE(leftRookCastle);
    ASSERT_TRUE(rightRookCastle);
}

/*We add enemy rook right above king coordinate at the end of right */
TEST_F(CastlingTest, EnemyRookAboveRightKing)
{
    auto rook = make_shared<Figure>(Point(king->getX() + 2, 5), Rook, Blacks);
    ps.setBoard({king, enemyKing, leftRook, rightRook, rook});
    ASSERT_TRUE(ps.checkCastling(leftRook, king));
    ASSERT_TRUE(ps.checkCastling(rightRook, king));
    auto moves = ps.getListOfAvailableMoves(Whites);
    bool kingCastleLeft = false, kingCastleRight = false, leftRookCastle = false,
         rightRookCastle = false;
    for (const auto& i : moves) {
        if (*i.first == *king && *(i.first->getPoint()) == *(king->getPoint())) {
            if (*i.second == kingLeftRookPoint)
                kingCastleLeft = true;
            if (*i.second == kingRightRookPoint)
                kingCastleRight = true;
        } else if (*i.first == *leftRook && *(i.first->getPoint()) == *(leftRook->getPoint())) {
            if (*i.second == *king->getPoint())
                leftRookCastle = true;
        } else if (*i.first == *rightRook && *(i.first->getPoint()) == *(rightRook->getPoint())) {
            if (*i.second == *king->getPoint())
                rightRookCastle = true;
        }
    }
    ASSERT_TRUE(kingCastleLeft);
    ASSERT_FALSE(kingCastleRight);
    ASSERT_TRUE(leftRookCastle);
    ASSERT_FALSE(rightRookCastle);
}

TEST(King, OneKingAtMiddleOfMap)
{
    PathSystem ps;

    auto king = make_shared<Figure>(Point(3, 3), FigureType::King, FigurePlayer::Whites);
    ps.setBoard({king});
    auto path = ps.buildPath(king);

    ASSERT_EQ(path.size(), 8); // top topRight right rightBot bot botLeft left leftTop
}

TEST(King, TopRightCorner)
{
    PathSystem ps;

    auto king = make_shared<Figure>(Point(7, 7), FigureType::King, FigurePlayer::Whites);
    ps.setBoard({king});
    auto path = ps.buildPath(king);

    ASSERT_EQ(path.size(), 3); // bot botLeft left
}

TEST(King, OnALineWithEnemyRook)
{
    PathSystem ps;

    auto king = make_shared<Figure>(Point(7, 7), FigureType::King, FigurePlayer::Whites);
    auto enemyKing = make_shared<Figure>(Point(0, 0), FigureType::King, FigurePlayer::Blacks);
    auto enemyRook = make_shared<Figure>(Point(0, 7), FigureType::Rook, FigurePlayer::Blacks);
    ps.setBoard({king, enemyRook, enemyKing});

    auto moves = ps.getListOfAvailableMoves(king->getPlayer());
    PPoints kingMoves;
    for (const auto& i : moves)
        if (*i.first == *king)
            kingMoves.push_back(i.second);

    ASSERT_EQ(kingMoves.size(), 2);
}

TEST(King, OnALineWithEnemyRookAndAllyBishopCanKillEnemy)
{
    PathSystem ps;

    auto king = make_shared<Figure>(Point(7, 7), FigureType::King, FigurePlayer::Whites);
    auto enemyKing = make_shared<Figure>(Point(0, 0), FigureType::King, FigurePlayer::Blacks);
    auto enemyRook = make_shared<Figure>(Point(0, 7), FigureType::Rook, FigurePlayer::Blacks);
    auto allyBishop = make_shared<Figure>(Point(7, 0), FigureType::Bishop, FigurePlayer::Whites);
    ps.setBoard({king, enemyRook, allyBishop, enemyKing});

    auto moves = ps.getListOfAvailableMoves(FigurePlayer::Whites);
    PPoints kingMoves;
    PPoints bishopMoves;
    for (const auto& i : moves)
        if (*i.first == *king)
            kingMoves.push_back(i.second);
        else if (*i.first == *allyBishop)
            bishopMoves.push_back(i.second);

    ASSERT_EQ(kingMoves.size(), 2); // bot botLeft
    ASSERT_EQ(moves.size(), 3); // king and the allyBishop
    ASSERT_EQ(bishopMoves.size(), 1); // only one turn to get that rook
}

TEST(King, NearEnemyQueen)
{
    PathSystem ps;

    auto king = make_shared<Figure>(Point(7, 7), FigureType::King, FigurePlayer::Blacks);
    auto enemyKing = make_shared<Figure>(Point(0, 0), FigureType::King, FigurePlayer::Whites);
    auto enemyQueen = make_shared<Figure>(Point(6, 6), FigureType::Queen, FigurePlayer::Whites);
    ps.setBoard({king, enemyQueen, enemyKing});

    auto moves = ps.getListOfAvailableMoves(FigurePlayer::Blacks);
    ASSERT_EQ(moves.size(), 1); // king attacks queen
}

TEST(King, NearEnemyProtectedQueen)
{
    PathSystem ps;

    auto king = make_shared<Figure>(Point(7, 7), FigureType::King, FigurePlayer::Blacks);
    auto enemyKing = make_shared<Figure>(Point(0, 0), FigureType::King, FigurePlayer::Whites);
    auto enemyQueen = make_shared<Figure>(Point(6, 6), FigureType::Queen, FigurePlayer::Whites);
    auto pawn = make_shared<Figure>(Point(5, 5), FigureType::Pawn, FigurePlayer::Whites);
    ps.setBoard({king, enemyQueen, enemyKing, pawn});

    auto moves = ps.getListOfAvailableMoves(FigurePlayer::Blacks);
    ASSERT_TRUE(moves.empty()); // checkmate situation
}
