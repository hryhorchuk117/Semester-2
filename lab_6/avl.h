#pragma once

#include "point.h"

#include <vector>

struct avlNode {
    explicit avlNode(const point &newPoint);

    point data;
    int height;
    avlNode *left;
    avlNode *right;

    int balanceFactor();

    void fixHeight();

    avlNode* rotateRight();

    avlNode* rotateLeft();

    avlNode* balance();
};

int height0(avlNode*);

class avl {
public:

    avl();

    avlNode* getRoot();

    void add(avlNode*, point);

    void addRandom(int);

    void erase(point);

    std::vector<avlNode*> find(avlNode*, point, std::vector<avlNode*>&);

    std::vector<avlNode*> find(avlNode*, point, std::vector<avlNode*>&, double);

    void printInOrder(avlNode*);

    template <class func>
    void special(avlNode* curr, func f) {
        if (curr->left != nullptr) {
            special(curr->left, f);
        }

        f(curr);

        if (curr->right != nullptr) {
            special(curr->right, f);
        }
    }

private:
    avlNode* root;

    avlNode* parent(avlNode*, avlNode*, std::vector<avlNode*>&);

    void addTree(avlNode*, avlNode*);

};