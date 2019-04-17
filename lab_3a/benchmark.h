#pragma once

#include "sort.h"

#include <fstream>
#include <chrono>
#include <iomanip>
#include <algorithm>


std::vector<int> randomVector(int size) {
    std::vector<int> res;
    while (res.size() < size) {
        res.push_back(randomInt(-100000, 100000));
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

void Benchmark(int n, std::vector<std::vector<int>>& vec) {
    if (vec.empty()) {
        vec.push_back(randomVector(10000));
    } else {
        for (int i = n / 2; i < n; ++i) {
            vec.push_back(randomVector(10000));
            //std::cout << "vec.size == " << vec.size() << std::endl;
        }
    }
        //std::cout << "size == " << vec.size() << std::endl;
    std::fstream out("benchmark_3a.txt", std::ios::app);

    void (*selectionSort_ptr)(std::vector<int>&, std::vector<int>::iterator,
                std::vector<int>::iterator, bool) = selectionSort;

    void (*quickSort_ptr)(std::vector<int>&, std::vector<int>::iterator,
                              std::vector<int>::iterator, bool) = quickSort;

    void (*mergeSort_ptr)(std::vector<int>&, std::vector<int>::iterator,
                          std::vector<int>::iterator, bool) = mergeSortIter;

    void (*combinedSort_ptr)(std::vector<int>&, std::vector<int>::iterator,
                          std::vector<int>::iterator, bool) = combinedSort;

    void (*sort_ptr)(std::vector<int>&, std::vector<int>::iterator,
                     std::vector<int>::iterator, bool) = sort_std;


    //std::cout << "OUT" << std::endl;

    out  << std::setw(9) << n
         << std::setw(12) << testSort(vec, selectionSort_ptr)
         << std::setw(12) << testSort(vec, quickSort_ptr)
         << std::setw(12) << testSort(vec, mergeSort_ptr)
         << std::setw(12) << testSort(vec, combinedSort_ptr)
         << std::setw(12) << testSort(vec, sort_ptr) << std::endl;
}