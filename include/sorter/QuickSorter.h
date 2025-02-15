#pragma once

#include <functional>

#include "ISorter.h"


template <Comparable Type> 
class QuickSorter : public ISorter<Type>
{
private:
    std::function<short(const Type&, const Type&)> comparator;

    void swap(Type& elem1, Type& elem2)
    {
        if (comparator(elem1, elem2) != 0)
        {
            Type temp = elem1;
            elem1 = elem2;
            elem2 = temp;
        }
    }

    size_t partition(ISequence<Type>& sequence, size_t low, size_t high)
    {
        constexpr double GOLDEN_RATIO = 0.6180339887498948482;
        size_t pivotIndex = low + static_cast<size_t>((high - low) * GOLDEN_RATIO);
        Type pivot = sequence[pivotIndex];
        
        size_t i = low, j = high;
        while (true)
        {
            while (comparator(sequence[i], pivot) == 1) i++;
            while (comparator(sequence[j], pivot) == -1) j--;
            if (i >= j) return j;
            swap(sequence[i++], sequence[j--]);
        }
    }

    void quickSort(ISequence<Type>& sequence, size_t low, size_t high)
    {
        if (low < high)
        {
            size_t k = partition(sequence, low, high);
            quickSort(sequence, low, k);
            quickSort(sequence, k + 1, high);
        }
    }
public:
    QuickSorter(std::function<short(const Type&, const Type&)> comparator_ = 
        [](const Type& a, const Type& b) { return (a > b) ? -1 : (a < b) ? 1 : 0; })
        : comparator(comparator_) {}

    void sort(ISequence<Type>& sequence) override
    {
        if (sequence.getSize() == 0) return;
        quickSort(sequence, 0, sequence.getSize() - 1);
    }
};