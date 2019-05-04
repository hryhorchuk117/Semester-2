#pragma once

#include <vector>
#include <random>
#include <iostream>

struct node {
    explicit node(int new_data) {
        this->data = new_data;
        this->next = {nullptr};
    }

    explicit node(int new_data, const std::vector<node*>& new_next) {
        this->data = new_data;
        this->next = new_next;
    }

    int data;
    std::vector<node*> next;
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

void addNode(int new_data, double p, node* curr) {
    if (randomTrue(p) || curr->next.empty()) {
        node* new_node = new node(new_data);
        curr->next.push_back(new_node);
    } else {
        int k = randomInt(0, curr->next.size());
        addNode(new_data, p, curr->next[k]);
    }
}

void printTree(node* head) {
    std::cout << head->data << '(';
    for (auto item : head->next) {
        printTree(item);
    }
    std::cout << ')';
}

