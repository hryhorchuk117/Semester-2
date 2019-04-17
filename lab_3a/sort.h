#pragma once

#include "benchmark.h"

#include <vector>
#include <iostream>
#include <algorithm>
#include <random>

template <class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T> vec) {
    for (auto item : vec) {
        out << item << " ";
    }
    return out;
}

template <class T>
std::istream& operator>>(std::istream& in, std::vector<T>& vec) {
    int n;
    in >> n;
    for (int i = 0; i < n; ++i) {
        int item;
        in >> item;
        vec.push_back(item);
    }
    return in;
}

int randomInt(int begin, int end) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return dis(gen);
}

template <class T, class iter>
void selectionSort(std::vector<T>& vec, iter begin, iter end, bool print) {
    for (iter j = begin; j < end - 1; ++j) {
        if (print) {
            std::cout << vec << std::endl;
        }
        T min = *j;
        iter min_it = j;
        for (auto it = j; it < end; ++it) {

            if (*it < min) {
                min_it = it;
                min = *it;
            }
        }
        vec.erase(min_it);
        vec.insert(j, min);
    }
    if (print) {
        std::cout << vec << std::endl;
    }
}

template <class iter>
void swap_iter(iter& lhs, iter& rhs) {
    auto temp = *rhs;
    *rhs = *lhs;
    *lhs = temp;
}

template <class T, class iter>
iter partition(std::vector<T>& vec, iter begin, iter end)
{
    int size = end - begin - 1;
    int r = randomInt(0, size);
    iter random = r + begin;

    iter pivot = end - 1;
    swap_iter(random, pivot);

    iter i = begin;
    for (iter j = begin; j <= end - 2; j++) {
        if (*j <= *pivot) {
            swap_iter(i, j);
            ++i;
        }
    }

    iter new_pivot = i;
    swap_iter(new_pivot, pivot);
    return new_pivot;
}


template <class T, class iter>
void quickSort(std::vector<T>& vec, iter begin, iter end, bool print) {
    if (begin < end) {
        iter pivot = partition(vec, begin, end);

        if (print) {
            std::cout << vec << std::endl;
        }

        quickSort(vec, begin, pivot, print);
        quickSort(vec, pivot + 1, end, print);
    }
}

template <class T>
void merge(std::vector<T>& vec, int iLeft, int iRight, int iEnd, std::vector<T>& temp) {
    int i = iLeft, j = iRight;
    for (int k = iLeft; k < iEnd; k++) {
        if (i < iRight && (j >= iEnd || vec[i] <= vec[j])) {
            temp[k]= vec[i];
            i = i + 1;
        } else {
            temp[k] = vec[j];
            j = j + 1;
        }
    }
}

template <class T>
void mergeSort(std::vector<T>& vec, std::vector<T>& temp, bool print) {
    for (int width = 1; width < vec.size(); width = 2 * width) {
        for (int i = 0; i < vec.size(); i = i + 2 * width) {

            if (print) {
                std::cout << vec << std::endl;
            }

            merge(vec, i, std::min(i + width, (int)vec.size()),
                  std::min(i + 2 * width, (int)vec.size()), temp);
        }
        vec = temp;
    }
}

template <class T, class iter>
void mergeSortIter(std::vector<T>& vec, iter begin, iter end, bool print) {
    std::vector<T> new_vec;
    for (auto it = begin; it < end; ++it) {
        new_vec.push_back(*it);
    }

    std::vector<T> temp(new_vec.size());
    mergeSort(new_vec, temp, print);

    int j = 0;
    for (auto it = begin; it < end; ++it) {
        *it = new_vec[j];
        ++j;
    }

    if (print) {
        std::cout << vec << std::endl;
    }
}

template <class T, class iter>
void combinedSort(std::vector<T>& vec, iter begin, iter end, bool print) {
    const int N = 10;

    if (begin < end) {
        iter pivot = partition(vec, begin, end);

        if (print) {
            std::cout << vec << std::endl;
        }

        if (abs(pivot - begin) <= N) {
            selectionSort(vec, begin, pivot, print);
        } else {
            combinedSort(vec, begin, pivot, print);
        }

        if (abs(end - pivot - 1) <= N) {
            selectionSort(vec, pivot + 1, end, print);
        } else {
            combinedSort(vec, pivot + 1, end, print);
        }

    }
}

template <class T, class iter>
void sort_std(std::vector<T>& vec, iter begin, iter end, bool print) {
    std::sort(vec.begin(), vec.end());
}