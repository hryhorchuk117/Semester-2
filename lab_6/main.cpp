#include "list.h"
#include "vector.h"
#include "binaryTree.h"
#include "avl.h"
#include "2-3tree.h"
#include "benchmark.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <iomanip>

const int BENCHMARK = 1048576 / 4;
//2 ^ 18

using namespace std;

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


void foo(avlNode* it) {
    it->data.xx++;
}

void writeBenchmark(ofstream& out) {
    out << setw(8) << '#'
        << setw(31) << "Add"
        << setw(55) << "Find"
        << setw(55) << "Find_mist"
        << setw(51) << "Print"
        << setw(55) << "Erase\n\n";

    out << setw(22) << "List"
        << setw(12) << "Vec"
        << setw(12) << "Tree"
        << setw(12) << "Avl";

    for (int i = 0; i < 4; ++i) {
        out << setw(17) << "List"
            << setw(12) << "Vec"
            << setw(12) << "Tree"
            << setw(12) << "Avl";
    }

    out << "\n\n";
}

int main() {
    ifstream in("demo.txt");
    string mode;
    bool interactive = true;
    cin >> mode;

    if (mode == "Benchmark") {
        ofstream out("benchmark.txt");
        writeBenchmark(out);
        benchmark(BENCHMARK);
        return 0;
    }

    if (mode == "Demo") {
        interactive = false;
    }


    list testList;
    vec testVec;
    tree testTree;
    avl testAvl;
    auto* test23 = new node23;

    while (true) {

        write("Choose the type of struct to test\n\n", interactive);
        write("List        -  1\n", interactive);
        write("Vector      -  2\n", interactive);
        write("Binary Tree -  3\n", interactive);
        write("AVL Tree    -  4\n", interactive);
        write("2-3 Tree    -  5\n", interactive);
        write("Exit        -  6\n\n", interactive);

        int type;
        read(type, interactive, in);

        if (type == 6) {
            return 0;
        }

        if (type == 1) {
            while (true) {

                write("Choose the operation :\n\n", interactive);
                write("Add node            -  1\n", interactive);
                write("Add k random nodes  -  2\n", interactive);
                write("Delete node         -  3\n", interactive);
                write("Print               -  4\n", interactive);
                write("Print in order      -  5\n", interactive);
                write("Exit                -  6\n\n", interactive);

                int op;
                read(op, interactive, in);

                if (op == 6) {
                    break;
                }

                switch (op) {
                    case 1: {

                        write("Enter the coordinates of point\n", interactive);
                        point p;
                        read(p, interactive, in);
                        testList.append(p);


                        cout << "Added\n";
                        break;
                    }

                    case 2: {
                        write("Enter the amount of elements\n", interactive);
                        int k;
                        read(k, interactive, in);
                        testList.addRandom(k);
                        cout << "Added\n";
                        break;
                    }

                    case 3: {
                        write("Enter the coordinates of point\n", interactive);
                        point p;
                        read(p, interactive, in);
                        testList.erase(p);

                        cout << "Deleted\n";
                        break;
                    }

                    case 4: {
                        testList.print();
                        cout << "\n";
                        break;
                    }

                    case 5: {
                        testList.printInOrder();
                        cout << "\n";
                        break;
                    }

                    default:
                        write("Wrong operation\n", interactive);
                }
            }


        }

        if (type == 2) {
            while (true) {

                write("Choose the operation :\n\n", interactive);
                write("Add element            -  1\n", interactive);
                write("Add k random elements  -  2\n", interactive);
                write("Delete element         -  3\n", interactive);
                write("Print                  -  4\n", interactive);
                write("Print in order         -  5\n", interactive);
                write("Exit                   -  6\n\n", interactive);

                int op;
                read(op, interactive, in);

                if (op == 6) {
                    break;
                }

                switch (op) {
                    case 1: {
                        write("Enter the coordinates of point\n", interactive);
                        point p;
                        read(p, interactive, in);
                        testVec.append(p);

                        cout << "Added\n";
                        break;
                    }

                    case 2: {
                        write("Enter the amount of elements\n", interactive);
                        int k;
                        read(k, interactive, in);
                        testVec.addRandom(k);
                        cout << "Added\n";
                        break;
                    }

                    case 3: {
                        write("Enter the coordinates of point\n", interactive);
                        point p;
                        read(p, interactive, in);
                        testVec.erase(p);

                        cout << "Deleted\n";
                        break;
                    }

                    case 4: {
                        testVec.print();
                        cout << "\n";
                        break;
                    }

                    case 5: {
                        testVec.printInOrder();
                        cout << "\n";
                        break;
                    }

                    default:
                        write("Wrong operation\n", interactive);
                }
            }
        }

        if (type == 3) {
            while (true) {

                write("Choose the operation :\n\n", interactive);
                write("Add element            -  1\n", interactive);
                write("Add k random elements  -  2\n", interactive);
                write("Delete element         -  3\n", interactive);
                write("Print in order         -  4\n", interactive);
                write("Exit                   -  5\n\n", interactive);

                int op;
                read(op, interactive, in);

                if (op == 5) {
                    break;
                }

                switch (op) {
                    case 1: {
                        write("Enter the coordinates of point\n", interactive);
                        point p;
                        read(p, interactive, in);
                        testTree.add(testTree.getRoot(), p);

                        cout << "Added\n";
                        break;
                    }

                    case 2: {
                        write("Enter the amount of elements\n", interactive);
                        int k;
                        read(k, interactive, in);
                        testTree.addRandom(k);
                        cout << "Added\n";
                        break;
                    }

                    case 3: {
                        write("Enter the coordinates of point\n", interactive);
                        point p;
                        read(p, interactive, in);
                        testTree.erase(p);

                        cout << "Deleted\n";
                        break;
                    }

                    case 4: {
                        testTree.printInOrder(testTree.getRoot());
                        cout << "\n";
                        break;
                    }

                    default:
                        write("Wrong operation\n", interactive);
                }
            }
        }

        if (type == 4) {
            while (true) {

                write("Choose the operation :\n\n", interactive);
                write("Add element            -  1\n", interactive);
                write("Add k random elements  -  2\n", interactive);
                write("Delete element         -  3\n", interactive);
                write("Print in order         -  4\n", interactive);
                write("Exit                   -  5\n\n", interactive);

                int op;
                read(op, interactive, in);

                if (op == 5) {
                    break;
                }

                switch (op) {
                    case 1: {
                        write("Enter the coordinates of point\n", interactive);
                        point p;
                        read(p, interactive, in);
                        testAvl.add(testAvl.getRoot(), p);

                        cout << "Added\n";
                        break;
                    }

                    case 2: {
                        write("Enter the amount of elements\n", interactive);
                        int k;
                        read(k, interactive, in);
                        testAvl.addRandom(k);
                        cout << "Added\n";
                        break;
                    }

                    case 3: {
                        write("Enter the coordinates of point\n", interactive);
                        point p;
                        read(p, interactive, in);
                        testAvl.erase(p);

                        cout << "Deleted\n";
                        break;
                    }

                    case 4: {
                        testAvl.printInOrder(testAvl.getRoot());
                        cout << "\n";
                        break;
                    }

                    default:
                        write("Wrong operation\n", interactive);
                }
            }
        }

        if (type == 5) {
            while (true) {

                write("Choose the operation :\n\n", interactive);
                write("Add element            -  1\n", interactive);
                write("Add k random elements  -  2\n", interactive);
                write("Delete element         -  3\n", interactive);
                write("Print in order         -  4\n", interactive);
                write("Exit                   -  5\n\n", interactive);

                int op;
                read(op, interactive, in);

                if (op == 5) {
                    break;
                }

                switch (op) {
                    case 1: {
                        write("Enter the coordinates of point\n", interactive);
                        point p;
                        read(p, interactive, in);
                        test23->insert(test23, p);

                        cout << "Added\n";
                        break;
                    }

                    case 2: {
                        write("Enter the amount of elements\n", interactive);
                        int k;
                        read(k, interactive, in);
                        test23->insertRandom(k);
                        cout << "Added\n";
                        break;
                    }

                    case 3: {
                        write("Enter the coordinates of point\n", interactive);
                        point p;
                        read(p, interactive, in);
                        test23->remove(test23, p);

                        cout << "Deleted\n";
                        break;
                    }

                    case 4: {
                        test23->printInOrder(test23);
                        cout << "\n";
                        break;
                    }

                    default:
                        write("Wrong operation\n", interactive);
                }
            }
        }
    }

}
