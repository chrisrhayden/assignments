#include "list.h"

#include <iostream>
using namespace std;

Node::Node(long int new_hash, HouseData *to_add) {
    data = InternalHouseData();

    data.copy_from_house_data(to_add);

    hash = new_hash;

    next = 0;
}

Node::~Node() {
    hash = 0;
    next = 0;
}

bool Node::display() {
    // pad when displaying by nodes
    cout << '\n';
    return data.display();
}

List::List() {
    head = 0;
}

List::~List() {
    Node *current = head;
    Node *temp = 0;

    while (current) {
        temp = current->next;
        delete current;
        current = temp;
    }

    head = 0;
}

bool List::is_empty() {
    return !head ? true : false;
}

bool List::add(long int hash, HouseData *to_add) {
    if (to_add->is_empty()) {
        return false;
    }

    Node *new_node = new Node(hash, to_add);

    if (!head) {
        head = new_node;
    } else {
        new_node->next = head;
        head = new_node;
    }

    return true;
}

bool List::display() {
    if (!head) {
        return false;
    }

    bool success = true;
    Node *current = head;

    while (current && success) {
        success = current->display();

        current = current->next;
    }

    return success;
}
