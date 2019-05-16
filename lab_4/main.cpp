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
void read(T& item, bool interactive, ifstream& in) {

    if (interactive) {
        cin >> item;
        return;
    }
    in >> item;
}

int main() {
    ifstream in("/home/hryhorchuk117/CLionProjects/lab4/demo.txt");
    string type;
    cin >> type;
    bool interactive = true;
    if (type == "Demo") {
        interactive = false;
    }

    write("Enter the data for the first tree node\n", interactive);
    int dat;
    read(dat, interactive, in);
    auto *head = new node(dat);

    write("Enter the data for the first binary tree node\n", interactive);
    int datBinary;
    read(datBinary, interactive, in);
    auto *headBinary = new binaryNode(dat);

    write("Enter the name and the date of the first catalog\n", interactive);
    string name;
    date d;
    read(name, interactive, in);
    read(d, interactive, in);
    auto *catalog = new catalogNode(name, d);

    while (true) {
        write("Choose the type of struct to test\n", interactive);
        write("Binary tree - 1\n", interactive);
        write("Tree - 2\n", interactive);
        write("Catalog - 3\n", interactive);
        write("Exit - 4\n", interactive);

        int treeType;
        read(treeType, interactive, in);
        if (treeType == 4) {
            return 0;
        }
        if (treeType == 1) {
            write("Choose the operation :\n", interactive);
            write("Add node - 1\n", interactive);
            write("Print vector - 2\n", interactive);
            int op;
            read(op, interactive, in);
            switch(op) {
                case 1: {
                    write("Enter the data\n", interactive);
                    int data;
                    read(data, interactive, in);
                    addBinary(data, headBinary);
                    cout << "Added\n";
                    break;
                }
                case 2: {
                    vector<binaryTree> vec;
                    vec = presentation(headBinary, vec);
                    cout << vec << '\n';
                    break;
                }
                default: write("Wrong operation\n", interactive);
            }



        } if (treeType == 2) {
            write("Choose the operation :\n", interactive);
            write("Add node - 1\n", interactive);
            write("Print tree - 2\n", interactive);
            write("Delete node - 3\n", interactive);
            int op;
            read(op, interactive, in);
            switch(op) {
                case 1: {
                    write("Enter the data and probability 'p'\n", interactive);
                    double p;
                    int data;
                    read(data, interactive, in);
                    read(p, interactive, in);
                    addNode(data, p, head);
                    cout << "Added\n";
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
                    read(data, interactive, in);
                    read(p, interactive, in);
                    deleteNode(head, data, p);
                    cout << "Deleted\n";
                    break;
                }
                default: write("Wrong operation\n", interactive);
            }
        }
        if (treeType == 3) {
            write("Choose the operation :\n", interactive);
            write("Add catalog - 1\n", interactive);
            write("Add file - 2\n", interactive);
            write("Print catalog - 3\n", interactive);
            write("Size - 4\n", interactive);
            write("Min and Max date - 5\n", interactive);
            write("Number of files and catalogs - 6\n", interactive);

            int op;
            read(op, interactive, in);

            switch (op) {
                case 1: {
                    write("Enter the name and the date of the new catalog\n", interactive);
                    string newName;
                    date newDate;
                    read(newName, interactive, in);
                    read(newDate, interactive, in);
                    write("Enter the catalog to add a new one\n", interactive);
                    string nameParent;
                    read(nameParent, interactive, in);
                    vector<catalogNode*> vec;
                    vector<catalogNode*> parent = findCatalogName(catalog, nameParent, vec);
                    //cout << parent.size() << ' ' << parent[0]->name << "==" << nameParent << "\n";
                    addCatalog(parent[0], newName, newDate);
                    cout << "Added\n";
                    break;
                }
                case 2: {
                    write("Enter the name, the size and the date of the new file\n", interactive);
                    string newName;
                    double newSize;
                    date newDate;
                    read(newName, interactive, in);
                    read(newSize, interactive, in);
                    read(newDate, interactive, in);
                    write("Enter the catalog to add a new one\n", interactive);
                    string nameParent;
                    read(nameParent, interactive, in);
                    vector<catalogNode*> vec;
                    vector<catalogNode*> parent = findCatalogName(catalog, nameParent, vec);
                    addFile(parent[0], newName, newSize, newDate);
                    cout << "Added\n";
                    break;
                }
                case 3: {
                    printCatalog(catalog);
                    cout << "\n";
                    break;
                }
                case 4: {
                    cout << size(catalog) << "\n";
                    break;
                }
                case 5: {
                    pair<date, date> res = dateMinMax(catalog);
                    cout << res.first << "\n" << res.second << "\n";
                    break;
                }
                case 6: {
                    pair<int, int> res = filesAndCatalogs(catalog);
                    cout << res.first << " " << ++res.second << "\n";
                    break;
                }
                default: write("Wrong operation\n", interactive);
            }
        }
    }
}
