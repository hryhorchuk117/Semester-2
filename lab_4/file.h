#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <tuple>
#include <algorithm>

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

std::ostream& operator << (std::ostream& out, date& d) {
    out << d.day << '/' << d.month << '/' << d.year;
    return out;
}

bool operator < (const date& lhs,const date& rhs) {
    return lhs.year*365 + lhs.month*30 + lhs.day < rhs.year*365 + rhs.month*30 + rhs.day;
}

std::pair<int, int> operator + (std::pair<int, int> lhs, std::pair<int, int> rhs) {
    lhs.first += rhs.first;
    lhs.second += rhs.second;
    return lhs;
}

struct fileNode {
    explicit fileNode(const std::string& newName, double newSize, const date& newDate) {
        this->name = newName;
        this->size = newSize;
        this->change = newDate;
    }

    std::string name = "";
    double size = 0;
    date change;

};

struct catalogNode {
    explicit catalogNode(const std::string& newName, const date& newDate) {
        this->name = newName;
        this->change = newDate;
        this->nextCatalog = {};
        this->nextFile = {};
    }

    std::string name = "";
    date change;
    std::vector<catalogNode*> nextCatalog;
    std::vector<fileNode*> nextFile;
};

double size(catalogNode* catalog) {
    double count = 0;
    for (auto& item : catalog->nextFile) {
        count += item->size;
    }
    for (auto& item : catalog->nextCatalog) {
        count += size(item);
    }

    return count;
}

void addCatalog(catalogNode* catalog, const std::string& name, date date) {
    auto newCatalog = new catalogNode(name, date);
    catalog->nextCatalog.push_back(newCatalog);
}

void addFile (catalogNode* catalog, const std::string& name, double size, date date) {
    auto newFile = new fileNode(name, size, date);
    catalog->nextFile.push_back(newFile);
}

std::vector<catalogNode*> findCatalogName(catalogNode* catalog, const std::string& name, std::vector<catalogNode*>& vec) {
    if (catalog->name == name) {
        //std::cout << catalog->name  << "==" << name << "\n";
        vec.push_back(catalog);
    }
    for (auto item : catalog->nextCatalog) {
        findCatalogName(item, name, vec);
    }
    return vec;
}

void printCatalog(catalogNode* catalog) {
    std::cout << catalog->name << " " << catalog->change << " (";
    for (auto item : catalog->nextCatalog) {
        printCatalog(item);
    }

    for (auto item : catalog->nextFile) {
        std::cout << item->name << " " << item->change << " " << item->size << "; ";
    }
    std::cout << " ) ";
}

std::pair<int,int> filesAndCatalogs(catalogNode* catalog) {
    std::pair<int, int> count = {0, 0};
    count.first  += catalog->nextFile.size();
    count.second += catalog->nextCatalog.size();

    for (auto item : catalog->nextCatalog) {
        count = count + filesAndCatalogs(item);
    }

    return count;
}

std::vector<date> allDates(catalogNode* catalog, std::vector<date>& dates) {
    dates.push_back(catalog->change);
    for (auto item : catalog->nextFile) {
        dates.push_back(item->change);
    }

    for(auto item : catalog->nextCatalog) {
        allDates(item, dates);
    }

    return dates;
}

std::pair<date, date> dateMinMax(catalogNode* catalog) {
    date min = {INT16_MAX, INT16_MAX, INT16_MAX};
    date max;

    std::vector<date> dates;
    dates = allDates(catalog, dates);
    std::sort(begin(dates), end(dates));
    return {dates[0], dates[dates.size() - 1]};
}

//help func for filterCatalog()
template <class Func>
void filterCatalogAdding(catalogNode* catalog, catalogNode*& newCatalog, Func func) {
    for (auto item : catalog->nextFile) {
        if (func(item)) {
            addFile(newCatalog, item->name, item->size, item->change);
        }
    }

    for (auto item : catalog->nextCatalog) {
        if (func(item)) {
            addCatalog(newCatalog, item->name, item->change);
        }
    }

    for (auto item : newCatalog->nextCatalog) {
        filterCatalogAdding(newCatalog, func);
    }
}


template <class Func>
catalogNode* filterCatalog(catalogNode* catalog, Func func) {
    auto *newCatalog = new catalogNode(catalog->name, catalog->change);
    for (auto item : catalog->nextFile) {
        if (func(item)) {
            addFile(newCatalog, item->name, item->size, item->change);
        }
    }

    for (auto item : catalog->nextCatalog) {
        if (func(item)) {
            addCatalog(newCatalog, item->name, item->change);
        }
    }

    for (auto item : newCatalog->nextCatalog) {
        filterCatalogAdding(newCatalog, func);
    }
}
