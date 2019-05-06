#pragma once

#include <string>
#include <iostream>
#include <sstream>

struct date {
    int day = 0;
    int month = 0;
    int year = 0;
};

std::istream& operator >> (std::istream& in, date& d) {
    std::string line;
    getline(in, line);
    std::stringstream ss{line};
    ss >> d.day;
    ss.ignore();
    ss >> d.month;
    ss.ignore();
    ss >> d.year;
    return in;
}

struct fileData {
    std::string name = "";
    double size = 0;
    date change = {0, 0, 0};
};

struct fileNode {
    explicit fileNode(const fileData& newData) {
        this->data = newData;
        this->next = {};
    }

    fileData data;
    std::vector<fileNode*> next;

};


double size(fileNode* head) {
    double count = head->data.size;
    for (auto item : head->next) {
        count += size(item);
    }
    return count;
}


