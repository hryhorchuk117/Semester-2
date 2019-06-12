#include "2-3tree.h"

#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>

node23::node23() {
    this->size = 0;
    this->data = {};
    this->parent = nullptr;
    this->next = {nullptr, nullptr, nullptr, nullptr};
}

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

void node23::becomeNode2(point p, node23 *_first, node23 *_second) {
    data = {};
    next = {_first, _second, nullptr, nullptr};
    data.push_back(p);
    parent = nullptr;
    size = 1;
}

bool node23::leaf() {
    return !this->next[0] && !this->next[1] && !this->next[2] && !this->next[3];
}

node23* node23::insert(node23* root, point p) {
    if (!root) {
        return new node23(p);
    }

    if (root->leaf()) {
        root->insertData(p);
    }

    else if (p <= root->data[0]) {
        insert(root->next.front(), p);
    }

    else if ((root->size == 1) || ((root->size == 2) && p <= root->data[1])) {
        insert(root->next[1], p);
    }

    else {
        insert(root->next[2], p);
    }

    return split(root);
}

node23* node23::split(node23 *item) {
    if (item->size < 3) return item;

    auto *x = new node23(item->data[0], item->next, item->parent);
    auto *y = new node23(item->data[2], item->next, item->parent);
    if (x->next[0])  x->next[0]->parent = x;
    if (x->next[1])  x->next[1]->parent = x;
    if (y->next[0])  y->next[0]->parent = y;
    if (y->next[1])  y->next[1]->parent = y;

    if (item->parent) {
        item->parent->insertData(item->data[1]);

        if (item->parent->next[0] == item) item->parent->next[0] = nullptr;
        else if (item->parent->next[1] == item) item->parent->next[1] = nullptr;
        else if (item->parent->next[2] == item) item->parent->next[2] = nullptr;

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
        x->parent = item;
        y->parent = item;
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

    if (!curr) return;


    if (curr->next[0]) {
        printInOrder(curr->next[0]);
    }

    std::cout << curr->data[0] << "\n";

    if (curr->next[1] && curr->next[1]->size != 0) {
       printInOrder(curr->next[1]);
    }

    if (curr->data.size() > 1) {
        std::cout << curr->data[1] << "\n";
    }

    if (curr->next[2] && curr->next[2]->size != 0) {
       printInOrder(curr->next[2]);
    }

}

node23* node23::searchMin(node23* p) {
    if (!p) return p;
    if (!(p->next.front())) return p;
    else return searchMin(p->next.front());
}

node23* node23::remove(node23* root, point k) {
    node23* item = find(root, k);

    if (!item) {
        return root;
    }

    node23* min = nullptr;
    if (item->data[0] == k) {
        min = searchMin(item->next[1]);
    }
    else min = searchMin(item->next[2]);

    if (min) {
        point temp = (k == item->data[0] ? item->data[0] : item->data[1]);

        point swap = min->data[0];
        min->data[0] = temp;
        temp = swap;
        item = min;
    }

    item->eraseData(k);
    return fix(item);
}

node23* node23::fix(node23* leaf) {
    if (leaf->size == 0 && leaf->parent == nullptr) {
        delete leaf;
        return nullptr;
    }
    if (leaf->size != 0) {
        if (leaf->parent) return fix(leaf->parent);
        else return leaf;
    }

    node23* par = leaf->parent;
    if (par->next[0]->size == 2 || par->next[1]->size == 2 || par->size == 2) {
        leaf = redistribute(leaf);
    }
    else if (par->size == 2 && par->next[2]->size == 2) {
        leaf = redistribute(leaf);
    }
    else leaf = merge(leaf);

    return fix(leaf);
}

node23* node23::redistribute(node23* leaf) {
    node23* parent = leaf->parent;
    node23* first = parent->next[0];
    node23* second = parent->next[1];
    node23* third = parent->next[2];

    if ((parent->size == 2) && (first->size < 2) && (second->size < 2) && (third->size < 2)) {
        if (first == leaf) {
            parent->next[0] = parent->next[1];
            parent->next[1] = parent->next[2];
            parent->next[2] = nullptr;
            parent->next[0]->insertData(parent->data[0]);
            parent->next[0]->next[2] = parent->next[0]->next[1];
            parent->next[0]->next[1] = parent->next[0]->next[0];

            if (leaf->next[0] != nullptr) parent->next[0]->next[0] = leaf->next[0];
            else if (leaf->next[1] != nullptr) parent->next[0]->next[0] = leaf->next[1];

            if (parent->next[0]->next[0] != nullptr) parent->next[0]->next[0]->parent = parent->next[0];

            parent->eraseData(parent->data[0]);
            delete first;
        } else if (second == leaf) {
            first->insertData(parent->data[0]);
            parent->eraseData(parent->data[0]);
            if (leaf->next[0] != nullptr) first->next[2] = leaf->next[0];
            else if (leaf->next[1] != nullptr) first->next[2] = leaf->next[1];

            if (first->next[2] != nullptr) first->next[2]->parent = first;

            parent->next[1] = parent->next[2];
            parent->next[2] = nullptr;

            delete second;
        } else if (third == leaf) {
            second->insertData(parent->data[1]);
            parent->next[2] = nullptr;
            parent->eraseData(parent->data[1]);
            if (leaf->next[0] != nullptr) second->next[2] = leaf->next[0];
            else if (leaf->next[1] != nullptr) second->next[2] = leaf->next[1];

            if (second->next[2] != nullptr)  second->next[2]->parent = second;

            delete third;
        }
    } else if ((parent->size == 2) && ((first->size == 2) || (second->size == 2) || (third->size == 2))) {
        if (third == leaf) {
            if (leaf->next[0] != nullptr) {
                leaf->next[1] = leaf->next[0];
                leaf->next[0] = nullptr;
            }

            leaf->insertData(parent->data[1]);
            if (second->size == 2) {
                parent->data[1] = second->data[1];
                second->eraseData(second->data[1]);
                leaf->next[0] = second->next[2];
                second->next[2] = nullptr;
                if (leaf->next[0] != nullptr) leaf->next[0]->parent = leaf;
            } else if (first->size == 2) {
                parent->data[1] = second->data[0];
                leaf->next[0] = second->next[1];
                second->next[1] = second->next[0];
                if (leaf->next[0] != nullptr) leaf->next[0]->parent = leaf;

                second->data[0] = parent->data[0];
                parent->data[0] = first->data[1];
                first->eraseData(first->data[1]);
                second->next[0] = first->next[2];
                if (second->next[0] != nullptr) second->next[0]->parent = second;
                first->next[2] = nullptr;
            }
        } else if (second == leaf) {
            if (third->size == 2) {
                if (leaf->next[0] == nullptr) {
                    leaf->next[0] = leaf->next[1];
                    leaf->next[1] = nullptr;
                }
                second->insertData(parent->data[1]);
                parent->data[1] = third->data[0];
                third->eraseData(third->data[0]);
                second->next[1] = third->next[0];
                if (second->next[1] != nullptr) second->next[1]->parent = second;
                third->next[0] = third->next[1];
                third->next[1] = third->next[2];
                third->next[2] = nullptr;
            } else if (first->size == 2) {
                if (leaf->next[1] == nullptr) {
                    leaf->next[1] = leaf->next[0];
                    leaf->next[0] = nullptr;
                }
                second->insertData(parent->data[0]);
                parent->data[0] = first->data[1];
                first->eraseData(first->data[1]);
                second->next[0] = first->next[2];
                if (second->next[0] != nullptr) second->next[0]->parent = second;
                first->next[2] = nullptr;
            }
        } else if (first == leaf) {
            if (leaf->next[0] == nullptr) {
                leaf->next[0] = leaf->next[1];
                leaf->next[1] = nullptr;
            }
            first->insertData(parent->data[0]);
            if (second->size == 2) {
                parent->data[0] = second->data[0];
                second->eraseData(second->data[0]);
                first->next[1] = second->next[0];
                if (first->next[1] != nullptr) first->next[1]->parent = first;
                second->next[0] = second->next[1];
                second->next[1] = second->next[2];
                second->next[3] = nullptr;
            } else if (third->size == 2) {
                parent->data[0] = second->data[0];
                second->data[0] = parent->data[1];
                parent->data[1] = third->data[0];
                third->eraseData(third->data[0]);
                first->next[1] = second->next[0];
                if (first->next[1] != nullptr) first->next[1]->parent = first;
                second->next[0] = second->next[0];
                second->next[1] = third->next[0];
                if (second->next[1] != nullptr) second->next[1]->parent = second;
                third->next[0] = third->next[1];
                third->next[1] = third->next[2];
                third->next[2] = nullptr;
            }
        }
    } else if (parent->size == 1) {
        leaf->insertData(parent->data[0]);

        if (first == leaf && second->size == 2) {
            parent->data[0] = second->data[0];
            second->eraseData(second->data[0]);

            if (leaf->next[0] == nullptr) leaf->next[0] = leaf->next[1];

            leaf->next[1] = second->next[0];
            second->next[0] = second->next[1];
            second->next[1] = second->next[2];
            second->next[2] = nullptr;
            if (leaf->next[1] != nullptr) leaf->next[1]->parent = leaf;
        } else if (second == leaf && first->size == 2) {
            parent->data[0] = first->data[1];
            first->eraseData(first->data[1]);

            if (leaf->next[1] == nullptr) leaf->next[1] = leaf->next[0];

            leaf->next[0] = first->next[2];
            first->next[2] = nullptr;
            if (leaf->next[0] != nullptr) leaf->next[0]->parent = leaf;
        }
    }
    return parent;
}

node23* node23::merge(node23* leaf) {
    node23* par = leaf->parent;

    if (par->next[0] == leaf) {
        par->next[1]->insertData(par->data[0]);
        par->next[1]->next[2] = par->next[1]->next[1];
        par->next[1]->next[1] = par->next[1]->next[0];

        if (!leaf->next[0]) par->next[1]->next[0] = leaf->next[0];
        else if (!leaf->next[1]) par->next[1]->next[0] = leaf->next[1];

        if (!par->next[1]->next[0]) par->next[1]->next[0]->parent = par->next[1];

        par->eraseData(par->data[0]);
        delete par->next[0];
        par->next[0] = nullptr;
    } else if (par->next[1] == leaf) {
        par->next[1]->insertData(par->data[0]);

        if (leaf->next[0] != nullptr) par->next[0]->next[2] = leaf->next[0];
        else if (leaf->next[1] != nullptr) par->next[0]->next[2] = leaf->next[1];

        if (par->next[0]->next[2] != nullptr) par->next[0]->next[2]->parent = par->next[0];

        par->eraseData(par->data[0]);
        delete par->next[1];
        par->next[1] = nullptr;
    }

    if (par->parent == nullptr) {
        node23* temp = nullptr;
        if (par->next[0] != nullptr) temp = par->next[0];
        else temp = par->next[1];
        temp->parent = nullptr;
        delete par;
        return temp;
    }
    return par;
}