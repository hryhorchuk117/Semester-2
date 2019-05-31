#include "avl.h"

// avlNode

avlNode::avlNode(const point &newPoint) {
    this->data = newPoint;
    this->height = 1;
    this->left = nullptr;
    this->right = nullptr;
}

int avlNode::balanceFactor() {
    return height0(this->right) - height0(this->left);
}

void avlNode::fixHeight() {
    int hl = height0(this->left);
    int hr = height0(this->right);

    this->height = std::max(hl, hr) + 1; //(hl>hr?hl:hr)+1;
}

avlNode* avlNode::rotateRight() {
    avlNode* node = this->left;
    this->left = node->right;
    node->right = this;
    this->fixHeight();
    node->fixHeight();
    return node;
}

avlNode* avlNode::rotateLeft() {
    avlNode* node = this->right;
    this->right = node->left;
    node->left = this;
    this->fixHeight();
    node->fixHeight();
    return node;
}

avlNode* avlNode::balance(){
    this->fixHeight();
    if (this->balanceFactor() == 2) {
        if (this->right->balanceFactor() < 0) {
            this->right = this->right->rotateRight();
        }
        return this->rotateLeft();
    }

    if (this->balanceFactor() == -2) {
        if( this->left->balanceFactor() > 0  )
            this->left = this->left->rotateLeft();
        return this->rotateRight();
    }

    return this;
}

int height0(avlNode* curr) {
    if (!curr) {
        return 0;
    }
    return curr->height;
}

// avl

avl::avl() {
    root = nullptr;
}

avlNode* avl::getRoot() {
    return root;
}

void avl::add(avlNode* curr, point p) {
    if (!this->root) {
        this->root = new avlNode(p);
        return;
    }

    if (p < curr->data && curr->left == nullptr) {
        auto* lft = new avlNode(p);
        curr->left = lft;
        root = root->balance();
        return;
    }

    if (!(p < curr->data) && curr->right == nullptr) {
        auto* rght = new avlNode(p);
        curr->right = rght;
        root = root->balance();
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

void avl::addRandom(int k) {
    for (int i = 0; i < k; ++i) {
        add(root, randomPoint());
    }
}

void avl::erase(point p) {
    std::vector<avlNode*> del;
    del = find(root, p, del);

    while (!del.empty()) {
        std::vector<avlNode*> temp;
        if(root == del.front()) {

            if (root->left) {
                avlNode* add = root->right;
                root = root->left;
                if (add) {
                    addTree(root, add);
                }
            }
            else if (root->right) {
                avlNode* add = root->left;
                root = root->right;
                if (add) {
                    addTree(root, add);
                }
            } else root = nullptr;

            return;
        }

        avlNode* par = parent(root, del.front(), temp);

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

std::vector<avlNode*> avl::find(avlNode* curr, point p, std::vector<avlNode*>& res) {
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

std::vector<avlNode*> avl::find(avlNode* curr, point p, std::vector<avlNode*>& res, double mistake) {
    if (mistake > std::max(curr->data.distance() - p.distance(), p.distance() - curr->data.distance())) {
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

void avl::printInOrder(avlNode* curr) {
    if (curr->left != nullptr) {
        printInOrder(curr->left);
    }

    std::cout << curr->data << "\n";

    if (curr->right != nullptr) {
        printInOrder(curr->right);
    }
}


avlNode* avl::parent(avlNode* curr, avlNode* find, std::vector<avlNode*>& res) {
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

void avl::addTree(avlNode* treeNode, avlNode* addNode) {
    add(treeNode, addNode->data);

    if (addNode->left) {
        addTree(treeNode, addNode->left);
    }

    if (addNode->right) {
        addTree(treeNode, addNode->right);
    }
}