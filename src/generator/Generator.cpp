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
    std::normal_distribution<> intDist(0, 500000); 

    for (size_t i = 0; i < count; ++i) 
    {
        int value = std::round(intDist(gen)); 
        out << value << "\n";
    }

    out.close();
    std::cout << "Generation of normally distributed ints completed.\n";
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
    std::normal_distribution<> coordDist(0.0, 50000.0); 

    for (size_t i = 0; i < count; ++i) 
    {
        double x = coordDist(gen);
        double y = coordDist(gen);
        out << x << " " << y << "\n";
    }

    out.close();
    std::cout << "Generation of normally distributed points completed.\n";
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
    
    std::normal_distribution<> ageDist(35, 10);     
    std::normal_distribution<> salaryDist(75000.0, 20000.0);
    
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
        int age = std::round(ageDist(gen));
        if (age < 18) age = 18; 
        if (age > 65) age = 65; 

        double salary = salaryDist(gen);
        if (salary < 30000.0) salary = 30000.0; 
        if (salary > 150000.0) salary = 150000.0; 
        out << name << " " << age << " " << salary << "\n";
    }

    out.close();
    std::cout << "Generation of normally distributed persons completed.\n";
}