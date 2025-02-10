#include <iostream>

#include "UnitTest.h"


int main() 
{
    unitTestHistogramBasic();
    unitTestHistogramEmpty();
    unitTestHistogramNoMatch();
    unitTestHistogramSingleInterval();
    unitTestHistogramFullRange();
    unitTestHistogramSomeEmpty();
    unitTestHistogramBoundaryValues();
    unitTestHistogramSameAge();
    unitTestHistogramNarrowIntervals();
    unitTestHistogramTotalCount();
    
    std::cout << "All histogram tests passed.\n";
    return 0;
}