#include "benchmark.h"

#include <fstream>
#include <iomanip>
#include <chrono>
#include <vector>

template <class type>
double testAdd(type& test, int k) {
    auto start = std::chrono::high_resolution_clock::now();

    test.addRandom(k);

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    return elapsed.count();
}

template <class type>
double testFind(type& test, point p) {
    auto start = std::chrono::high_resolution_clock::now();

    test.find(p);

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    return elapsed.count();
}

template <class type>
double testFindMist(type& test, point p, double m) {
    auto start = std::chrono::high_resolution_clock::now();

    test.find(p, m);

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    return elapsed.count();
}

template <class type, class vec>
double testFindTree(type& test, point p, vec& res) {
    auto start = std::chrono::high_resolution_clock::now();

    test.find(test.getRoot(), p, res);

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    return elapsed.count();
}

template <class type, class vec>
double testFindMistTree(type& test, point p, vec& res, double m) {
    auto start = std::chrono::high_resolution_clock::now();

    test.find(test.getRoot(), p, res, m);

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    return elapsed.count();
}

template <class type>
double testErase(type& test, point p) {
    auto start = std::chrono::high_resolution_clock::now();

    test.erase(p);

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    return elapsed.count();
}

template <class type>
double testPrint(type& test) {
    auto start = std::chrono::high_resolution_clock::now();

    test.printInOrder();

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    return elapsed.count();
}

template <class type>
double testPrintTree(type& test) {
  auto start = std::chrono::high_resolution_clock::now();

  test.printInOrder(test.getRoot());

  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;

  return elapsed.count();
}

void benchmark(int n) {
    std::ofstream out("/home/hryhorchuk117/CLionProjects/lab6/benchmark.txt", std::ios::app);
    for (int i = 1; i <= n; i*=2) {
        list testList;
        vec testVec;
        tree testTree;
        avl testAvl;

        std::vector<binary*> findTree;
        std::vector<avlNode*> findAvl;

        out << std::setw(8) << i
            << std::setw(17) << testAdd(testList, i)
            << std::setw(12) << testAdd(testVec, i)
            << std::setw(12) << testAdd(testTree, i)
            << std::setw(12) << testAdd(testAvl, i);

        testList.insert({100, 200, 300}, i / 2);
        testVec.append( {100, 200, 300});
        testTree.add(testTree.getRoot(), {100, 200, 300});
        testAvl.add(testAvl.getRoot(), {100, 200, 300});

        out << std::setw(17) << testFind(testList, {100, 200, 300})
            << std::setw(12) << testFind(testVec, {100, 200, 300})
            << std::setw(12) << testFindTree(testTree, {100, 200, 300}, findTree)
            << std::setw(12) << testFindTree(testAvl, {100, 200, 300}, findAvl)

            << std::setw(17) << testFindMist(testList, {100, 200, 300}, 100)
            << std::setw(12) << testFindMist(testVec, {100, 200, 300}, 100)
            << std::setw(12) << testFindMistTree(testTree, {100, 200, 300}, findTree, 100)
            << std::setw(12) << testFindMistTree(testAvl, {100, 200, 300}, findAvl, 100)

            << std::setw(17) << testPrint(testList)
            << std::setw(12) << testPrint(testVec)
            << std::setw(12) << testPrintTree(testTree)
            << std::setw(12) << testPrintTree(testAvl)

            << std::setw(17) << testErase(testList, {100, 200, 300})
            << std::setw(12) << testErase(testVec, {100, 200, 300})
            << std::setw(12) << testErase(testTree, {100, 200, 300})
            << std::setw(12) << testErase(testAvl, {100, 200, 300});

        out << '\n';
    }

}