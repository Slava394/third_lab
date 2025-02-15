#pragma once

#include <stdexcept>  


class Interval
{
private:
    double lower, upper;

    void validateBounds(double newLower, double newUpper) 
    {
        if (newLower >= newUpper) 
        {
            throw std::logic_error("Upper bound can't be less or equal to the lower bound.");
        }
    }

public:
    Interval() : lower(0.0), upper(1.0) {} 

    Interval(double lower_, double upper_) : lower(lower_), upper(upper_)
    {
        validateBounds(lower, upper);
    }

    Interval(const Interval& other)
    {
        lower = other.lower;
        upper = other.upper;
    }

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
        return other < *this;
    }

    bool operator<=(const Interval& other) const 
    {
        return !(other < *this);
    }

    bool operator>=(const Interval& other) const 
    {
        return !(*this < other);
    }

    double getLower() const 
    {
        return lower;
    }

    double getUpper() const 
    {
        return upper;
    }
};