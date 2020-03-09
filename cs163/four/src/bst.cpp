#include "bst.h"

Tree::Tree() {
    root = 0;
}

Tree::~Tree() {
    this->remove_all(this->root);

    root = 0;
}

int Tree::remove_all(Node *current) {
    if (!current) {
        return true;
    }

    int total = 0;

    if (current->left) {
        total += this->remove_all(current->left);
    }

    if (current->right) {
        total += this->remove_all(current->right);
    }

    return total;
}
