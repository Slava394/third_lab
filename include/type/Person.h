#pragma once

#include <string>
#include <iostream>


struct Person 
{
    std::string name;
    int age;
    double salary;

    Person() : name(""), age(0), salary(0.0) {}
    Person(const std::string& n, int a, double s) : name(n), age(a), salary(s) {}

    bool operator<(const Person& other) const 
    {
        if (age != other.age)
        {
            return age < other.age;
        }
        if (salary != other.salary)
        {
            return salary < other.salary;
        }
        return name < other.name;
    }

    bool operator>(const Person& other) const 
    {
        return other < *this;
    }

    bool operator==(const Person& other) const 
    {
        return age == other.age && name == other.name && salary == other.salary;
    }
};

inline std::ostream& operator<<(std::ostream& os, const Person& p) 
{
    os << p.name << " " << p.age << " " << p.salary;
    return os;
}