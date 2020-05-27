#include <Point.h>

#include <sstream>
#include <stdexcept>

using namespace std;

Point::Point(unsigned int a, unsigned int b)
    : x(a)
    , y(b)
{
}

Point::Point(const Point& point)
    : x(point.getX())
    , y(point.getY())
{
}

Point& Point::operator=(const Point& p)
{
    x = p.x;
    y = p.y;
    return *this;
}

unsigned int Point::getX() const
{
    return x;
}

unsigned int Point::getY() const
{
    return y;
}

void Point::setX(unsigned int i)
{
    x = i;
}

void Point::setY(unsigned int i)
{
    y = i;
}

string Point::asString() const
{
    ostringstream s;
    s << "(" << getX();
    s << ", " << getY();
    s << ")";
    return s.str();
}

bool Point::inBounds() const
{
    return x < 8 && y < 8;
}

bool Point::operator==(const Point& b) const
{
    return x == b.getX() && y == b.getY();
}

bool Point::operator!=(const Point& point) const
{
    return !(*this == point);
}

void Point::shift(int dx, int dy)
{
    x += dx;
    y += dy;
}

ostream& operator<<(ostream& o, const Point& p)
{
    o << p.asString();
    return o;
}
