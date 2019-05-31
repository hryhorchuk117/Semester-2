#pragma once

#include "point.h"

#include <vector>

struct binary {
    explicit binary(const point& newPoint);

    point data;
    binary* left;
    binary* right;
};

class tree {
public:
    tree();

    binary* getRoot();

    void add(binary*, point);

    void addRandom(int);

    void erase(point);

    static std::vector<binary*> find(binary*, point, std::vector<binary*>&);

    static std::vector<binary*> find(binary*, point, std::vector<binary*>&, double);

    static void printInOrder(binary*);

    template <class func>
    void special(binary* curr, func f) {
        if (curr->left != nullptr) {
            special(curr->left, f);
        }

        f(curr);

        if (curr->right != nullptr) {
            special(curr->right, f);
        }
    }

private:
    binary* root;

    static binary* parent(binary*, binary*, std::vector<binary*>&);

    void addTree(binary*, binary*);
};