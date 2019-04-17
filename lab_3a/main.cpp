#include "benchmark.h"
#include "sort.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    ifstream in("demo.txt");
    string type;

    cin >> type;

    if (type == "Demo") {
        while(true) {
            if (in.eof()) {
                return 0;
            }

            vector<int> vec;
            in >> vec;
            vector<vector<int>> vecs;
            for (int i = 0; i < 4; ++i) {
                vecs.push_back(vec);
            }


            cout << "vector : " << endl << vec << endl;

            cout << "selection sort : " << endl;
            selectionSort(vecs[0], begin(vecs[0]), end(vecs[0]), true);

            cout << "quick sort : " << endl;
            quickSort(vecs[1], begin(vecs[1]), end(vecs[1]), true);

            cout << "merge sort : " << endl;
            mergeSortIter(vecs[2], begin(vecs[2]), end(vecs[2]), true);

            cout << "combined sort : " << endl;
            combinedSort(vecs[3], begin(vecs[3]), end(vecs[3]), true);

            cout << endl;
        }
    }

    if (type == "Benchmark") {
        ofstream out("benchmark_3a.txt");
        out << std::setw(9) << "#" << std::setw(12) << "selection" << std::setw(12)
            << "quick" << std::setw(12) << "merge"<< std::setw(12)
            << "combined"<< std::setw(12) << "std::sort" << std::endl << std::endl;

        int N = 256;
        std::vector<std::vector<int>> vec;
        for (int i = 1; i <= N; i *= 2) {
            Benchmark(i, vec);
            cout << "OK, " << " i == " << i << endl;
        }
    }

    return 0;
}