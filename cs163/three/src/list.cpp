#include <cstring>
#include <iostream>

#include "list.h"

using namespace std;

Node::Node(MealData *to_add) {
    data = MealData();

    data.copy_from_meal_data(to_add);

    next = 0;
}

Node::~Node() {
    next = 0;
}

bool Node::display() {
    // pad when displaying by nodes
    if (data.is_empty()) {
        return false;
    }

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

bool List::add(MealData *to_add) {
    bool found = false;
    Node *current = head;
    while (current && !found) {
        if (current->data.match_data_key_full(NameOfMeal,
                                              to_add->name_of_meal)) {
            found = true;
        }

        current = current->next;
    }

    if (found) {
        // idk i guess this could be false
        return true;
    }

    Node *new_node = new Node(to_add);

    if (!head) {
        head = new_node;
    } else {
        new_node->next = head;
        head = new_node;
    }

    return true;
}

bool List::get(char *key, MealData *to_fill) {
    if (!to_fill) {
        return false;
    }

    bool success = false;
    Node *current = head;

    while (current && !success) {
        if (strcmp(current->data.name_of_meal, key) == 0) {
            to_fill->copy_from_meal_data(&current->data);
            success = true;
        }

        current = current->next;
    }

    return success;
}

bool List::remove(DataKey data_key, char *key, MealData *to_fill) {
    // will remove all by key
    // not finding a match is still a success
    bool success = true;
    Node *current = head;
    Node *prev = 0;

    while (current && success) {
        if (current->data.match_data_key_full(data_key, key)) {
            success = to_fill->copy_from_meal_data(&current->data);

            if (prev) {
                prev->next = current->next;
            } else {
                head = current->next;
            }

            delete current;
            current = 0;
            // dont bother traversing as we should break here with:
            //      success = true;
        } else {
            prev = current;
            current = current->next;
        }
    }

    return success;
}

bool List::retrieve(DataKey data_key, char *sub_str, List *meal_collect) {
    bool success = true;

    Node *current = head;

    while (current && success) {
        if (current->data.match_data_key(data_key, sub_str)) {
            success = meal_collect->add(&current->data);
        }

        current = current->next;
    }

    return success;
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
