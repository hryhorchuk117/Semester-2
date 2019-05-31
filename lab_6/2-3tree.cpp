#include "2-3tree.h"

#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>

node23::node23(point p) {
    this->size = 1;
    this->data = {p};
    this->parent = nullptr;
    this->next = {nullptr, nullptr, nullptr, nullptr};
}

node23::node23(point p, node23* _parent) {
    this->size = 1;
    this->data = {p};
    this->parent = _parent;
    this->next = {nullptr, nullptr, nullptr, nullptr};
}

node23::node23(point p, const std::vector<node23*>& _next , node23* _parent) {
    this->size = 1;
    this->data = {p};
    this->parent = _parent;
    this->next = _next;
}

void node23::insertData(point p) {
    ++size;
    data.push_back(p);
    std::sort(begin(data), end(data));
}

void node23::eraseData(point p) {
    auto it = std::find(begin(data), end(data), p);
    data.erase(it);
}

void node23::becomeNode2(point p, node23 *_first, node23 *_second) {  // Преобразовать в 2-вершину.
    data = {};
    next = {_first, _second, nullptr, nullptr};
    data.push_back(p);
    parent = nullptr;
    size = 1;
}

node23* node23::insert(node23* root, point p) {
    if (!root) {
        return new node23(p);
    }

    if (!root->next.front()) {
        root->insertData(p);
    }

    else if (p <= root->data[0]) {
        insert(root->next.front(), p);
    }

    else if ((root->size == 1) || ((root->size == 2) && p <= root->data[1])) {
        insert(root->next[1], p);
    }

    else insert(root->next[2], p);

    return split(root);
}

node23* node23::split(node23 *item) {
    if (item->size < 3) return item;

    auto *x = new node23(item->data[0], item->next, item->parent); // Создаем две новые вершины,
    auto *y = new node23(item->data[2], item->next, item->parent);  // которые имеют такого же родителя, как и разделяющийся элемент.
    if (x->next[0])  x->next[0]->parent = x;    // Правильно устанавливаем "родителя" "сыновей".
    if (x->next[1])  x->next[1]->parent = x;   // После разделения, "родителем" "сыновей" является "дедушка",
    if (y->next[0])  y->next[0]->parent = y;    // Поэтому нужно правильно установить указатели.
    if (y->next[1])  y->next[1]->parent = y;

    if (item->parent) {
        item->parent->insert(item->parent, item->data[1]);

        if (item->parent->next[0] == item) item->parent->next[0] = nullptr;
        else if (item->parent->next[1] == item) item->parent->next[1] = nullptr;
        else if (item->parent->next[2] == item) item->parent->next[2] = nullptr;

        // Дальше происходит своеобразная сортировка ключей при разделении.
        if (item->parent->next[0] == nullptr) {
            item->parent->next[3] = item->parent->next[2];
            item->parent->next[2] = item->parent->next[1];
            item->parent->next[1] = y;
            item->parent->next[0] = x;
        } else if (item->parent->next[1] == nullptr) {
            item->parent->next[3] = item->parent->next[2];
            item->parent->next[2] = y;
            item->parent->next[1] = x;
        } else {
            item->parent->next[3] = y;
            item->parent->next[2] = x;
        }

        node23 *tmp = item->parent;
        delete item;
        return tmp;
    } else {
        x->parent = item;   // Так как в эту ветку попадает только корень,
        y->parent = item;   // то мы "родителем" новых вершин делаем разделяющийся элемент.
        item->becomeNode2(item->data[1], x, y);
        return item;
    }
}

node23* node23::insertRandom(int k) {
    for (int i = 0; i < k - 1; ++i) {
        insert(this, randomPoint());
    }
    return  insert(this, randomPoint());
}

node23* node23::find(node23* curr, point p) {
    for (auto item : curr->data) {
        if (item == p) {
            return curr;
        }
    }

    if (curr->data[0].distance() > p.distance()) {
        return find(curr->next[0], p);
    }

    if (curr->data.size() == 1 || curr->data[1].distance() > p.distance()) {
        return find(curr->next[1], p);
    }

    return find(curr->next[2], p);
}

std::vector<node23*> node23::find(node23* curr, point p, double mistake, std::vector<node23*>& res) {
    for (auto item : curr->data) {
        if (std::max(item.distance() - p.distance(), p.distance() - item.distance()) < mistake) {
            res.push_back(curr);
            break;
        }
    }

    for (auto item : curr->next) {
        find(item, p, mistake, res);
    }

    return res;
}

void node23::printInOrder(node23* curr) {

    if (curr->next.front()) {
        printInOrder(curr->next.front());
    }

    std::cout << curr->data.front() << "\n";

    if (curr->next[1]) {
        printInOrder(curr->next[1]);
    }

    if ()
}

