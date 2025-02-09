#pragma once

#include <limits>


struct HistogramBin 
{
private:
    double squaredDeviationsSum;

public:
    int count;       
    double sum;      
    double mean;     
    double min;      
    double max;  
    double variance;    

    HistogramBin() : squaredDeviationsSum(0), count(0), sum(0), mean(0), 
            min(std::numeric_limits<double>::max()),
            max(std::numeric_limits<double>::lowest()),
            variance(0) {}

    void add(double value) 
    {
        ++count;
        sum += value;
        if (value < min) 
        {
            min = value;
        }
        if (value > max) 
        { 
            max = value;
        }
        double delta1 = value - mean;
        mean += delta1 / count;
        double delta2 = value - mean;
        squaredDeviationsSum += delta1 * delta2;
        variance = (count > 1) ? (squaredDeviationsSum / (count - 1)) : 0;
    }
};