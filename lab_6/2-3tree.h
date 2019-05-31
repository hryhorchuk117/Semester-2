#pragma once

#include "point.h"

#include <vector>
#include <utility>

struct node23 {

    explicit node23(point);

    explicit node23(point, node23*);

    explicit node23(point, const std::vector<node23*>&, node23*);

    int size;
    std::vector<point> data;
    std::vector<node23*> next;
    node23* parent;

    void insertData(point);

    void eraseData(point);

    void becomeNode2(point, node23*, node23*);

    node23* insert(node23*, point);

    node23* insertRandom(int);

    node23* split(node23*);

    node23* find(node23*, point);

    std::vector<node23*> find(node23*, point, double, std::vector<node23*>&);

    void printInOrder(node23* curr);
};


