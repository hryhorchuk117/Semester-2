#pragma once

#include <vector>
#include <math.h>
#include <iostream>

template <class iter>
void swapIter(iter& lhs, iter& rhs) {
    auto temp = *lhs;
    *lhs = *rhs;
    *rhs = temp;
}

template <class T, class iter>
void insertionSort(std::vector<T>& vec, iter begin, iter end) {
    for (auto it = begin; it < end; ++it) {
        iter curr = it;

        while (curr > begin) {
            iter prev = curr - 1;
            if (*curr < *prev) {
               swapIter(curr, prev);
            } else break;

            --curr;
        }
    }
}


template <class T, class iter>
void flashSort(std::vector<T>& vec, iter begin, iter end) {
    T min = *begin, max = *begin;
    iter it_max = begin;
    const int m = round(0.42*(end - begin));

    for (auto it = begin; it < end; ++it) {

        if (*it > max) {
            max = *it;
            it_max = it;
        }

        if (*it < min) {
            min = *it;
        }
    }

    if (max == min) {
        return;
    }

    const double c = ((double)(m - 1)) / (max - min);

    std::vector<T> temp(m);

    for (iter it = begin; it < end; ++it) {
        int k = (int)(c*(*it - min));
        ++temp[k];
    }

    for (int i = 1; i < temp.size(); ++i) {
        temp[i] += temp[i - 1];
    }

    swapIter(begin, it_max);

    int count = 0;
    int flash = 0, j = 0, k = m - 1;


    while (count < (begin - end) - 1) {
        while (j > (temp[k] - 1)) {
            j++;
            k = (int) (c * (vec[j] - min));
        }
        flash = vec[j];
        while (j != temp[k]) {
            k = (int) (c * (flash - min));

            int hold = vec[temp[k] - 1];
            vec[temp[k] - 1] = flash;
            flash = hold;

            --temp[k];
            ++count;
        }
    }

    insertionSort(vec, begin, end);
}

