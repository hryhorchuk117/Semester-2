// 4, 7, 16, 18, 21, 26

#include "tree.h"
#include "file.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void write(const string& s, bool interactive) {
    if (interactive) {
        cout << s;
    }
}

template <class T>
void read(T& item, bool interactive) {
    ifstream in("demo.txt");
    if (interactive) {
        cin >> item;
        return;
    }
    in >> item;
}

int main() {
    string type;
    cin >> type;
    bool interactive = true;
    if (type == "Demo") {
        interactive = false;
    }

    write("Enter the data for the first tree node\n", interactive);
    int dat;
    read(dat, interactive);
    auto *head = new node(dat);

    write("Enter the data for the first binary tree node\n", interactive);
    int datBinary;
    read(datBinary, interactive);
    auto *headBinary = new binaryNode(dat);

    while (true) {
        string treeType;
        read(treeType, interactive);
        if (treeType == "Exit") {
            return 0;
        }
        if (treeType == "bin") {
            write("Choose the operation :\n", interactive);
            write("Add node - 1\n", interactive);
            write("Print vector - 2\n", interactive);
            int op;
            read(op, interactive);
            switch(op) {
                case 1: {
                    write("Enter the data\n", interactive);
                    int data;
                    read(data, interactive);
                    addBinary(data, headBinary);
                    write("Added\n", interactive);
                    break;
                }
                case 2: {
                    vector<binaryTree> vec = presentation(headBinary, vec);
                    cout << vec << '\n';
                    break;
                }
                default: write("Wrong operation\n", interactive);
            }



        } else {
            write("Choose the operation :\n", interactive);
            write("Add node - 1\n", interactive);
            write("Print tree - 2\n", interactive);
            write("Delete node - 3\n", interactive);
            int op;
            read(op, interactive);
            switch(op) {
                case 1: {
                    write("Enter the data and probability 'p'\n", interactive);
                    double p;
                    int data;
                    read(data, interactive);
                    read(p, interactive);
                    addNode(data, p, head);
                    write("Added\n", interactive);
                    break;
                }
                case 2: {
                    printTree(head);
                    cout << '\n';
                    break;
                }
                case 3: {
                    write("Enter the data and probability 'p'\n", interactive);
                    double p;
                    int data;
                    read(data, interactive);
                    read(p, interactive);
                    deleteNode(head, data, p);
                    write("Deleted\n", interactive);
                    break;
                }
                default: write("Wrong operation\n", interactive);
            }
        }
    }
}
