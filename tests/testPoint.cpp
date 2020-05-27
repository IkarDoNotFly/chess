
#include <Point.h>
#include <gtest/gtest.h>

TEST(Point, coordinateCheck)
{
    Point point(0, 0);
    ASSERT_EQ(point.getX(), 0);
    ASSERT_EQ(point.getY(), 0);

    point = Point(1, 1);
    ASSERT_EQ(point.getX(), 1);
    ASSERT_EQ(point.getY(), 1);

    point = Point(3, 2);
    ASSERT_EQ(point.getX(), 3);
    ASSERT_EQ(point.getY(), 2);
}

TEST(Point, inBounds)
{
    Point point(0, 0);
    ASSERT_TRUE(point.inBounds());

    point = Point(1, 1);
    ASSERT_TRUE(point.inBounds());

    point = Point(2, 2);
    ASSERT_TRUE(point.inBounds());

    point = Point(3, 3);
    ASSERT_TRUE(point.inBounds());

    point = Point(4, 4);
    ASSERT_TRUE(point.inBounds());

    point = Point(5, 5);
    ASSERT_TRUE(point.inBounds());

    point = Point(6, 6);
    ASSERT_TRUE(point.inBounds());

    point = Point(7, 7);
    ASSERT_TRUE(point.inBounds());

    point = Point(0, 8);
    ASSERT_FALSE(point.inBounds());

    point = Point(8, 0);
    ASSERT_FALSE(point.inBounds());
}

TEST(Point, setX)
{
    Point point(0, 0);

    auto x = 5;
    point.setX(x);
    ASSERT_EQ(point.getX(), x);
}

TEST(Point, setY)
{
    Point point(0, 0);

    auto y = 5;
    point.setY(y);
    ASSERT_EQ(point.getY(), y);
}

TEST(Point, negativeCoordinates)
{
    Point point(-1, -1);
    ASSERT_FALSE(point.inBounds());

    auto x = point.getX();
    auto y = point.getY();

    ASSERT_GT(x, 0);
    ASSERT_GT(y, 0);
}
