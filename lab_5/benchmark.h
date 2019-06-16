#include "graphMatrix.h"
#include "graphEdges.h"

#include <iostream>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <utility>

graphEdges convert(const graphMatrix& graph) {
    graphEdges res(graph.vertexNumber, graph.isOriented);
    for (int i = 0; i < graph.vertexNumber; ++i) {
        for (int j = 0; j < graph.vertexNumber; ++j) {
            if (graph.matrix[i][j] != 0) {
                addEdge(res, i, j, graph.matrix[i][j]);
            }
        }
    }

    return res;
}

double testCreate(int vert, int edges, bool matrix) {
    auto start = std::chrono::high_resolution_clock::now();

    if (matrix) {
        randomGraphMatr(vert, edges, false);
    } else randomGraphEdge(vert, edges, false);


    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    return elapsed.count();
}

template <class graphType>
double testComponents(graphType graph) {
    auto start = std::chrono::high_resolution_clock::now();

    findComps(graph);

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    return elapsed.count();
}

template <class graphType>
double testFloyd(graphType graph) {
    auto start = std::chrono::high_resolution_clock::now();

    matr temp;
    floyd(graph, temp);

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    return elapsed.count();
}

template <class graphType>
double testSpanning(graphType graph) {
    auto start = std::chrono::high_resolution_clock::now();

    bfsTree(graph);

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    return elapsed.count();
}


void benchmark(int n) {
    std::ofstream out("benchmark.txt", std::ios::app);

    for (int i = 4; i <= n; i*=2) {
        int MAX_EDGES = i * (i - 1) / 2;
        int currEdges = 0;
        for (int j = 0; j < 3; ++j) {
            currEdges += MAX_EDGES / 3;
            graphMatrix testMatrix = randomGraphMatr(i, currEdges, true);
            graphEdges testEdges = convert(testMatrix);
            out << std::setw(9) << i
                << std::setw(9) << currEdges
                << std::setw(12) << testCreate(i, currEdges, true)
                << std::setw(12) << testComponents(testMatrix)
                << std::setw(12) << testComponents(testEdges)
                << std::setw(12) << testFloyd(testMatrix)
                << std::setw(12) << testFloyd(testEdges)
                << std::setw(12) << testSpanning(testMatrix)
                << std::setw(12) << testSpanning(testEdges) << '\n';
        }
    }

}
