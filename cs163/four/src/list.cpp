#include <cstring>
#include <iostream>

#include "list.h"

using namespace std;

ListNode::ListNode() {
    next = 0;
}

// constructor
ListNode::~ListNode() {
    // if a room exist delete it
    if (this->data) {
        delete this->data;
    }

    // set next to null/zeroth address
    next = 0;
}

// print a room name
bool ListNode::display() {
    if (!this->data) {
        return false;
    }

    return this->data->display();
}

// generic constructor
List::List() {
    // set data to null
    head = 0;
    tail = 0;
}

// generic list destructor
List::~List() {
    // get head
    ListNode *current = head;
    // make a temp
    ListNode *temp = 0;

    // if head dose not exist the loop wont run
    // else head dose so start deleting
    while (current) {
        // get the next node
        temp = current->next;

        // remove the current node
        delete current;

        // setup the next iteration
        current = temp;
    }

    // just to be sure
    head = 0;
    tail = 0;
}

// add a node to the list by name
bool List::append(MealData *to_add) {
    if (!to_add) {
        // i guess this is an error
        return false;
    }

    // if head dose not exist start a new list
    if (!head) {
        head = new ListNode();

        head->data = new MealData();

        head->data->copy_from_meal_data(to_add);

        tail = head;
    } else {
        tail->next = new ListNode();

        tail = tail->next;

        tail->data = new MealData();

        tail->data->copy_from_meal_data(to_add);
    }

    return true;
}

// display all the rooms in s a list
bool List::display() {
    if (!head) {
        return false;
    }

    ListNode *current = head;

    while (current) {
        // call display on each node if it has data
        current->display();

        // traverse
        current = current->next;
    }

    return true;
}
