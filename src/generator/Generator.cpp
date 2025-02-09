#include <iostream>
#include <fstream>
#include <random>

#include "Generator.h"
#include "Point.h"
#include "Person.h"


void generateInts(size_t count, const std::string& filename) 
{
    std::ofstream out(filename);
    
    if (!out) 
    {
        std::cerr << "Exception with open " << filename << ".\n";
        return;
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> intDist(-1000000, 1000000);
    
    for (size_t i = 0; i < count; ++i) 
    {
        int value = intDist(gen);
        out << value << "\n";
    }

    out.close();
    std::cout << "Generation of ints completed.\n";
}

void generatePoints(size_t count, const std::string& filename) 
{
    std::ofstream out(filename);

    if (!out) 
    {
        std::cerr << "Exception with open " << filename << ".\n";
        return;
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> coordDist(-100000.0, 100000.0);
    
    for (size_t i = 0; i < count; ++i) 
    {
        double x = coordDist(gen);
        double y = coordDist(gen);
        out << x << " " << y << "\n";
    }

    out.close();
    std::cout << "Generation of points completed.\n";
}

void generatePersons(size_t count, const std::string& filename) 
{
    std::ofstream out(filename);

    if (!out) 
    {
        std::cerr << "Exception with open " << filename << ".\n";
        return;
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::uniform_int_distribution<> ageDist(18, 65);              
    std::uniform_real_distribution<> salaryDist(30000.0, 150000.0);   
    
    auto generateRandomName = [&gen]() -> std::string {
        std::string name;
        std::uniform_int_distribution<> lenDist(5, 10);
        int len = lenDist(gen);
        std::uniform_int_distribution<> letterDist(0, 25);
        for (int i = 0; i < len; i++) 
        {
            char c = 'a' + letterDist(gen);
            name.push_back(c);
        }
        return name;
    };

    for (size_t i = 0; i < count; ++i) 
    {
        std::string name = generateRandomName();
        int age = ageDist(gen);
        double salary = salaryDist(gen);
        out << name << " " << age << " " << salary << "\n";
    }

    out.close();
    std::cout << "Generation of persons completed.\n";
}