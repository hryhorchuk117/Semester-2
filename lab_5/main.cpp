#include "graphEdges.h"
#include "graphMatrix.h"
#include "benchmark.h"

#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <iomanip>

using namespace std;

const int BENCHMARK = 64;

void write(const string& s, bool interactive) {
    if (interactive) {
        cout << s;
    }
}

template <class T>
void read(T& item, bool interactive, ifstream& in) {
    if (interactive) {
        cin >> item;
        return;
    }
    in >> item;
}

void writeOperations(bool interactive) {
    write("Choose the operation :\n\n", interactive);
    write("Create new     - 1\n", interactive);
    write("Create random  - 2\n", interactive);
    write("Add edge       - 3\n", interactive);
    write("Print          - 4\n", interactive);
    write("Components     - 5\n", interactive);
    write("Floyd          - 6\n", interactive);
    write("Spanning tree  - 7\n", interactive);
    write("Topological    - 8\n", interactive);
    write("Exit           - 0\n", interactive);
}

void writeBenchmark(std::ofstream& out) {
    out << setw(9) << "Vertices" << setw(9) << "Edges" << setw(12) << "Create" << setw(12) << "Matr_comp"
        << setw(12) << "Edges_comp" <<  setw(12) << "Matr_floyd" <<  setw(12)
        << "Edges_floyd" <<  setw(12) << "Matr_span" <<  setw(12) << "Edges_span\n";
}

int main() {

    ifstream in("demo.txt");
    string mode;
    bool interactive = true;
    cin >> mode;

    if (mode == "Benchmark") {
        std::ofstream out("benchmark.txt");
        writeBenchmark(out);
        benchmark(BENCHMARK);
        return 0;
    }

    if (mode == "Demo") {
        interactive = false;
    }

    graphMatrix testMatrix(0, false);
    graphEdges testEdges(0, false);

    while (true) {
        write("Choose graph type :\n", interactive);
        write("Matrix - 1\n", interactive);
        write("Edges  - 2\n", interactive);
        write("Exit   - 0\n\n", interactive);

        int type;
        read(type, interactive, in);

        if (type == 0) {
            return 0;
        }

        if (type == 1) {
            while (true) {
                writeOperations(interactive);
                int op;
                read(op, interactive, in);

                if (op == 0) {
                  break;
                }

                switch (op) {
                case 1: {
                    write("Insert the number of vertexes\n", interactive);
                    int vert;
                    read(vert, interactive, in);
                    write("Is this graph oriented?\n", interactive);
                    bool isOriented;
                    read(isOriented, interactive, in);

                    graphMatrix temp(vert, isOriented);
                    testMatrix = temp;

                    std::cout << "Created\n\n";
                    break;
                }

                case 2: {
                    write("insert the number of vertexes and edges\n", interactive);
                    int vert, edges;
                    read(vert, interactive, in);
                    read(edges, interactive, in);
                    write("Is this graph oriented?\n", interactive);
                    bool isOriented;
                    read(isOriented, interactive, in);

                    testMatrix = randomGraphMatr(vert, edges, isOriented);
                    std::cout << "Created\n\n";

                    break;
                }

                case 3: {
                    write("Insert 2 vertexes and the weight\n", interactive);
                    int vert1, vert2, weight;
                    read(vert1, interactive, in);
                    read(vert2, interactive, in);
                    read(weight, interactive, in);
                    addEdge(testMatrix, vert1, vert2, weight);

                    cout << "Added\n\n";
                    break;
                }

                case 4: {
                    printGraph(testMatrix);
                    std::cout << "\n";
                    break;
                }

                case 5: {
                    findComps(testMatrix);
                    std::cout << "\n";
                    break;
                }

                case 6: {
                    matr res;
                    floyd(testMatrix, res);
                    std::cout << "\n";

                    for (int i = 0; i < testMatrix.vertexNumber; ++i) {
                        for (int j = 0; j < testMatrix.vertexNumber; ++j) {
                            cout << res[i][j] << " ";
                        }
                        cout << "\n";
                    }

                    std::cout << "\n";
                    break;
                }

                case 7: {
                    graphMatrix tree = bfsTree(testMatrix);
                    printGraph(tree);

                    std::cout << "\n";
                    break;
                }

                case 8: {
                    auto vec = topologicalSort(testMatrix);
                    for (auto item : vec) {
                        cout << item << " ";
                    }
                    cout << "\n\n";
                    break;
                }

                default: std::cout << "Wrong operation!\n\n";

                }
            }
        }



        if (type == 2) {
            while (true) {
                writeOperations(interactive);
                int op;
                read(op, interactive, in);

                if (op == 0) {
                    break;
                }

                switch (op) {
                case 1: {
                    write("Insert the number of vertexes\n", interactive);
                    int vert;
                    read(vert, interactive, in);
                    write("Is this graph oriented?\n", interactive);
                    bool isOriented;
                    read(isOriented, interactive, in);

                    graphEdges temp(vert, isOriented);
                    testEdges = temp;

                    std::cout << "Created\n\n";
                    break;
                }

                case 2: {
                    write("insert the number of vertexes and edges\n", interactive);
                    int vert, edges;
                    read(vert, interactive, in);
                    read(edges, interactive, in);
                    write("Is this graph oriented?\n", interactive);
                    bool isOriented;
                    read(isOriented, interactive, in);

                    testEdges = randomGraphEdge(vert, edges, isOriented);
                    std::cout << "Created\n\n";

                    break;
                }

                case 3: {
                    write("Insert 2 vertexes and the weight\n", interactive);
                    int vert1, vert2, weight;
                    read(vert1, interactive, in);
                    read(vert2, interactive, in);
                    read(weight, interactive, in);
                    addEdge(testEdges, vert1, vert2, weight);

                    cout << "Added\n\n";
                    break;
                }

                case 4: {
                    printGraph(testEdges);
                    std::cout << "\n";
                    break;
                }

                case 5: {
                    findComps(testEdges);
                    std::cout << "\n";
                    break;
                }

                case 6: {
                    matr res;
                    floyd(testEdges, res);

                    for (int i = 0; i < testEdges.edges.size(); ++i) {
                        for (int j = 0; j < testEdges.edges.size(); ++j) {
                            cout << res[i][j] << " ";
                        }
                        cout << "\n";
                    }

                    std::cout << "\n\n";
                    break;
                }

                case 7: {
                    printGraph(bfsTree(testEdges));
                    break;
                }

                case 8: {
                    auto vec = topologicalSort(testEdges);
                    for (auto item : vec) {
                        cout << item << " ";
                    }
                    cout << "\n\n";
                    break;
                }

                default: std::cout << "Wrong operation!\n";

                }
            }
        }

    }
}
