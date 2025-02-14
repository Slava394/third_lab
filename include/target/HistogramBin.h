#pragma once

#include <limits>


class HistogramBin 
{
private:
    int count;       
    double sum;      
    double mean;     
    double min;      
    double max;  
    double variance;    
    double squaredDeviationsSum;

public:
    HistogramBin() 
        : count(0), sum(0), mean(0), 
          min(std::numeric_limits<double>::max()),
          max(std::numeric_limits<double>::lowest()),
          variance(0), squaredDeviationsSum(0) {}

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

    int getCount() const 
    { 
        return count; 
    }

    double getSum() const 
    { 
        return sum; 
    }

    double getMean() const 
    { 
        return mean; 
    }

    double getMin() const 
    { 
        return min; 
    }

    double getMax() const 
    { 
        return max; 
    }

    double getVariance() const 
    { 
        return variance; 
    }
};