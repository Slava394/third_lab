#pragma once


void unitTestSetBasicInsertRemove();
void unitTestSetDuplicateInsertion();
void unitTestSetRemoveNonexistent();
void unitTestSetCompositeBasic();
void unitTestSetMultipleInsertRemove();
void unitTestSetInsertRemoveAlternate();
void unitTestSetCompositeDuplicates();
void unitTestSetRemoveAll();
void unitTestSetInsertOutOfOrder();
void unitTestSetMixedOperations();

void unitTestDictionaryBasic();
void unitTestDictionaryComposite();
void unitTestDictionaryDuplicateKeys();
void unitTestDictionaryRemoveNonExistent();
void unitTestDictionaryManyKeys();
void unitTestDictionaryRemoveOrder();
void unitTestDictionaryUpdateValue();
void unitTestDictionaryInorderIteration();
void unitTestDictionaryCompositeRemove();
void unitTestDictionaryClear();

void unitTestHistogramBasic();
void unitTestHistogramEmpty();
void unitTestHistogramNoMatch();
void unitTestHistogramSingleInterval();
void unitTestHistogramFullRange();
void unitTestHistogramSomeEmpty();
void unitTestHistogramBoundaryValues();
void unitTestHistogramSameAge();
void unitTestHistogramNarrowIntervals();
void unitTestHistogramTotalCount();