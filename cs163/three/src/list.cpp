#include <cstring>
#include <iostream>

#include "list.h"

using namespace std;

// node constructor
Node::Node(MealData *to_add) {
    data = MealData();

    data.copy_from_meal_data(to_add);

    next = 0;
}

// node deconstructor
Node::~Node() {
    next = 0;
}

// call display  on data if data exists
bool Node::display() {
    // pad when displaying by nodes
    if (data.is_empty()) {
        return false;
    }

    cout << '\n';
    return data.display();
}

// list constructor
List::List() {
    head = 0;
}

// list deconstructor
List::~List() {
    Node *current = head;
    Node *temp = 0;

    // traverse while data deleting each that does
    while (current) {
        temp = current->next;
        delete current;
        current = temp;
    }

    head = 0;
}

// check if empty
bool List::is_empty() {
    return !head ? true : false;
}

// add to the head of the list
bool List::add(MealData *to_add) {
    bool found = false;
    Node *current = head;

    // check if it already exists
    while (current && !found) {
        if (current->data.match_data_key_full(NameOfMeal,
                                              to_add->name_of_meal)) {
            found = true;
        }

        current = current->next;
    }

    // if the data dose exists the just return false
    if (found) {
        // idk i guess this could be false
        return true;
    }

    // dat dose not exists so make a new meal
    Node *new_node = new Node(to_add);

    // add meal to head
    if (!head) {
        head = new_node;
    } else {
        new_node->next = head;
        head = new_node;
    }

    return true;
}

// get the first data by key
bool List::get(char *key, MealData *to_fill) {
    if (!to_fill) {
        return false;
    }

    bool success = false;
    Node *current = head;

    while (current && !success) {
        // look for key
        if (strcmp(current->data.name_of_meal, key) == 0) {
            // copy to passed in value if we found a match
            to_fill->copy_from_meal_data(&current->data);
            success = true;
        }

        current = current->next;
    }

    return success;
}

// remove by data_key
bool List::remove(DataKey data_key, char *key, MealData *to_fill) {
    // will remove all by key
    // not finding a match is still a success
    bool success = true;
    Node *current = head;
    Node *prev = 0;

    while (current && success) {
        // match the full string
        if (current->data.match_data_key_full(data_key, key)) {
            success = to_fill->copy_from_meal_data(&current->data);

            // connect prev if it exists
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
            // else traverse
            prev = current;
            current = current->next;
        }
    }

    return success;
}

// get data by data_key
bool List::retrieve(DataKey data_key, char *sub_str, List *meal_collect) {
    bool success = true;

    Node *current = head;

    while (current && success) {
        // match on a sub_str
        if (current->data.match_data_key(data_key, sub_str)) {
            success = meal_collect->add(&current->data);
        }

        current = current->next;
    }

    return success;
}

// recursive wrapper to call display without passing in head
bool List::display() {
    if (!head) {
        return false;
    }

    // start the recursion
    display(head);

    return true;
}

// I forgot to make a recursive function so I hope this works
// display the node in a list
void List::display(Node *current) {
    // if current is null just return
    if (!current) {
        return;
    }

    // call display
    current->display();

    // do the recursion
    return display(current->next);
}

// bool List::display() {
//     if (!head) {
//         return false;
//     }
//
//     bool success = true;
//     Node *current = head;
//
//     while (current && success) {
//         success = current->display();
//
//         current = current->next;
//     }
//
//     return success;
// }
