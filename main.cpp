#include "flashsort.h"
#include "benchmark.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

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
        T item;
        in >> item;
        vec.push_back(item);
    }
    return in;
}

int main() {

    vector<int> vec = {1, 4, 2, 5 ,3, 10, 6, 9, 8 ,7};
    flashSort(vec, begin(vec), end(vec));
    cout << vec << endl;

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
            cout << "vector: " << vec << endl;
            flashSort(vec, begin(vec), end(vec));
            cout << "sorted vector: " << vec << endl;
        }
    }

    if (type == "B") {
        ofstream out("/home/maksimka117/CLionProjects/Semester-2/lab_3c/benchmark_3c.txt");
        out << std::setw(9) << "#" << std::setw(12) << "flash" << endl;

        int N = 256;
        std::vector<std::vector<int>> vec;
        for (int i = 1; i <= N; i *= 2) {
            cout << i;
            Benchmark(i, vec);
            cout << i;
        }
    }

    return 0;
}