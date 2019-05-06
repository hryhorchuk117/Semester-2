#pragma once

#include <vector>
#include <random>
#include <iostream>

struct node {
    explicit node(int newData) {
        this->data = newData;
        this->next = {};
    }

    explicit node(int newData, const std::vector<node*>& newNext) {
        this->data = newData;
        this->next = newNext;
    }

    int data;
    std::vector<node*> next;
};

struct binaryNode {
    explicit binaryNode(int newData) {
        this->data = newData;
        this->left = nullptr;
        this->right = nullptr;
    }

    int data;
    binaryNode* left;
    binaryNode* right;
};

//struct for block 5
struct binaryTree {
    int data;
    bool isLeft;
    int indexRight;
};

int randomInt(int begin, int end) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return dis(gen);
}

bool randomTrue(double p) {
    double rand = (double)randomInt(0, 10000) / 10000;
    return p > rand;
}

template <class node>
void addNode(int newData, double p, node* curr) {
    if (randomTrue(p) || curr->next.empty()) {
        node* newNode = new node(newData);
        curr->next.push_back(newNode);
    } else {
        int k = randomInt(0, curr->next.size());
        addNode(newData, p, curr->next[k]);
    }
}

template <class node>
void addTree(node* add, double p, node* head) {
    addNode(add->data, p, head);
    for (auto item : add->next) {
        addTree(item, p, head);
    }
}

template <class node>
void printTree(node* head) {
    std::cout << head->data << '(';
    for (auto item : head->next) {
        printTree(item);
    }
    std::cout << ')';
}

template <class node>
std::vector<node*> findNode(int findData, node* head, std::vector<node*>& res) {
    if (head->data == findData) {
        res.push_back(head);
    }
    for (auto item : head->next) {
        findNode(findData, item, res);
    }
    return res;
}

template <class node>
void deletePointer(node* head, node* del) {
    if (head == del) {
        return;
    }
    for (auto it = begin(head->next); it <end(head->next); ++it) {
        if (*it == del) {
            head->next.erase(it);
            break;
        }
    }

    for (auto item : head->next) {
        deletePointer(item, del);
    }
}

template <class node>
void deleteNode(node* head, int delData, double p) {
    if (head->data == delData) {
        node* newHead = new node(head->next[0]->data);
        for (int i = 1; i < head->next.size(); ++i) {
            addTree(head->next[i], p, newHead);
        }
        head = newHead;
    }

    std::vector<node*> res = findNode(delData, head, res);
    for (auto del : res) {
        deletePointer(head, del);
        for (auto item : del->next) {
            addTree(item, p, head);
        }
    }
}

void addBinary(int add, binaryNode* head) {

    if (add < head->data && head->left == nullptr) {
        auto* lft = new binaryNode(add);
        head->left = lft;
        return;
    }

    if (add >= head->data && head->right == nullptr) {
        auto* rght = new binaryNode(add);
        head->right = rght;
        return;
    }

    if (add < head->data) {
        addBinary(add, head->left);
        return;
    }

    addBinary(add, head->right);
}

int size(binaryNode* head) {
    int count = 1;

    if (head->left) {
        count += size(head->left);
    }

    if (head->right) {
        count += size(head->right);
    }

    return count;
}

std::vector<binaryTree> presentation(binaryNode* head, std::vector<binaryTree>& res) {
    bool isLeft = head->left;
    int indexRight = -1;
    if (head->right) {
        indexRight = res.size() + size(head->left);
    }
    res.push_back({head->data, isLeft, indexRight});

    if (head->left) {
        presentation(head->left, res);
    }

    if (head->right) {
        presentation(head->right, res);
    }

    return res;
}
