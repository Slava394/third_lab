#pragma once

#include <initializer_list>

#include "ISequence.h"
#include "Vector.h"


template <class T>
class Sequence : public ISequence<T>
{
private:
    Vector<T> vector;
    
public:
    Sequence(size_t size = 0, T* dataPtr = nullptr) : vector(size, dataPtr) {}

    Sequence(std::initializer_list<T> initList) : vector(initList) {}

    Sequence(const Sequence<T>& sequence) : vector(sequence.vector) {}

    Sequence<T>& operator=(const Sequence<T>& other)
    {
        if (this != &other)
        {
            vector = other.vector;
        }
        return *this;
    }

    Sequence(Sequence<T>&& sequence) noexcept : vector(std::move(sequence.vector)) {}

    Sequence<T>& operator=(Sequence<T>&& sequence) noexcept
    {
        if (this != &sequence)
        {
            vector = std::move(sequence.vector);
        }
        return *this;
    }

    ~Sequence() override = default;

    T& operator[](size_t index) override 
    { 
        return vector[index]; 
    }

    const T& operator[](size_t index) const override 
    { 
        return vector[index]; 
    }
    
    T& getFirst() override 
    { 
        return vector.getFirst(); 
    }

    T& getLast() override 
    { 
        return vector.getLast(); 
    }

    T& get(size_t index) override 
    { 
        return vector.get(index); 
    }

    const T& getFirst() const override 
    { 
        return vector.getFirst(); 
    }

    const T& getLast() const override 
    { 
        return vector.getLast(); 
    }

    const T& get(size_t index) const override 
    { 
        return vector.get(index); 
    }

    size_t getSize() const override 
    { 
        return vector.getSize(); 
    }

    void set(const T& value, size_t index) override 
    { 
        vector.set(value, index); 
    }

    void prepend(const T& value) override 
    { 
        vector.prepend(value); 
    }

    void append(const T& value) override 
    { 
        vector.append(value); 
    }

    void insertAt(const T& value, size_t index) override 
    { 
        vector.insertAt(value, index); 
    }

    void removeFirst() override 
    { 
        vector.removeFirst(); 
    }

    void removeLast() override 
    { 
        vector.removeLast(); 
    }
    
    void removeAt(size_t index) override 
    { 
        vector.removeAt(index); 
    }

    bool empty() const
    {
        if (getSize() == 0)
        {
            return true;
        }
        return false;
    }

    void clear()
    {
        vector.clear();
    }
};