#include "list.h"
#include "point.h"

#include <algorithm>
#include <iostream>
#include <vector>

node::node(point value) {
    this->value = value;
    this->next = nullptr;
}

node::node(point value, node* next) {
    this->next = next;
    this->value = value;
}

list::list() {
    this->length = 0;
    this->head = nullptr;
}

void list::append(point p) {
    if (head == nullptr) {
        head = new node(p);
        ++length;
    }
    else {
        node* nod = head;
        for (int i = 1; i < length; ++i) {
            nod = nod->next;
        }
        nod->next = new node(p);
        ++length;
    }
}

void list::insert(point p, int k) {

    if (k == 0) {
        node* nod = head;
        head = new node(p, nod);
        ++length;
    }
    else {

        node *nod = getNode(k - 1);

        node *newNode = new node(p, nod->next);
        nod->next = newNode;
        ++length;
    }
}

void list::addRandom(int k) {
    for (int i = 0; i < k; ++i) {
        append(randomPoint());
    }
}

int list::number(point p) {
    node* curr = head;
    int res = 0;
    while (!(curr->value == p)) {
        curr = curr->next;
        ++res;
    }

    return res;
}

void list::erase(point p) {

    int k = number(p);

    if (k == 0) {
        --length;
        head = getNode(1);
    }

    else if (k == length - 1) {
        --length;
        node* node = getNode(length - 1);
        node->next = nullptr;
    }

    else {
        --length;
        node* prev = getNode(k - 1);
        prev->next = prev->next->next;
    }
}

node* list::find(point find){
    node* curr = head;
    while (curr) {
        if (curr->value == find) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

std::vector<node*> list::find(point find, double mistake) {
    node* curr = head;
    std::vector<node*> res;
    while (curr) {
        if (abs(curr->value.distance() - find.distance()) < mistake) {
            res.push_back(curr);
        }
        curr = curr->next;
    }
    return res;
}


int list::lengthGet() {
    return length;
}

void list::print() {
    node* curr = head;

    for (int i = 0; i < length; ++i) {
        std::cout << curr->value << std::endl;
        curr = curr->next;
    }

}

void list::printInOrder() {
    std::vector<point> all;
    node* curr = head;
    std::vector<node*> res;
    while (curr) {
        all.push_back(curr->value);
        curr = curr->next;
    }

    std::sort(begin(all), end(all));
    for (auto item : all) {
        std::cout << item << "\n";
    }
}

/*template <class func>
void list::special(func f) {
    std::vector<node*> allNodes;
    node* curr = head;
    while (curr) {
        allNodes.push_back(curr);
        curr = curr->next;
    }

    std::sort(begin(allNodes), end(allNodes),
            [](node* lhs, node* rhs){return lhs->value < rhs->value;});

    for (auto item : allNodes) {
        //f(item);
    }
}*/

node* list::getNode(int k) {
    node* node = head;
    for (int i = 0; i < k; ++i) {
        node = node->next;
    }
    return node;
}
