#include <iostream>

#include "UnitTest.h"


int main() 
{
    unitTestSetBasicInsertRemove();
    unitTestSetDuplicateInsertion();
    unitTestSetRemoveNonexistent();
    unitTestSetCompositeBasic();
    unitTestSetMultipleInsertRemove();
    unitTestSetInsertRemoveAlternate();
    unitTestSetCompositeDuplicates();
    unitTestSetRemoveAll();
    unitTestSetInsertOutOfOrder();
    unitTestSetMixedOperations();

    std::cout << "All set tests passed.\n";
    return 0;
}