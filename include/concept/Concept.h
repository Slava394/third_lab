#pragma once

#include <concepts>


template <typename K>
concept Comparable = std::copyable<K> &&
requires(const K& a, const K& b) 
{
    { a < b } -> std::convertible_to<bool>;
    { a > b } -> std::convertible_to<bool>;
    { a == b } -> std::convertible_to<bool>;
};