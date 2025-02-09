#pragma once

#include <functional>
#include "Dictionary.h"    
#include "ISequence.h"    
#include "Interval.h"      
#include "HistogramBin.h"  


template <typename T>
class Histogram 
{
private:
    Dictionary<Interval, HistogramBin> bins;

public:
    Histogram(const ISequence<T>& data,
              std::function<double(const T&)> valueExtractor,
              const ISequence<Interval>& intervals) //stupid
    {
        for (size_t i = 0; i < intervals.getSize(); ++i) 
        {
            const Interval& interval = intervals.get(i);
            HistogramBin bin;
            bins.insert(interval, bin);
        }
        
        for (size_t i = 0; i < data.getSize(); ++i) 
        {
            const T& element = data.get(i);
            double value = valueExtractor(element);
            
            size_t left = 0;
            size_t right = intervals.getSize();
            
            while (left < right)
            {
                size_t middle = left + (right - left) / 2;
                const Interval& currentInterval = intervals.get(middle);
                
                if (currentInterval.contains(value))
                {
                    HistogramBin* binPtr = bins.find(currentInterval);
                    if (binPtr)
                    {
                        binPtr->add(value);
                    }
                    break;
                }
                else if (value < currentInterval.lower)
                {
                    right = middle;
                }
                else 
                {
                    left = middle + 1;
                }
            }
        }
    }
    
    const Dictionary<Interval, HistogramBin>& getBins() const 
    {
        return bins;
    }
};
