#pragma once

#include <list>
#include <memory>
#include <string>

/// This class represents point on a chessboard
class Point {
    unsigned int x, y;

public:
    Point(const Point& point);
    explicit Point(unsigned int x = 0, unsigned int y = 0);
    Point& operator=(const Point& p);
    unsigned int getX() const;
    unsigned int getY() const;
    bool inBounds() const; /// says whether coordinates in [0;7] range
    void setX(unsigned int);
    void setY(unsigned int);
    void shift(int dx, int dy);
    std::string asString() const;
    bool operator==(const Point& point) const;
    bool operator!=(const Point& point) const;
};

std::ostream& operator<<(std::ostream& o, const Point& p);

typedef std::shared_ptr<Point> PPoint;
typedef std::list<PPoint> PPoints;
