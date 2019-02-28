#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <string>

#include "struct.h"
#include "binary.h"

template <class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T> vec) {
    for (const auto& item : vec) {
        out << item << std::endl;
    }
    return out;
}


class Database {
public:
    std::vector<Monster> database;

    virtual void Add(const Monster& m) {};

    virtual void Print() {};

    virtual void Delete(const Monster& m) {};

    virtual void Clear() {};

    virtual void Change(const Monster& m_prev, const Monster& m_new) {};

    std::vector<Monster> Find(const std::string& find, bool& interactive,
        std::ifstream& in) {

        if (find == "name") {
            std::string name;
            if (interactive) {
                std::cin >> name;
            }
            else {
                in >> name;
            }
            return FindName(name);
        }
        else if (find == "type") {
            std::string type_m;
            if (interactive) {
                std::cin >> type_m;
            }
            else {
                in >> type_m;
            }
           return FindType(type_m);
        }
        else if (find == "attack") {
            int begin, end;
            if (interactive) {
                std::cin >> begin >> end;
            }
            else {
                in >> begin >> end;
            }
            return FindAttack(begin, end);
        }
        else if (find == "date") {
            Date date{};
            if (interactive) {
                std::cin >> date;
            }
            else {
                in >> date;
            }
            return FindDate(date);
        }
    }

    virtual std::vector<Monster> FindName(const std::string &name) {};
    virtual std::vector<Monster> FindType(const std::string &type) {};
    virtual std::vector<Monster> FindAttack(int begin, int end)      {};
    virtual std::vector<Monster> FindDate(const Date &date)        {};
private:

};


class Database_vec : public Database {
public:

    void Add(const Monster& m) override {
        database.push_back(m);
    }

    void Print() override {
        std::cout << database;
    }

    void Delete(const Monster& m) override {
        for (auto it = begin(database); it < end(database); ++it ) {
            if (*it == m) {
                database.erase(it);
            }
        }
    }

    void Clear() override {
        database = {};
    };

    void Change (const Monster& m_prev, const Monster& m_new) override {
        for (auto it = begin(database); it < end(database); ++it) {
            if (*it == m_prev) {
                *it = m_new;
                break;
            }
        }
    }

    std::vector<Monster> FindDate(const Date &date) override {
        std::vector<Monster> res;
        for (const auto& item : database) {
            if (item.date > date) {
                res.push_back(item);
            }
        }
        return res;
    }

    std::vector<Monster> FindAttack(int begin, int end) override {
        std::vector<Monster> res;
        for (const auto& item : database) {
            if (item.attack > begin && item.attack < end) {
                res.push_back(item);
            }
        }
        return res;
    }

    std::vector<Monster> FindType(const std::string &type) override {
        std::vector<Monster> res;
        for (const auto& item : database) {
            if (item.type == type) {
                res.push_back(item);
            }
        }
        return res;
    }

    std::vector<Monster> FindName(const std::string &name) override {
        std::vector<Monster> res;
        for (const auto& item : database) {
            bool same_name = true;
            for (int i = 0; i < name.size(); ++i) {
                if (name[i] != item.name[i]) {
                    same_name = false;
                    break;
                }
            }
            if (same_name) {
                res.push_back(item);
            }
        }
        return res;
    }

private:
    std::vector<Monster> database;


};

class Database_txt : public Database {
public:

    void Add(const Monster& m) override {
        std::ofstream out(path_txt, std::ios::app);
        out << m << std::endl;
    }

    void Print() override {
        Monster m;
        std::ifstream in(path_txt);
        while(true) {
            in >> m;
            in >> m.id;
            if (in.eof()) break;
            if (!m.name.empty())
            std::cout << m << std::endl;
        }
    }

    void Delete(const Monster& m) override {
        std::vector<Monster> database;
        database = Read_txt();
        for (auto it = begin(database); it < end(database); ++it ) {
            if (*it == m) {
                database.erase(it);
            }
        }
        Write_txt(database);
        database = {};
    }

    void Clear() override {
        std::ofstream out(path_txt);
    };

    void Change (const Monster& m_prev, const Monster& m_new) override {
        std::vector<Monster> database;
        database = Read_txt();
        for (auto it = begin(database); it < end(database); ++it ) {
            if (*it == m_prev) {
                *it = m_new;
                break;
            }
        }
        Write_txt(database);
    }

    std::vector<Monster> FindDate(const Date &date) override {
        std::ifstream in(path_txt);
        std::vector<Monster> res;
        Monster m;
        while(true) {
            in >> m;
            in >> m.id;
            if (in.eof()) break;
            if (m.date > date) {
                res.push_back(m);
            }
        }
        return res;
    }

    std::vector<Monster> FindAttack(int begin, int end) override {
        std::ifstream in(path_txt);
        std::vector<Monster> res;
        Monster m;
        while (true) {
            in >> m;
            in >> m.id;
            if (in.eof()) break;
            if (m.attack > begin && m.attack < end) {
                res.push_back(m);
            }
        }
        return res;
    }

    std::vector<Monster> FindType(const std::string &type) override {
        std::ifstream in(path_txt);
        std::vector<Monster> res;
        Monster m;
        while (true) {
            in >> m;
            in >> m.id;
            if (in.eof()) break;
            if (m.type == type) {
                res.push_back(m);
            }
        }
        return res;
    }

    std::vector<Monster> FindName(const std::string &name) override {
        std::ifstream in(path_txt);
        std::vector<Monster> res;
        Monster m;
        while (true) {
            in >> m;
            in >> m.id;
            if (in.eof()) break;
            bool same_name = true;
            for (int i = 0; i < name.size(); ++i) {
                if (name[i] != m.name[i]) {
                    same_name = false;
                    break;
                }
            }
            if (same_name) {
                res.push_back(m);
            }
        }
        return res;
    }

private:
    const std::string path_txt = "/home/maksimka117/CLionProjects/lab_1.txt";

    std::vector<Monster> Read_txt() {
        std::vector<Monster> database;
        database = {};
        Monster m;
        std::ifstream in(path_txt);
        while(true) {
            in >> m;
            in >> m.id;
            if (in.eof()) break;
            if (!m.name.empty()) {
                database.push_back(m);
            }
        }
        return  database;
    }

    void Write_txt(const std::vector<Monster>& database) {
        std::ofstream out(path_txt);
        out << database;
    }


};

class Database_binary : public Database {
public:
    void Add(const Monster& m) override {
        std::ofstream out(path_binary, std::ios::app | std::ios::binary);
        WriteBinary(m, out);
    }

    void Print() override {
        char c;
        std::ifstream in(path_binary, std::ios::binary);
        while(in.read((char*) &c, sizeof(c))) {
            Monster m = ReadBinary(in);
            std::cout << m << std::endl;
        }
    }

    void Delete(const Monster& del) override {
        std::vector<Monster> vec;
        char c;
        std::ifstream in(path_binary, std::ios::binary);
        while(in.read((char*) &c, sizeof(c))) {
            Monster m = ReadBinary(in);
            vec.push_back(m);
        }

        for (auto it = begin(vec); it < end(vec); ++it) {
            if (*it == del) {
                vec.erase(it);
            }
        }

        std::ofstream out(path_binary, std::ios::binary);
        for (const auto& item : vec) {
            WriteBinary(item, out);
        }
    }

    void Clear() override {
        std::ofstream out(path_binary, std::ios::binary);
    }

    void Change (const Monster& m_prev, const Monster& m_new) override {
        std::vector<Monster> vec;
        char c;
        std::ifstream in(path_binary, std::ios::binary);
        while(in.read((char*) &c, sizeof(c))) {
            Monster m = ReadBinary(in);
            vec.push_back(m);
        }

        for (auto it = begin(database); it < end(database); ++it ) {
            if (*it == m_prev) {
                *it = m_new;
                break;
            }
        }

        std::ofstream out(path_binary, std::ios::binary);
        for (const auto& item : vec) {
            WriteBinary(item, out);
        }
    }

    std::vector<Monster> FindDate(const Date &date) override {
        std::ifstream in(path_binary, std::ios::binary);
        std::vector<Monster> res;
        Monster m;
        char c;
        while(in.read((char*) &c, sizeof(c))) {
            m = ReadBinary(in);
            if (m.date > date) {
                res.push_back(m);
            }
        }
        return res;
    }

    std::vector<Monster> FindAttack(int begin, int end) override {
        std::ifstream in(path_binary, std::ios::binary);
        std::vector<Monster> res;
        char c;
        Monster m;
        while (in.read((char*) &c, sizeof(c))) {
            m = ReadBinary(in);
            if (m.attack > begin && m.attack < end) {
                res.push_back(m);
            }
        }
        return res;
    }

    std::vector<Monster> FindType(const std::string &type) override {
        std::ifstream in(path_binary, std::ios::binary);
        std::vector<Monster> res;
        Monster m;
        char c;
        while (in.read((char*) &c, sizeof(c))) {
            m = ReadBinary(in);
            if (m.type == type) {
                res.push_back(m);
            }
        }
        return res;
    }

    std::vector<Monster> FindName(const std::string &name) override {
        std::ifstream in(path_binary, std::ios::binary);
        std::vector<Monster> res;
        Monster m;
        char c;
        while (in.read((char*) &c, sizeof(c))) {
            m = ReadBinary(in);
            bool same_name = true;
            for (int i = 0; i < name.size(); ++i) {
                if (name[i] != m.name[i]) {
                    same_name = false;
                    break;
                }
            }
            if (same_name) {
                res.push_back(m);
            }
        }
        return res;
    }

private:
    std::string path_binary = "/home/maksimka117/CLionProjects/lab_1_binary.txt";


};