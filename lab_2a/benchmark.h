#pragma once

#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <iomanip>

#include "point.h"
#include "array"
#include "vector"
#include "list.h"

int RandomInt(int begin, int end) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return dis(gen);
}

Point RandomPoint() {
    Point p;
    p.xx = static_cast<double>(RandomInt(-INT32_MAX, INT32_MAX)) / 100;
    p.yy = static_cast<double>(RandomInt(-INT32_MAX, INT32_MAX)) / 100;
    p.zz = static_cast<double>(RandomInt(-INT32_MAX, INT32_MAX)) / 100;
    return p;
}

template <class T>
double TestAppend(T& t, int n, const std::vector<Point>& vec) {
    auto start = std::chrono::high_resolution_clock::now();

    for (const auto &item:vec) {
        t.Append(item);
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    return elapsed.count();
}

template <class T>
double TestInsert(T t, int n, const std::vector<int>& pointers,
                               const std::vector<Point>& vec) {
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < n; ++i) {
        t.Insert(vec[i], pointers[i]);
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    return elapsed.count();
}

template <class T>
double TestRemove(T& t, int n, const std::vector<int>& pointers) {
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < n; ++i) {
        t.Remove(pointers[n - i]);
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    return elapsed.count();
}

template <class T>
double TestGet(T& t, int n, const std::vector<int>& pointers) {
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < n; ++i) {
        t.Get(pointers[i]);
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    return elapsed.count();
}

void Test(int n, const std::string& type,
        Array& array, Vector& vector, List& list) {
    std::ofstream out(".../lab_2a_benchmark.txt", std::ios::app);

    std::vector<Point> vec(static_cast<unsigned long>(n));
    for (int i = 0; i < n; ++i) {
        vec.push_back(RandomPoint());
    }

    std::vector<int> pointers(static_cast<unsigned long>(n));
    for (int i = 0; i < n; ++i) {
        pointers.push_back(RandomInt(0, n));
    }

    if (type == "append") {
        out << std::setw(9) << n
            << std::setw(12) << TestAppend(array, n, vec)
            << std::setw(12) << TestAppend(vector, n, vec)
            << std::setw(12) << TestAppend(list, n, vec) << std::endl;
    }

    if (type == "insert") {
        out << std::setw(9) << n
            << std::setw(12) << TestInsert(array, n, pointers, vec)
            << std::setw(12) << TestInsert(vector, n, pointers, vec)
            << std::setw(12) << TestInsert(list, n, pointers, vec) << std::endl;
    }

    if (type == "remove") {
        out << std::setw(9) << n
            << std::setw(12) << TestRemove(array, n, pointers)
            << std::setw(12) << TestRemove(vector, n, pointers)
            << std::setw(12) << TestRemove(list, n, pointers) << std::endl;
    }

    if (type == "get") {
        out << std::setw(9) << n
            << std::setw(12) << TestGet(array, n, pointers)
            << std::setw(12) << TestGet(vector, n, pointers)
            << std::setw(12) << TestGet(list, n, pointers) << std::endl;
    }
}
