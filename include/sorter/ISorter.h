#pragma once

#include <concepts>
#include <functional>

#include "ISequence.h"


template <Comparable Type>
class ISorter
{
public:
    virtual void sort(ISequence<Type>& sequence) = 0;
};