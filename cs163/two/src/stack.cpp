#include "stack.h"

SNode::SNode(int array_len) {
    next = 0;
    length = 0;
    max_length = array_len;

    elements = new Route[max_length];
}

SNode::~SNode() {
    delete[] elements;
    elements = 0;

    length = 0;

    next = 0;
}

bool SNode::is_empty() {
    return elements[0].is_empty();
}

bool SNode::is_full() {
    return length == max_length;
}

bool SNode::display() {
    bool success = true;
    for (int i = length - 1; i >= 0 && success; --i) {
        success = elements[i].display();
    }

    return success;
}

bool SNode::add(Route *to_add) {
    if (length == max_length) {
        return false;
    }

    // get a pointer to a Route
    Route *element = &elements[length];

    if (!to_add->copy_into(element)) {
        elements[length] = Route();
        length -= 1;
        return false;
    }

    length += 1;
    return true;
}

bool SNode::remove(Route *&to_fill) {
    if (elements[0].is_empty()) {
        return false;
    }

    length -= 1;
    bool success = elements[length].copy_into(to_fill);

    if (success) {
        elements[length].clear();
    } else {
        length += 1;
    }

    return success;
}

bool SNode::peek(Route *&to_fill) {
    if (elements[0].is_empty()) {
        return false;
    }

    return elements[0].copy_into(to_fill);
}

Stack::Stack(int len) {
    tail = 0;
    head = 0;

    array_length = len;
}

Stack::~Stack() {
    if (!head) {
        return;
    }

    SNode *current = head;
    SNode *temp = 0;

    while (current) {
        temp = current->next;

        delete current;

        current = temp;
    }

    head = 0;
    tail = 0;
}

bool Stack::push(Route *to_add) {
    if (!head) {
        SNode *new_snode = new SNode(array_length);

        head = new_snode;
    } else if (head->is_full()) {
        SNode *new_snode = new SNode(array_length);

        new_snode->next = head;

        head = new_snode;
    }

    return head->add(to_add);
}

bool Stack::pop(Route *&to_fill) {
    if (!head || head->is_empty()) {
        return false;
    }

    bool copy_success = head->remove(to_fill);

    if (head->is_empty()) {
        SNode *temp = head->next;

        delete head;

        head = temp;
    }

    return copy_success;
}

bool Stack::peek(Route *&to_fill) {
    if (!head) {
        return false;
    }

    return head->peek(to_fill);
}

bool Stack::is_empty() {
    if (!head) {
        return true;
    }

    return head->is_empty();
}

bool Stack::display() {
    if (!head) {
        return false;
    }

    SNode *current = head;
    bool success = true;

    while (current && success) {
        success = current->display();

        current = current->next;
    }

    return success;
}
