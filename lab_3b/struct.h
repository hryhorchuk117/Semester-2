#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <tuple>
#include <vector>
#include <fstream>

struct Time {
    int hour;
    int minute;
    int second;
};

struct Date {
    Date () {}

    Date (int day_new, int month_new, int year_new,
          int hour_new, int minute_new, int second_new) {
        day = day_new;
        month = month_new;
        year = year_new;
        time.hour = hour_new;
        time.minute = minute_new;
        time.second = second_new;
    }

    int day;
    int month;
    int year;
    Time time;
};

struct Monster {
    std::string name;
    int attack;
    int health;
    int type;
    double special;
    Date date;
    int id;
};

std::ostream& operator<<  (std::ostream&, const Date&);
std::ostream& operator<<  (std::ostream&, const Monster&);
std::istream& operator>>  (std::istream&, Date&);
std::istream& operator>>  (std::istream&, Monster&);
bool          operator==  (const Date&, const Date&);
bool          operator==  (const Monster&, const Monster&);
bool          operator>   (const Date&, const Date&);

void GetId(Monster& m) {
    std::ifstream id_in("lab_3b_id.txt");
    id_in >> m.id;

    if (m.id == INT32_MAX) {
        m.id = 0;
    }

    ++m.id;
    std::ofstream id_out("/lab_3b_id.txt");
    id_out << m.id;
}

std::ostream& operator<< (std::ostream &out, const Date &d) {
    out << d.day << "/" << d.month << "/" << d.year << " "
        << d.time.hour << ":" << d.time.minute << ":" << d.time.second;
    return out;
}

std::ostream& operator<< (std::ostream &out, const Monster &m) {
    out << m.name << " " << m.attack << " " << m.health << " " <<  m.type
        << " " << m.special << " " << m.date << " " << m.id;
    return out;
}

std::istream& operator>> (std::istream& in, Date& d) {
    std::string date, time;
    in >> date >> time;
    std::stringstream ss_date{date} , ss_time{time};
    ss_date >> d.day; ss_date.ignore();
    ss_date >> d.month; ss_date.ignore();
    ss_date >> d.year;

    ss_time >> d.time.hour; ss_time.ignore();
    ss_time >> d.time.minute; ss_time.ignore();
    ss_time >> d.time.second;
    return in;
}

std::istream& operator >> (std::istream& in, Monster& m) {
    in >> m.name >> m.attack  >> m.health
       >> m.type >> m.special >> m.date;
    return in;
}

bool operator==(const Date& lhs, const Date& rhs) {
    return
            std::tie(lhs.year, lhs.month, lhs.day, lhs.time.second, lhs.time.minute, lhs.time.hour) ==
            std::tie(rhs.year, rhs.month, rhs.day, rhs.time.second, rhs.time.minute, rhs.time.hour);
}

bool operator==(const Monster& lhs, const Monster& rhs) {
    return
            std::tie(lhs.type, lhs.date, lhs.special, lhs.health, lhs.attack, lhs.name, lhs.id) ==
            std::tie(rhs.type, rhs.date, rhs.special, rhs.health, rhs.attack, rhs.name, rhs.id);
}

bool operator>(const Date& lhs, const Date& rhs) {
    int days_difference = (lhs.year - rhs.year) * 360 +
                          (lhs.month - rhs.month) * 30 + lhs.day - rhs.day;
    if (days_difference > 0) {
        return true;
    }

    if (days_difference < 0) {
        return false;
    }

    return lhs.time.hour * 3600 + lhs.time.minute * 60 + lhs.time.second >
           rhs.time.hour * 3600 + rhs.time.minute * 60 + rhs.time.second;
}
