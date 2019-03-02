#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <exception>

#include "point.h"
#include "array.h"
#include "vector.h"
#include "list.h"
#include "benchmark.h"

using std::cin;
using std::cout;
using std::endl;

template <class T>
void Operation(T& t, const std::string& operation, bool interactive,
        std::ifstream& in) {
    Point p;
    int k;

    if (operation == "Append") {
        if (interactive) {
            cin >> p;
        }
        else {
            in >> p;
        }
        t.Append(p);
    } else

    if (operation == "Insert") {
        if (interactive) {
            cin >> p >> k;
        }
        else {
            in >> p >> k;
        }
        t.Insert(p, k);
    } else

    if (operation == "Remove") {
        if (interactive) {
            cin >> k;
        }
        else {
            in >> k;
        }
        t.Remove(k);
    } else

    if (operation == "Get") {
        if (interactive) {
            cin >> k;
        }
        else {
            in >> k;
        }
        std::cout << t.Get(k) << endl;
    } else

    if (operation == "Length") {
        std::cout << t.Length() << endl;
    } else

    if (operation == "Print") {
        t.Print();
    }
}

void Write(std::ofstream& out, const std::string& what) {
    out << std::endl << std::setw(26) << what << std::endl << std::endl;
    out << std::setw(9) << "#" << std::setw(12) << "array" << std::setw(12)
        << "vector" << std::setw(12) << "list" << std::endl;
}

int main() {
    Array array;
    Vector vector;
    List list;
    bool interactive = true;
    std::ifstream in (".../lab_2a_demo");

    std::string type;
    std::string operation;

    while (true) {

            cin >> operation;

            if (operation == "Stop") {
                return 0;
            }

            if (operation == "Demo") {
                interactive = false;
                while (true) {
                    in >> operation >> type;
                    if (in.eof()) return 0;
                    if (type == "array") {
                        Operation(array, operation, interactive, in);
                        std::cout << "OK" << endl;
                    } else if (type == "vector") {
                        Operation(vector, operation, interactive, in);
                        std::cout << "OK" << endl;
                    } else if (type == "list") {
                        Operation(list, operation, interactive, in);
                        std::cout << "OK" << endl;
                    }
                }
            }

            if (operation == "Benchmark") {
                std::ofstream out(".../lab_2a_benchmark.txt", std::ios::app);
                // 2^15 == 32768
                const int MAX = 32768;
                int n = 2;

                Write(out, "append");
                while (n <= MAX) {
                    Test(n, "append", array, vector, list);
                    n *= 2;
                }

                Write(out, "insert");
                n = 2;
                while (n <= MAX) {
                    Test(n, "insert", array, vector, list);
                    n *= 2;
                }


                Write(out, "get");
                n = 2;
                while (n <= MAX) {
                    Test(n, "get", array, vector, list);
                    n *= 2;
                }

                Write(out, "remove");
                n = 2;
                while (n <= MAX) {
                    Test(n, "remove", array, vector, list);
                    n *= 2;
                }
                return 0;
            }

            cin >> type;

            if (type == "array") {
                Operation(array, operation, interactive, in);
                std::cout << "OK" << endl;
            } else if (type == "vector") {
                Operation(vector, operation, interactive, in);
                std::cout << "OK" << endl;
            } else if (type == "list") {
                Operation(list, operation, interactive, in);
                std::cout << "OK" << endl;
            }
    }

}
