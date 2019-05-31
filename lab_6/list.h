#pragma once

#include "point.h"

#include <iostream>
#include <vector>
#include <algorithm>

struct node {

    explicit node(point);

    explicit node(point, node*);

    point value;
    node* next;
};

class list {
public:
    list();

    void append(point);

    void insert(point, int);

    void addRandom(int);

    int number(point);

    void remove(point);

    node* get(point);

    std::vector<node*> getVector(point, double);

    int lengthGet();

    void print();

    void printInOrder();

    template <class func>
    void special(func f) {
        std::vector<node*> allNodes;
        node* curr = head;
        while (curr) {
            allNodes.push_back(curr);
            curr = curr->next;
        }

        std::sort(begin(allNodes), end(allNodes),
                  [](node* lhs, node* rhs){return lhs->value < rhs->value;});

        for (auto item : allNodes) {
            f(item);
        }
    }

private:
    int length;
    node* head;

    node* getNode(int);
};
