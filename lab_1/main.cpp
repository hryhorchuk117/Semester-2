#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "struct.h"
#include "binary.h"
#include "benchmark.h"
#include "database.h"

void Operation (Database& data, const std::string& operation,
        bool& interactive, std::ifstream& in) {

    if (operation == "Add") {
        Monster m;
        if (interactive) {
            std::cin >> m;
            GetId(m);
        }
        else {
            in >> m;
            GetId(m);
        }

        data.Add(m);
    }

    if (operation == "Print") {
        data.Print();
    }

    if (operation == "Delete") {
        Monster m;
        if (interactive) {
            std::cin >> m;
            std::cin >> m.id;
        }
        else {
            in >> m;
            in >> m.id;
        }
        data.Delete(m);
    }

    if (operation == "Clear") {
        data.Clear();
    }

    if (operation == "Change") {
        Monster m_prev, m_new;
        if (interactive) {
            std::cin >> m_prev >> m_prev.id;
            std::cin >> m_new;
            GetId(m_new);
        }
        else {
            in >> m_prev >> m_prev.id;
            in >> m_new;
            GetId(m_new);
        }
        data.Change(m_prev, m_new);
    }

    if (operation == "Find") {
        std::string find;
        if (interactive) {
            std::cin >> find;
        }
        else {
            in >> find;
        }
        std::cout << find << " ";
        std::cout << data.Find(find, interactive, in);
    }
}

void Write(std::ofstream& out, const std::string& what) {
    out << std::endl << std::setw(22) << what << std::endl << std::endl;
    out << std::setw(9) << "#" << std::setw(12) << "vec" << std::setw(12)
        << "txt" << std::setw(12) << "binary" << std::endl;
}

int main() {
    Database_vec vec;
    Database_txt txt;
    Database_binary binary;

    std::ifstream in(".../lab_1_demo.txt");
    std::string operation;
    std::string type;
    bool interactive = true;

    while (true) {
        std::cin >> operation;

        if (operation == "Stop") {
            return 0;
        }

        if (operation == "Demo") {
            interactive = false;
            while (true) {
                in >> operation;
                in >> type;

                if (in.eof()) {
                    return 0;
                }

                if (type == "vec") {
                    Operation(vec, operation, interactive, in);
                }
                if (type == "txt") {
                    Operation(txt, operation, interactive, in);
                }
                if (type == "binary") {
                    Operation(binary, operation, interactive, in);
                }
            }
        }

        if (operation == "benchmark") {
            std::ofstream out(".../lab_1_benchmark.txt", std::ios::app);
            const int MAX = 524290;
            int n = 2;

            Write(out, "add");
            while (n < MAX) {
                Benchmark(n, "add");
                n *= 2;
            }

            Write(out, "date");
            n = 2;
            while (n < MAX) {
                Benchmark(n, "date");
                n *= 2;
            }

            Write(out, "name");
            n = 2;
            while (n < MAX) {
                Benchmark(n, "name");
                n *= 2;
            }
            return 0;
        }

        std::cin >> type;

        if (type == "vec") {
            Operation(vec, operation, interactive, in);
        }
        if (type == "txt") {
            Operation(txt, operation, interactive, in);
        }
        if (type == "binary") {
            Operation(binary, operation, interactive, in);
        }
    }
}
