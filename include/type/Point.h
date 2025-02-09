#pragma once

#include <string>


struct Point 
{
    double x;
    double y;
    
    Point() : x(0.0), y(0.0) {}
    Point(double x, double y) : x(x), y(y) {}

    bool operator<(const Point& other) const 
    {
        if (x != other.x)
        {
            return x < other.x;
        }
        return y < other.y;
    }

    bool operator>(const Point& other) const 
    {
        return other < *this;
    }

    bool operator==(const Point& other) const 
    {
        return x == other.x && y == other.y;
    }
};

inline std::ostream& operator<<(std::ostream& os, const Point& p) 
{
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}