#pragma once

#include <vector>
#include <time.h>
#include <random>
#include <chrono>
#include <iomanip>

#include "struct.h"
#include "database.h"

int RandomInt(int begin, int end) {
     std::random_device rd;
     std::mt19937_64 gen(rd());
     std::uniform_int_distribution<> dis(begin, end);
    return dis(gen);
}

std::string RandomString(int length)
{
    auto& letters = "abcdefghijklmnopqrstuvwxyz";

    std::string s;
    s.reserve(static_cast<unsigned long>(length));

    for (int i = 0; i < length; ++i) {
        s += letters[RandomInt(0, sizeof(letters) - 2)];
    }

    return s;
}

Date RandomDate() {
    Date d(RandomInt(1, 30), RandomInt(1, 12), RandomInt(1, 2018),
           RandomInt(0, 24), RandomInt(0, 60), RandomInt(0, 60));
    return d;
}

Monster RandomMonster() {
    Monster m{};
    m.name = RandomString(10);
    int health = RandomInt(0, 50000);
    m.health = health;
    m.attack = RandomInt(0, 1000);
    m.special = static_cast<double>(RandomInt(0, 100)) / 100;
    m.date = RandomDate();
    int type = RandomInt(0, 3);
    std::vector<std::string> vec = {"Increased_attack", "Double_attack",
                                    "Heal", "Paralyze"};
    m.type = vec[type];
    GetId(m);
    return m;
}

double TestAdd(Database& data, const std::vector<Monster>& vec) {
    std::vector<double> res;

    for (int i = 0; i < 10; ++i) {
        auto start = std::chrono::high_resolution_clock::now();

        for (const auto &item:vec) {
            data.Add(item);
        }

        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;

        res.push_back(elapsed.count());
    }

    double sum = 0;
    for (auto item : res) {
        sum += item/10;
    }
    return sum;
}

double TestFindName(Database& data, const std::string& name) {
    std::vector<double> res;

    for (int i = 0; i < 10; ++i) {
        auto start = std::chrono::high_resolution_clock::now();

        data.FindName(name);

        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;

        res.push_back(elapsed.count());
    }

    double sum = 0;
    for (auto item : res) {
        sum += item/10;
    }
    return sum;
}

double TestFindDate(Database& data, const Date& date) {
    std::vector<double> res;

    for (int i = 0; i < 10; ++i) {
        auto start = std::chrono::high_resolution_clock::now();

        data.FindDate(date);

        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;

        res.push_back(elapsed.count());
    }

    double sum = 0;
    for (auto item : res) {
        sum += item/10;
    }
    return sum;
}

void Benchmark(int n, const std::string& what) {
    std::ofstream out(".../lab_1_benchmark.txt", std::ios::app);
    Database_vec vec;
    Database_txt txt;
    Database_binary binary;
    vec.Clear();
    txt.Clear();
    binary.Clear();


    if (what == "add") {
        std::vector<Monster> monsters;
        monsters.reserve(static_cast<unsigned long>(n));
        for (int i = 0; i < n; ++i) {
            monsters.push_back(RandomMonster());
        }

        out  << std::setw(9) << n
             << std::setw(12) << TestAdd(vec, monsters)
             << std::setw(12) << TestAdd(txt, monsters)
             << std::setw(12) << TestAdd(binary, monsters) << std::endl;
    }

    if (what == "date") {
        Date date = RandomDate();
        out  << std::setw(9) << n
             << std::setw(12) << TestFindDate(vec, date)
             << std::setw(12) << TestFindDate(txt, date)
             << std::setw(12) << TestFindDate(binary, date) << std::endl;
    }

    if (what == "name") {
        std::string name = RandomString(RandomInt(1, 10));
        out  << std::setw(9) << n
             << std::setw(12) << TestFindName(vec, name)
             << std::setw(12) << TestFindName(txt, name)
             << std::setw(12) << TestFindName(binary,name) << std::endl;
    }
}
