#pragma once

#include <string>
#include <iostream>
#include <sstream>

struct date {
    int day = 0;
    int month = 0;
    int year = 0;
};

std::istream operator >> (std::istream& in, date& d) {
    std::string line;
    getline(in, line);
    std::stringstream ss{line};

}

struct catalogData {
    std::string name = "";
    double size = 0;
    date change = {0, 0, 0};
};

struct catalogNode {
    catalogNode(const catalogData& newData) {
        this->data = newData;
        this->next = {};
    }

    catalogData data;
    std::vector<catalogNode*> next;
};

class catalog {
public:
    catalog() {
        std::cout << "Create the catalog :\n";
        std::string newName;
        date newDate;
        double newSize;
        std::cin >> newName >> newDate >> newSize;
    }
    int size( ) {
        int count = 1;
        for (auto item)

    }
private:
    catalogNode head;
};
