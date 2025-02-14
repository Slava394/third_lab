#include <iostream>
#include <cassert>
#include <string>

#include "UnitTest.h"
#include "Sequence.h"
#include "Set.h"
#include "Dictionary.h"              
#include "Histogram.h"   
#include "Point.h"
#include "Person.h" 


//=============================================================================
//                        Тесты для Set
//=============================================================================

void unitTestSetBasicInsertRemove() 
{
    Set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    assert(s.contains(1));
    assert(s.contains(2));
    assert(s.contains(3));
    bool removed = s.remove(2);
    assert(removed);
    assert(!s.contains(2));
    std::cout << "unitTestSetBasicInsertRemove passed.\n";
}

void unitTestSetDuplicateInsertion() 
{
    Set<int> s;
    s.insert(5);
    s.insert(5);
    s.insert(5);
    assert(s.contains(5));
    bool removed = s.remove(5);
    assert(removed);
    removed = s.remove(5);
    assert(!removed);
    std::cout << "unitTestSetDuplicateInsertion passed.\n";
}

void unitTestSetRemoveNonexistent() 
{
    Set<int> s;
    s.insert(10);
    bool removed = s.remove(20);
    assert(!removed);
    std::cout << "unitTestSetRemoveNonexistent passed.\n";
}

void unitTestSetCompositeBasic() 
{
    Set<Point> s;
    Point p1(1.0, 2.0), p2(3.0, 4.0), p3(5.0, 6.0);
    s.insert(p1);
    s.insert(p2);
    assert(s.contains(p1));
    assert(s.contains(p2));
    s.remove(p1);
    assert(!s.contains(p1));
    std::cout << "unitTestSetCompositeBasic passed.\n";
}

void unitTestSetMultipleInsertRemove() 
{
    Set<int> s;
    for (int i = 0; i < 100; i++) 
    {
        s.insert(i);
    }
    for (int i = 0; i < 100; i += 2) 
    { 
        s.remove(i);
    }
    for (int i = 0; i < 100; i++) 
    {
        if (i % 2 == 0)
        {
            assert(!s.contains(i));
        }
        else
        {
            assert(s.contains(i));
        }
    }
    std::cout << "unitTestSet5MultipleInsertRemove passed.\n";
}

void unitTestSetInsertRemoveAlternate() 
{
    Set<int> s;
    s.insert(10);
    assert(s.contains(10));
    s.remove(10);
    assert(!s.contains(10));
    s.insert(10);
    assert(s.contains(10));
    std::cout << "unitTestSetInsertRemoveAlternate passed.\n";
}

void unitTestSetCompositeDuplicates() 
{
    Set<Point> s;
    Point p(7.0, 8.0);
    s.insert(p);
    s.insert(p);
    assert(s.contains(p));
    s.remove(p);
    assert(!s.contains(p));
    std::cout << "unitTestSetCompositeDuplicates passed.\n";
}

void unitTestSetRemoveAll() 
{
    Set<int> s;
    for (int i = 0; i < 50; i++) 
    {
        s.insert(i);
    }
    for (int i = 0; i < 50; i++) 
    {
        s.remove(i);
    }
    for (int i = 0; i < 50; i++) 
    {
        assert(!s.contains(i));
    }
    std::cout << "unitTestSetRemoveAll passed.\n";
}

void unitTestSetInsertOutOfOrder() 
{
    Set<int> s;
    int arr[] = {10, 3, 7, 2, 15, 8, 6};
    for (int v : arr) 
    {
        s.insert(v);
    }
    for (int v : arr) 
    {
        assert(s.contains(v));
    }
    std::cout << "unitTestSetInsertOutOfOrder passed.\n";
}

// Test 10: Смешанные операции для Set<int>
void unitTestSetMixedOperations() 
{
    Set<int> s;
    s.insert(100);
    s.insert(200);
    assert(s.contains(100));
    assert(s.contains(200));
    s.remove(100);
    assert(!s.contains(100));
    s.insert(300);
    assert(s.contains(300));
    s.remove(200);
    assert(!s.contains(200));
    s.insert(400);
    assert(s.contains(400));
    std::cout << "unitTestSetMixedOperations passed.\n";
}

//=============================================================================
//                        Тесты для Dictionary
//=============================================================================

void unitTestDictionaryBasic() 
{
    Dictionary<int, std::string> dict;
    dict.insert(1, "one");
    dict.insert(2, "two");
    dict.insert(3, "three");
    std::string* val = dict.find(1);
    assert(val && *val == "one");
    val = dict.find(2);
    assert(val && *val == "two");
    val = dict.find(3);
    assert(val && *val == "three");
    std::cout << "unitTestDictionaryBasic passed.\n";
}

void unitTestDictionaryComposite() 
{
    Dictionary<Person, std::string> dict;
    Person p1("Alice", 30, 50000);
    Person p2("Bob", 25, 40000);
    Person p3("Charlie", 35, 60000);
    dict.insert(p1, "HR");
    dict.insert(p2, "IT");
    dict.insert(p3, "Sales");
    std::string* dept = dict.find(p1);
    assert(dept && *dept == "HR");
    dept = dict.find(p2);
    assert(dept && *dept == "IT");
    dept = dict.find(p3);
    assert(dept && *dept == "Sales");
    std::cout << "unitTestDictionaryComposite passed.\n";
}

void unitTestDictionaryDuplicateKeys() 
{
    Dictionary<int, std::string> dict;
    dict.insert(1, "one");
    dict.insert(1, "uno");  
    std::string* val = dict.find(1);
    assert(val && *val == "uno");
    std::cout << "unitTestDictionaryDuplicateKeys passed.\n";
}

void unitTestDictionaryRemoveNonExistent() 
{
    Dictionary<int, std::string> dict;
    dict.insert(1, "one");
    bool removed = dict.remove(2);
    assert(!removed);
    std::cout << "unitTestDictionaryRemoveNonExistent passed.\n";
}

void unitTestDictionaryManyKeys() 
{
    Dictionary<int, std::string> dict;
    for (int i = 0; i < 100; i++) 
    {
        dict.insert(i, "num" + std::to_string(i));
    }
    for (int i = 0; i < 100; i++) 
    {
        std::string* val = dict.find(i);
        assert(val && *val == "num" + std::to_string(i));
    }
    std::cout << "unitTestDictionaryManyKeys passed.\n";
}

void unitTestDictionaryRemoveOrder() 
{
    Dictionary<int, std::string> dict;
    for (int i = 0; i < 10; i++) 
    {
        dict.insert(i, "num" + std::to_string(i));
    }
    for (int i = 1; i < 10; i += 2) 
    {
        bool removed = dict.remove(i);
        assert(removed);
    }
    for (int i = 1; i < 10; i += 2) 
    {
        std::string* val = dict.find(i);
        assert(val == nullptr);
    }
    for (int i = 0; i < 10; i += 2) 
    {
        bool removed = dict.remove(i);
        assert(removed);
    }
    for (int i = 0; i < 10; i++) 
    {
        std::string* val = dict.find(i);
        assert(val == nullptr);
    }
    std::cout << "unitTestDictionaryRemoveOrder passed.\n";
}

void unitTestDictionaryUpdateValue() 
{
    Dictionary<int, std::string> dict;
    dict.insert(5, "five");
    dict.insert(5, "FIVE");
    std::string* val = dict.find(5);
    assert(val && *val == "FIVE");
    std::cout << "unitTestDictionaryUpdateValue passed.\n";
}

void unitTestDictionaryInorderIteration() 
{
    Dictionary<int, std::string> dict;
    dict.insert(3, "three");
    dict.insert(1, "one");
    dict.insert(2, "two");
    int lastKey = -1;
    dict.inorder([&](const int& key, const std::string& value) {
        assert(key > lastKey);
        lastKey = key;
    });
    std::cout << "unitTestDictionaryInorderIteration passed.\n";
}

void unitTestDictionaryCompositeRemove() 
{
    Dictionary<Person, std::string> dict;
    Person p1("Alice", 30, 50000);
    Person p2("Bob", 25, 40000);
    Person p3("Charlie", 35, 60000);
    dict.insert(p1, "HR");
    dict.insert(p2, "IT");
    dict.insert(p3, "Sales");
    bool removed = dict.remove(p1);
    assert(removed);
    std::string* dept = dict.find(p1);
    assert(dept == nullptr);
    std::cout << "unitTestDictionaryCompositeRemove passed.\n";
}

void unitTestDictionaryClear() 
{
    Dictionary<int, std::string> dict;
    for (int i = 0; i < 50; i++) 
    {
        dict.insert(i, "num" + std::to_string(i));
    }
    for (int i = 0; i < 50; i++) 
    {
        bool removed = dict.remove(i);
        assert(removed);
    }
    for (int i = 0; i < 50; i++) 
    {
        std::string* val = dict.find(i);
        assert(val == nullptr);
    }
    std::cout << "unitTestDictionaryClear passed.\n";
}

//=============================================================================
//                        Тесты для Histogram
//=============================================================================

void unitTestHistogramBasic() 
{
    Sequence<Person> persons;
    persons.append(Person("Alice", 28, 50000));
    persons.append(Person("Bob", 33, 40000));
    persons.append(Person("Charlie", 45, 60000));
    persons.append(Person("David", 37, 55000));
    persons.append(Person("Eva", 25, 48000));
    persons.append(Person("Frank", 42, 63000));

    Sequence<Interval> intervals;
    intervals.append(Interval(20, 30));  
    intervals.append(Interval(30, 40));  
    intervals.append(Interval(40, 50));  

    Histogram<Person> hist(persons, [](const Person& p) -> double {
        return static_cast<double>(p.age);
    }, intervals);

    int count20_30 = 0, count30_40 = 0, count40_50 = 0;
    hist.getBins().inorder([&](const Interval& interval, const HistogramBin& bin) {
        if (interval.getLower() == 20 && interval.getUpper() == 30)
        {
            count20_30 = bin.getCount();
        }
        else if (interval.getLower() == 30 && interval.getUpper() == 40)
        {
            count30_40 = bin.getCount();
        }
        else if (interval.getLower() == 40 && interval.getUpper() == 50)
        {
            count40_50 = bin.getCount();
        }
    });

    assert(count20_30 == 2);
    assert(count30_40 == 2);
    assert(count40_50 == 2);
    std::cout << "unitTestHistogramBasic passed.\n";
}

void unitTestHistogramEmpty() 
{
    Sequence<Person> persons; 

    Sequence<Interval> intervals;
    intervals.append(Interval(20, 30));
    intervals.append(Interval(30, 40));

    Histogram<Person> hist(persons, [](const Person& p) -> double { 
        return p.age; 
    }, intervals);

    int total = 0;
    hist.getBins().inorder([&](const Interval& interval, const HistogramBin& bin) {
        total += bin.getCount();
    });

    assert(total == 0);
    std::cout << "unitTestHistogramEmpty passed.\n";
}

void unitTestHistogramNoMatch() 
{
    Sequence<Person> persons;
    persons.append(Person("Old1", 80, 50000));
    persons.append(Person("Old2", 85, 55000));
    persons.append(Person("Old3", 90, 60000));

    Sequence<Interval> intervals;
    intervals.append(Interval(20, 30));
    intervals.append(Interval(30, 40));

    Histogram<Person> hist(persons, [](const Person& p) -> double { 
        return p.age; 
    }, intervals);

    int total = 0;
    hist.getBins().inorder([&](const Interval& interval, const HistogramBin& bin) {
        total += bin.getCount();
    });

    assert(total == 0);
    std::cout << "unitTestHistogramNoMatch passed.\n";
}

void unitTestHistogramSingleInterval() 
{
    Sequence<Person> persons;
    persons.append(Person("Young1", 22, 40000));
    persons.append(Person("Young2", 25, 45000));
    persons.append(Person("Young3", 27, 42000));

    Sequence<Interval> intervals;
    intervals.append(Interval(20, 30)); 
    intervals.append(Interval(30, 40));

    Histogram<Person> hist(persons, [](const Person& p) -> double { 
        return p.age; 
    }, intervals);

    int count20_30 = 0, count30_40 = 0;
    hist.getBins().inorder([&](const Interval& interval, const HistogramBin& bin) {
        if (interval.getLower() == 20 && interval.getUpper() == 30)
        {
            count20_30 = bin.getCount();
        }
        else if (interval.getLower() == 30 && interval.getUpper() == 40)
        {
            count30_40 = bin.getCount();
        }
    });

    assert(count20_30 == 3);
    assert(count30_40 == 0);
    std::cout << "unitTestHistogramSingleInterval passed.\n";
}

void unitTestHistogramFullRange() 
{
    Sequence<Person> persons;
    persons.append(Person("A", 18, 30000));
    persons.append(Person("B", 35, 50000));
    persons.append(Person("C", 55, 70000));

    Sequence<Interval> intervals;
    intervals.append(Interval(18, 25)); 
    intervals.append(Interval(25, 45)); 
    intervals.append(Interval(45, 65)); 

    Histogram<Person> hist(persons, [](const Person& p) -> double { 
        return p.age; 
    }, intervals);

    int total = 0;
    hist.getBins().inorder([&](const Interval& interval, const HistogramBin& bin) {
        total += bin.getCount();
    });

    assert(total == 3);
    std::cout << "unitTestHistogramFullRange passed.\n";
}

void unitTestHistogramSomeEmpty() 
{
    Sequence<Person> persons;
    persons.append(Person("A", 22, 40000));
    persons.append(Person("B", 38, 50000));

    Sequence<Interval> intervals;
    intervals.append(Interval(20, 30));
    intervals.append(Interval(30, 40));
    intervals.append(Interval(40, 50));

    Histogram<Person> hist(persons, [](const Person& p) -> double { 
        return p.age; 
    }, intervals);

    int count20_30 = 0, count30_40 = 0, count40_50 = 0;
    hist.getBins().inorder([&](const Interval& interval, const HistogramBin& bin) {
        if (interval.getLower() == 20 && interval.getUpper() == 30)
        {
            count20_30 = bin.getCount();
        }
        else if (interval.getLower() == 30 && interval.getUpper() == 40)
        {
            count30_40 = bin.getCount();
        }
        else if (interval.getLower() == 40 && interval.getUpper() == 50)
        {
            count40_50 = bin.getCount();
        }
    });

    assert(count20_30 == 1);
    assert(count30_40 == 1);
    assert(count40_50 == 0);
    std::cout << "unitTestHistogramSomeEmpty passed.\n";
}

void unitTestHistogramBoundaryValues() 
{
    Sequence<Person> persons;
    persons.append(Person("A", 20, 40000));  
    persons.append(Person("B", 29, 50000)); 
    persons.append(Person("C", 30, 60000));  
    persons.append(Person("D", 39, 55000));  

    Sequence<Interval> intervals;
    intervals.append(Interval(20, 30));
    intervals.append(Interval(30, 40));

    Histogram<Person> hist(persons, [](const Person& p) -> double { 
        return p.age; 
    }, intervals);

    int count20_30 = 0, count30_40 = 0;
    hist.getBins().inorder([&](const Interval& interval, const HistogramBin& bin) {
        if (interval.getLower() == 20 && interval.getUpper() == 30)
        {
            count20_30 = bin.getCount();
        }
        else if (interval.getLower() == 30 && interval.getUpper() == 40)
        {
            count30_40 = bin.getCount();
        }
    });

    assert(count20_30 == 2); 
    assert(count30_40 == 2); 
    std::cout << "unitTestHistogramBoundaryValues passed.\n";
}

void unitTestHistogramSameAge() 
{
    Sequence<Person> persons;
    for (int i = 0; i < 5; i++) 
    {
        persons.append(Person("Same", 30, 50000));
    }

    Sequence<Interval> intervals;
    intervals.append(Interval(20, 30));  
    intervals.append(Interval(30, 40)); 

    Histogram<Person> hist(persons, [](const Person& p) -> double { 
        return p.age; 
    }, intervals);
    
    int count20_30 = 0, count30_40 = 0;
    hist.getBins().inorder([&](const Interval& interval, const HistogramBin& bin) {
        if (interval.getLower() == 20 && interval.getUpper() == 30)
        {
            count20_30 = bin.getCount();
        }
        else if (interval.getLower() == 30 && interval.getUpper() == 40)
        {
            count30_40 = bin.getCount();
        }
    });

    assert(count20_30 == 0);
    assert(count30_40 == 5);
    std::cout << "unitTestHistogramSameAge passed.\n";
}

void unitTestHistogramNarrowIntervals() 
{
    Sequence<Person> persons;
    persons.append(Person("A", 25, 40000));
    persons.append(Person("B", 26, 45000));
    persons.append(Person("C", 27, 50000));

    Sequence<Interval> intervals;
    intervals.append(Interval(25, 26));
    intervals.append(Interval(26, 27));
    intervals.append(Interval(27, 28));

    Histogram<Person> hist(persons, [](const Person& p) -> double { 
        return p.age; 
    }, intervals);

    int count25_26 = 0, count26_27 = 0, count27_28 = 0;
    hist.getBins().inorder([&](const Interval& interval, const HistogramBin& bin) {
        if (interval.getLower() == 25 && interval.getUpper() == 26)
        {
            count25_26 = bin.getCount();
        }
        else if (interval.getLower() == 26 && interval.getUpper() == 27)
        {
            count26_27 = bin.getCount();
        }
        else if (interval.getLower() == 27 && interval.getUpper() == 28)
        {
            count27_28 = bin.getCount();
        }
    });

    assert(count25_26 == 1);
    assert(count26_27 == 1);
    assert(count27_28 == 1);
    std::cout << "unitTestHistogramNarrowIntervals passed.\n";
}

void unitTestHistogramTotalCount() 
{
    Sequence<Person> persons;
    for (int i = 0; i < 20; i++) 
    {
        persons.append(Person("P" + std::to_string(i), 30 + (i % 10), 50000));
    }

    Sequence<Interval> intervals;
    intervals.append(Interval(20, 50));
    intervals.append(Interval(50, 85));
    intervals.append(Interval(85, 100)); 

    Histogram<Person> hist(persons, [](const Person& p) -> double { 
        return p.age; 
    }, intervals);

    int totalCount = 0;
    hist.getBins().inorder([&](const Interval& interval, const HistogramBin& bin) {
        totalCount += bin.getCount();
    });

    assert(totalCount == 20);
    std::cout << "unitTestHistogramTotalCount passed.\n";
}