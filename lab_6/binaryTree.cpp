#include "binaryTree.h"

#include <iostream>
#include <vector>

binary::binary(const point& newPoint) {
    this->data = newPoint;
    left = nullptr;
    right = nullptr;
}

tree::tree() {
    this->root = nullptr;
}

binary* tree::getRoot() {
    return root;
}

void tree::add(binary* curr, point p) {
    if (!this->root) {
        this->root = new binary(p);
        return;
    }

    if (p < curr->data && curr->left == nullptr) {
        auto* lft = new binary(p);
        curr->left = lft;
        return;
    }

    if (!(p < curr->data) && curr->right == nullptr) {
        auto* rght = new binary(p);
        curr->right = rght;
        return;
    }

    if (p < curr->data) {
        add(curr->left, p);
        return;
    }

    if (!(p < curr->data)) {
        add(curr->right, p);
        return;
    }
}

void tree::addRandom(int k) {
    for (int i = 0; i < k; ++i) {
        add(root, randomPoint());
    }
}

void tree::erase(point p) {
    std::vector<binary*> del;
    del = find(root, p, del);

    while (!del.empty()) {
        std::vector<binary *> temp;
        if(root == del.front()) {

            if (root->left) {
                binary* add = root->right;
                root = root->left;
                if (add) {
                    addTree(root, add);
                }
            }
            else if (root->right) {
                binary* add = root->left;
                root = root->right;
                if (add) {
                    addTree(root, add);
                }
            } else root = nullptr;

            return;
        }

        binary *par = parent(root, del.front(), temp);

        if (par->left && par->left == del.front()) {
            par->left = nullptr;
        } else {
            par->right = nullptr;
        }
        if (del.front()->left) {
            addTree(root, del.front()->left);
        }
        if (del.front()->right) {
            addTree(root, del.front()->right);
        }
        del = {};
        del = find(root, p, del);

    }

}

std::vector<binary*> tree::find(binary* curr, point p, std::vector<binary*>& res) {
    if (curr->data == p) {
        res.push_back(curr);
    }

    if (curr->left && curr->data.distance() > p.distance()) {
        find(curr->left, p, res);
        return res;
    }

    if (curr->right && curr->data.distance() < p.distance()) {
        find(curr->right, p, res);
        return res;
    }

    return res;
}

std::vector<binary*> tree::find(binary* curr, point p, std::vector<binary*>& res, double mistake) {
    if (mistake > std::max(curr->data.distance() - p.distance(), p.distance() - curr->data.distance()))  {
        res.push_back(curr);
    }

    if (curr->left) {
        find(curr->left, p, res, mistake);
    }

    if (curr->right) {
        find(curr->right, p, res, mistake);
    }

    return res;
}

void tree::printInOrder(binary* curr) {
    if (curr->left) {
        printInOrder(curr->left);
    }

        std::cout << curr->data << "\n";

    if (curr->right) {
        printInOrder(curr->right);
    }
}

binary* tree::parent(binary* curr, binary* find, std::vector<binary*>& res) {
    if (curr->left == find || curr->right == find) {
        res.push_back(curr);
        return res.back();
    }

    if (curr->left) {
        parent(curr->left, find, res);
    }

    if (curr->right) {
        parent(curr->right, find, res);
    }

    if (!curr->left && !curr->right) {
        return {};
    }

    if (res.empty()) {
        return {};
    }
    return res.back();
}

void tree::addTree(binary* treeNode, binary* addNode) {
    add(treeNode, addNode->data);

    if (addNode->left) {
        addTree(treeNode, addNode->left);
    }

    if (addNode->right) {
        addTree(treeNode, addNode->right);
    }
}