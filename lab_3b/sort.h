#pragma once

#include "struct.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <random>

std::vector<int> setPriorities() {
    std::cout << "Choose the priority of sorting: \n\n"
              << "Name - 1\n"
              << "Attack - 2\n"
              << "Health - 3\n"
              << "Type - 4\n"
              << "Special attack - 5\n"
              << "Date - 6\n";

    std::string temp{};
    getline(std::cin, temp);
    std::stringstream prior{temp};
    std::vector<int> res;
    while(prior) {
        int p;
        prior >> p;
        res.push_back(p);
    }
    res.pop_back();
    return res;
}

bool comparing(const Monster& lhs, const Monster& rhs, const std::vector<int>& pr) {
    int i = 0;
    while(i < pr.size()) {
        switch (pr[i]) {
            case 1 : {if (lhs.name != rhs.name) {return lhs.name > rhs.name;} break; }
            case 2 : {if (lhs.attack != rhs.attack) {return lhs.attack > rhs.attack;}break;}
            case 3 : {if (lhs.health != rhs.health) {return lhs.health > rhs.health;}break;}
            case 4 : {if (lhs.type != rhs.type) {return lhs.type > rhs.type;}break;}
            case 5 : {if (lhs.special != rhs.special) {return lhs.special > rhs.special;}break;}
            case 6 : {if (!(lhs.date == rhs.date)) {return lhs.date > rhs.date;} break;}
        }
        ++i;
    }
    std::cout << "out def\n";
    return false;
}


template <class iter>
void countingSort(std::vector<Monster>& vec, iter begin, iter end) {
    std::vector<int> temp(4);
    for (iter it = begin; it < end; ++it) {
        ++temp[it->type];
    }

    for (int i = 1; i < temp.size(); ++i) {
        temp[i] += temp[i - 1];
    }

    for (int i = temp.size() - 1; i >= 0; --i) {
        temp[i] = temp[i - 1];
    }
    temp[0] = 0;

    std::vector<Monster> res(end - begin);

    for (iter it = begin; it < end; ++it) {
        res[temp[it->type]] = *it;
        ++temp[it->type];
    }

    int j = 0;
    for (iter it = begin; it < end; ++it) {
        *it = res[j];
        ++j;
    }
}

int getNumber (int n, int k) {
    for (int i = 0; i < k; ++i) {
        n /= 10;
    }
    return n % 10;
}

template <class iter>
void radixSort(std::vector<Monster>& vec, iter begin, iter end) {
    int MAX = 50000;
    int k = 0;
    while(MAX != 0) {


        std::vector<int> temp(10);
        for (iter it = begin; it < end; ++it) {
            ++temp[getNumber(it->health, k)];
        }

        for (int i = 1; i < temp.size(); ++i) {
            temp[i] += temp[i - 1];
        }

        for (int i = temp.size() - 1; i >= 0; --i) {
            temp[i] = temp[i - 1];
        }
        temp[0] = 0;

        std::vector<Monster> res(end - begin);

        for (iter it = begin; it < end; ++it) {
            res[temp[getNumber(it->health, k)]] = *it;
            ++temp[getNumber(it->health, k)];
        }

        int j = 0;
        for (iter it = begin; it < end; ++it) {
            *it = res[j];
            ++j;
        }

        MAX /= 10;
        ++k;
    }

}