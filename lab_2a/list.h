#pragma once

#include "point.h"

struct Node {

    explicit Node(Point value) {
        this->value = value;
        this->next = nullptr;
    }

    explicit Node(Point value, Node* next) {
        this->next = next;
        this->value = value;
    }

    Point value;
    Node* next;
};

class List {
public:
    List() {
        this->length = 0;
        this->head = nullptr;
    }

    void Append(Point p) {
        if (head == nullptr) {
            head = new Node(p);
            ++length;
        }
        else {
            Node* node = head;
            for (int i = 1; i < length; ++i) {
                node = node->next;
            }
            node->next = new Node(p);
            ++length;
        }
    }

    void Insert(Point p, int k ) {

        if (k > length || k < 0) {
            throw ("error");
        }

        if (k == 0) {
            Node* node = head;
            head = new Node(p, node);
            ++length;
        }
        else {

            Node *node = Get_node(k - 1);

            Node *new_node = new Node(p, node->next);
            node->next = new_node;
            ++length;
        }
    }

    void Remove(int k) {
        if (k >= length || k < 0 || length == 0) {
            throw ("error");
        }

        if (k == 0) {
            --length;
            head = Get_node(1);
        }

        else if (k == length - 1) {
            --length;
            Node* node = Get_node(length - 1);
            node->next = nullptr;
        }

        else {
            --length;
            Node* prev = Get_node(k - 1);
            prev->next = prev->next->next;
        }


    }

    Point Get(int k) {

        if (length == 0 || k < 0 || k >= length) {
            throw ("error");
        }

        Node* node = head;
        for (int i = 1; i < k; ++i) {
            node = node->next;
        }
        return node->value;
    }

    int Length() {
        return length;
    }

    void Print () {
        Node* node = head;

        for (int i = 0; i < length; ++i) {
            std::cout << node->value << std::endl;
            node = node->next;
        }
    }

private:
    int length;
    Node* head;

    Node* Get_node(int k) {
        Node* node = head;
        for (int i = 0; i < k; ++i) {
            node = node->next;
        }
        return node;
    }
};
