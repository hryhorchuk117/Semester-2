#pragma once

#include "flashsort.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <random>

int randomInt(int begin, int end) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return dis(gen);
}

std::vector<int> randomVector(int size) {
    std::vector<int> res;
    while (res.size() < size) {
        res.push_back(randomInt(-10000, 10000));
    }
    return res;
}

template <class T>
std::pair<double, double> testSort(std::vector<T>& vec) {
    std::pair<double, double> res;

    std::vector<T> copy = vec;
    auto start = std::chrono::high_resolution_clock::now();
    for (auto item : vec) {
        flashSort(item, begin(item), end(item));
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    res.first = elapsed.count();

    start = std::chrono::high_resolution_clock::now();
    for (auto item : vec) {
        std::sort(begin(item), end(item));
    }

    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;

    res.second = elapsed.count();

    return res;
}

void Benchmark(int n, std::vector<std::vector<int>>& vec) {
    if (vec.empty()) {
        vec.push_back(randomVector(10000));
    } else {
        for (int i = n / 2; i < n; ++i) {
            vec.push_back(randomVector(10000));
        }
    }
    std::fstream out("/home/hryhorchuk117/Semester-2/lab_3c/benchmark_3c.txt", std::ios::app);

    out  << std::setw(9) << n
         << std::setw(12) << testSort(vec).first
         << std::setw(12) << testSort(vec).second << std::endl;
}
