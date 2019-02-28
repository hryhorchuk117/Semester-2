#pragma once

#include <fstream>
#include <vector>

#include "struct.h"

std::string ReadStringBinary (std::ifstream&);
Date ReadDateBinary (std::ifstream&);
Monster ReadBinary (std::ifstream&);

void WriteStringBinary (const std::string&, std::ofstream&);
void WriteDateBinary (const Date&, std::ofstream&);
void WriteBinary (const Monster&, std::ofstream&);

std::string ReadStringBinary(std::ifstream& in) {
    std::string res;
    char symbol{};
    in.read((char*) &symbol, sizeof(symbol));
    while(symbol != ' ') {
        res += symbol;
        in.read((char*) &symbol, sizeof(symbol));
    }
    return res;
}

Date ReadDateBinary(std::ifstream& in) {
    std::vector<int> v;
    for (int i = 0; i < 6; ++i) {
        int element{};
        in.read((char*) &element, sizeof(element));
        v.push_back(element);
    }

    Date d(v[0], v[1], v[2], v[3], v[4], v[5]);
    return d;
}

Monster ReadBinary (std::ifstream& in) {
    Monster m;
    char c;
    m.name = ReadStringBinary(in);

    int attack{};
    in.read((char*) &attack, sizeof(attack));
    m.attack = attack;

    int health{};
    in.read((char*) &health, sizeof(health));
    m.health = health;

    m.type = ReadStringBinary(in);

    double special{};
    in.read((char*) &special, sizeof(special));
    m.special = special;

    m.date = ReadDateBinary(in);

    int id;
    in.read((char*) &id, sizeof(id));
    m.id = id;

    return m;
}

void WriteStringBinary (const std::string& s, std::ofstream& out) {
    for (auto symbol : s) {
        out.write((char*) &symbol, sizeof(symbol));
    }
    char space = ' ';
    out.write((char*) &space, sizeof(space));
}

void WriteDateBinary (const Date& d, std::ofstream& out) {

    out.write((char*) &d.day, sizeof(d.day));
    out.write((char*) &d.month, sizeof(d.month));
    out.write((char*) &d.year, sizeof(d.year));

    out.write((char*) &d.time.hour, sizeof(d.time.hour));
    out.write((char*) &d.time.minute, sizeof(d.time.minute));
    out.write((char*) &d.time.second, sizeof(d.time.second));
}

void WriteBinary (const Monster& m, std::ofstream& out) {
    char pointer = '*';
    out.write(&pointer, sizeof(pointer));
    WriteStringBinary (m.name, out);
    out.write((char*) &m.attack, sizeof(m.attack));
    out.write((char*) &m.health, sizeof(m.health));
    WriteStringBinary (m.type, out);
    out.write((char*) &m.special, sizeof(m.special));
    WriteDateBinary   (m.date, out);
    out.write((char*) &m.id, sizeof(m.id));
}
