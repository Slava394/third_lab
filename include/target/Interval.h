#pragma once


struct Interval
{
    double lower, upper;

    Interval() : lower(0.0), upper(0.0) {}
    
    Interval(double lower_, double upper_) : lower(lower_), upper(upper_) {}
    
    bool contains(double x) const 
    {
        return x >= lower && x < upper;
    }

    bool operator<(const Interval& other) const 
    {
        return (lower < other.lower) || (lower == other.lower && upper < other.upper);
    }

    bool operator==(const Interval& other) const 
    {
        return lower == other.lower && upper == other.upper;
    }

    bool operator>(const Interval& other) const
    {
        return !(*this == other) && !(*this < other);
    }

    bool operator<=(const Interval& other) const 
    {
        return *this < other || *this == other;
    }

    bool operator>=(const Interval& other) const 
    {
        return *this > other || *this == other;
    }
};