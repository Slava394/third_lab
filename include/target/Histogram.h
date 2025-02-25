#pragma once

#include <functional>

#include "Dictionary.h"    
#include "Sequence.h"    
#include "Interval.h"      
#include "HistogramBin.h"  
#include "QuickSorter.h"


template <typename T>
class Histogram 
{
private:
    Dictionary<Interval, HistogramBin> bins;
    Sequence<Interval> intervals;
    std::function<double(const T&)> valueExtractor;

    void addValueToBin(double value)
    {
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
            else if (value < currentInterval.getLower())
            {
                right = middle;
            }
            else 
            {
                left = middle + 1;
            }
        }
    }

    void validateIntervalsNonOverlapping(const Sequence<Interval>& sortedIntervals)
    {
        for (size_t i = 0; i + 1 < sortedIntervals.getSize(); ++i)
        {
            if (sortedIntervals.get(i).getUpper() > sortedIntervals.get(i + 1).getLower())
            {
                throw std::runtime_error("Intervals overlap at index " + std::to_string(i) + ".");
            }
        }
    }

public:
    Histogram(std::function<double(const T&)> valueExtractor_, const Sequence<Interval>& intervals_)
        : valueExtractor(valueExtractor_), intervals(intervals_)
    {
        QuickSorter<Interval> quickSorter;
        quickSorter.sort(intervals);
        
        validateIntervalsNonOverlapping(intervals);

        size_t size = intervals.getSize();
        for (size_t i = 0; i < size; ++i) 
        {
            bins.insert(intervals.get(i), HistogramBin());
        }
    }

    Histogram(std::function<double(const T&)> valueExtractor_, Sequence<Interval>&& intervals_)
        : valueExtractor(valueExtractor_), intervals(std::move(intervals_))
    {
        QuickSorter<Interval> quickSorter;
        quickSorter.sort(intervals);

        validateIntervalsNonOverlapping(intervals);

        size_t size = intervals.getSize();
        for (size_t i = 0; i < size; ++i) 
        {
            bins.insert(intervals.get(i), HistogramBin());
        }
    }

    Histogram(const Sequence<T>& data, std::function<double(const T&)> valueExtractor_, const Sequence<Interval>& intervals_)
        : valueExtractor(valueExtractor_), intervals(intervals_)
    {
        QuickSorter<Interval> quickSorter;
        quickSorter.sort(intervals);

        validateIntervalsNonOverlapping(intervals);

        size_t size = intervals.getSize();
        for (size_t i = 0; i < size; ++i) 
        {
            bins.insert(intervals.get(i), HistogramBin());
        }

        size_t dataSize = data.getSize();
        for (size_t i = 0; i < dataSize; ++i) 
        {
            addValueToBin(valueExtractor(data.get(i)));
        }
    }

    Histogram(const Sequence<T>& data, std::function<double(const T&)> valueExtractor_, Sequence<Interval>&& intervals_)
        : valueExtractor(valueExtractor_), intervals(std::move(intervals_))
    {
        QuickSorter<Interval> quickSorter;
        quickSorter.sort(intervals);

        validateIntervalsNonOverlapping(intervals);

        size_t size = intervals.getSize();
        for (size_t i = 0; i < size; ++i) 
        {
            bins.insert(intervals.get(i), HistogramBin());
        }

        size_t dataSize = data.getSize();
        for (size_t i = 0; i < dataSize; ++i) 
        {
            addValueToBin(valueExtractor(data.get(i)));
        }
    }

    void updateData(const T& element)
    {
        addValueToBin(valueExtractor(element));
    }
    
    const Dictionary<Interval, HistogramBin>& getBins() const 
    {
        return bins;
    }

    const Sequence<Interval>& getIntervals() const
    {
        return intervals;
    }
};