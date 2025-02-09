#include <iostream>

#include "Test.h"


int main() 
{
    unitTestDictionaryBasic();
    unitTestDictionaryComposite();
    unitTestDictionaryDuplicateKeys();
    unitTestDictionaryRemoveNonExistent();
    unitTestDictionaryManyKeys();
    unitTestDictionaryRemoveOrder();
    unitTestDictionaryUpdateValue();
    unitTestDictionaryInorderIteration();
    unitTestDictionaryCompositeRemove();
    unitTestDictionaryClear();
    
    std::cout << "All dictionary tests passed.\n";
    return 0;
}