#pragma once

#include "sort.h"
#include "struct.h"

#include <fstream>
#include <chrono>
#include <iomanip>
#include <algorithm>

Date randomDate() {
    Date d(randomInt(1, 30), randomInt(1, 12), randomInt(1, 2018),
           randomInt(0, 24), randomInt(0, 60), randomInt(0, 60));
    return d;
}

std::vector<Date> randomVector(int size) {
    std::vector<Date> res;
    while (res.size() < size) {
        res.push_back(randomDate());
    }
    return res;
}

template <class T, class func>
double testSort(std::vector<T> vec, func sort ) {
    auto start = std::chrono::high_resolution_clock::now();

    for (auto item : vec) {
        sort(item, begin(item), end(item), false);
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    return elapsed.count();
}

void Benchmark(int n, std::vector<std::vector<Date>>& vec) {
    if (vec.empty()) {
        vec.push_back(randomVector(10000));
    } else {
        for (int i = n / 2; i < n; ++i) {
            vec.push_back(randomVector(10000));
        }
    }
    std::fstream out("benchmark_3a.txt", std::ios::app);

    void (*selectionSort_ptr)(std::vector<Date>&, std::vector<Date>::iterator,
                std::vector<Date>::iterator, bool) = selectionSort;

    void (*quickSort_ptr)(std::vector<Date>&, std::vector<Date>::iterator,
                          std::vector<Date>::iterator, bool) = quickSort;

    void (*mergeSort_ptr)(std::vector<Date>&, std::vector<Date>::iterator,
                          std::vector<Date>::iterator, bool) = mergeSortIter;

    void (*combinedSort_ptr)(std::vector<Date>&, std::vector<Date>::iterator,
                             std::vector<Date>::iterator, bool) = combinedSort;

    void (*sort_ptr)(std::vector<Date>&, std::vector<Date>::iterator,
                     std::vector<Date>::iterator, bool) = sort_std;


    out  << std::setw(9) << n
         << std::setw(16) << testSort(vec, selectionSort_ptr) << "sec"
         << std::setw(16) << testSort(vec, quickSort_ptr) << "sec"
         << std::setw(16) << testSort(vec, mergeSort_ptr) << "sec"
         << std::setw(16) << testSort(vec, combinedSort_ptr) << "sec"
         << std::setw(16) << testSort(vec, sort_ptr) << "sec" << std::endl;
}
