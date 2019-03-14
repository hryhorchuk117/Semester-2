#pragma once

#include <utility>

struct Node {
    explicit Node(int degree, double coef) {
        this->next = nullptr;
        this->degree = degree;
        this->coef = coef;
    }

    explicit Node(int degree, double coef, Node* next) {
        this->next = next;
        this->degree = degree;
        this->coef = coef;
    }

    int degree;
    double coef;
    Node* next;
};

class Polynomial {
public:
    Polynomial() {
        length = 0;
        head = nullptr;
    }

    void Add(int new_degree, double new_coef) {
        if (new_coef == 0) {
            return;
        }

        if (head == nullptr) {
            head = new Node(new_degree, new_coef);
            ++length;

        }
        else {
            if (new_degree > head->degree) {
                Node* new_head = new Node(new_degree, new_coef, head);
                head = new_head;
                ++length;
                return;
            }

            Node* curr = head;
            while (true) {
                if (curr->degree == new_degree) {
                    curr->coef += new_coef;
                    if (curr->coef == 0) {
                        Delete(curr);
                    }
                    return;
                }
                if (curr->next && curr->next->degree > new_degree) {
                        curr = curr->next;
                }
                else if (curr->next && curr->next->degree == new_degree) {
                    curr = curr->next;
                }

                else break;
            }

            if (!curr->next) {
                curr->next = new Node(new_degree, new_coef);
            }
            else {
                Node* node = new Node(new_degree, new_coef, curr->next);
                curr->next = node;
            }

            ++length;
        }
    }

    void Delete(Node* del) {
        if (del == head) {
            if (length > 1) {
                head = head->next;
            }
            else {
                head = nullptr;
            }
        }
        else {
            Node* prev = head;
            while(prev->next != del) {
                prev = prev->next;
            }
            prev->next = del->next;
        }
        --length;
    }

    void Print() const {
        if (length == 0) {
            std::cout << 0;
            return;
        }
        Node* curr = head;
        for (int i = 0; i < length; ++i) {

            if (curr->degree == 1 && curr->coef != 1) {
                std::cout << curr->coef << " * x";
            }
            else if (curr->degree == 1) {
                std::cout << "x";
            }
            else if (curr->degree == 0) {
                std::cout << curr->coef;
            }
            else if (curr->coef != 1) {
                std::cout << curr->coef << " * x^" << curr->degree;
            }
            else {
                std::cout << "x^" << curr->degree;
            }

            if (i != length - 1) {
                std::cout << " + ";
            }

            curr = curr->next;
        }
    }

    int length;
    Node* head;

};

Polynomial operator+ (const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial res = lhs;
    Node* curr = rhs.head;
    while(curr) {
        res.Add(curr->degree, curr->coef);
        curr = curr->next;
    }
    return res;
}

Polynomial operator- (const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial rhs_new = rhs;
    Node* curr = rhs_new.head;
    while(curr) {
        curr->coef*=-1;
        curr = curr->next;
    }
    Polynomial res = lhs + rhs_new;
    return res;
}

Polynomial operator* (const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial res;
    Node* curr_lhs = lhs.head;
    Node* curr_rhs = rhs.head;

    while(curr_lhs) {
        while(curr_rhs) {
            res.Add(curr_lhs->degree + curr_rhs->degree,
                    curr_lhs->coef * curr_rhs->coef);
            curr_rhs = curr_rhs->next;
        }
        curr_rhs = rhs.head;
        curr_lhs = curr_lhs->next;
    }

    return res;
}

std::pair<Polynomial, Polynomial> operator/ (const Polynomial& lhs, const Polynomial& rhs) {
    std::pair<Polynomial, Polynomial> res;
    res.second = lhs; int i = 0;

    while(res.second.head && res.second.head->degree >= rhs.head->degree) {
        res.first.Add(res.second.head->degree - rhs.head->degree,
                      res.second.head->coef / rhs.head->coef);
        Node* curr_res_node = res.first.head;
        while (curr_res_node->next) {
            curr_res_node = curr_res_node->next;
        }

        Polynomial curr_res_pol;
        curr_res_pol.Add(curr_res_node->degree, curr_res_node->coef);
        Polynomial curr_lhs = curr_res_pol * rhs;
        res.second = res.second - curr_lhs;
    }

    return res;
}
