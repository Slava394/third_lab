#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

#include "LoadTest.h"
#include "Dictionary.h"
#include "Set.h"


void loadTestDictionary() 
{
    std::ofstream csv("dictionary_results.csv");
    if (!csv.is_open()) 
    {
        std::cerr << "Cannot open dictionary_results.csv for writing" << std::endl;
        return;
    }
    csv << "N,InsertionTimeMillis" << "\n";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(0, 500000); 

    const long long startN = 5'000'000;      
    const long long endN = 200'000'000;        
    const long long step = 5'000'000;         

    for (long long N = startN; N <= endN; N += step) 
    {
        Dictionary<int, int> dict;
        auto start_time = std::chrono::high_resolution_clock::now();
        for (long long i = 0; i < N; i++) 
        {
            int key = std::round(dist(gen));
            int value = std::round(dist(gen));
            dict.insert(key, value);
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        csv << N << "," << duration << "\n";
        std::cout << "Dictionary: Inserted " << N << " elements in " << duration << " ms" << std::endl;
    }
    csv.close();
}

void loadTestSet() 
{
    std::ofstream csv("set_results.csv");
    if (!csv.is_open()) 
    {
        std::cerr << "Cannot open set_results.csv for writing" << std::endl;
        return;
    }
    csv << "N,InsertionTimeMillis" << "\n";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(0, 500000); 

    const long long startN = 5'000'000;     
    const long long endN =  200'000'000;       
    const long long step = 5'000'000;        

    for (long long N = startN; N <= endN; N += step) 
    {
        Set<int> set;
        auto start_time = std::chrono::high_resolution_clock::now();
        for (long long i = 0; i < N; i++) 
        {
            int value = std::round(dist(gen));
            set.insert(value);
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        csv << N << "," << duration << "\n";
        std::cout << "Set: Inserted " << N << " elements in " << duration << " ms" << std::endl;
    }
    csv.close();
}