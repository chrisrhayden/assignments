#include <cstring>
#include <iostream>

#include "list.h"

using namespace std;

// a convenience function to get user input from stdin to the given array
void read_into_buf(char *&temp, char *&buf) {
    // fill array
    cin.get(temp, 1000, '\n');
    // clear read errors, like entering a single \n
    cin.clear();
    // ignore data that wont fit in to the array
    cin.ignore(1000, '\n');

    // get the size of the new string
    int temp_size = 0;
    if (temp[0] != '\0') {
        temp_size = strlen(temp);
    } else {
        temp_size = 0;
    }

    // make a new array at the right size
    buf = new char[temp_size];

    // fill the given buffer with user_input
    strcpy(buf, temp);

    // clear temp array
    temp[0] = '\0';
}

// set data and next node to null
Todo::Todo() {
    name = NULL;
    description = NULL;
    due_date = NULL;

    next = NULL;

    // set this to something, later we can make this meaning full
    priority = -1;
}

// destruct all dynamic memory
Todo::~Todo() {
    // call delete on a dynamic array
    delete[] name;
    delete[] description;
    delete[] due_date;
}

// a function to read in data
bool Todo::read_in_data() {
    // make a temp array, dynamic for fun, but its probably better without
    char *user_input = new char[1000];
    // set it to nothing
    user_input[0] = '\0';

    cout << "\n--------------------\nenter task name\n -> ";
    // call the function to actually get data in to the array
    read_into_buf(user_input, name);

    // if name is empty then stop entering items in to the list
    if (!name || strlen(name) == 0) {
        // delete the temp array
        delete[] user_input;
        return false;
    }

    cout << "enter task description\n -> ";
    read_into_buf(user_input, description);

    cout << "enter task priority\n (1 - 10) -> ";
    // priority is an int so cin >> is fine
    cin >> priority;
    cin.ignore(1000, '\n');

    cout << "enter task due date\n -> ";
    read_into_buf(user_input, due_date);

    delete[] user_input;
    return true;
}

// a simple display function
void Todo::display() {
    cout << "\n# name: " << name << "\n# priority: " << priority
         << "/10\n# due: " << due_date << "\n# description:\n  " << description
         << endl;
}

// set length and next to NULL
LinkedList::LinkedList() {
    head = NULL;
    internal_length = 0;
}

// destruct each item in the list allowing them to call there destructor in
// return
LinkedList::~LinkedList() {
    if (head == NULL) {
        return;
    }

    Todo *current = head;
    Todo *temp = NULL;

    while (current) {
        temp = current->next;

        delete current;

        current = temp;
    }
}

// call add_link() until it returns false
void LinkedList::build() {
    // while (add_link()) {}
    bool keep_looping = true;

    while (keep_looping) {
        keep_looping = add_link();
    }
}

/*
// this is bad and i feel bad
void LinkedList::insert_at(Todo *&node) {
    if (node == NULL || head == NULL) {
        return;
    }

    bool found = false;

    Todo *prev = head;
    Todo *current = head->next;

    if (node->name[0] < prev->name[0]) {
        node->next = prev;
        head = node;

        found = true;
    } else if (current == NULL || node->name[0] == prev->name[0]) {
        prev->next = node;
        node->next = current;

        found = true;
    }

    while (found != true && current->next) {
        cout << node->name[0] << " -- " << current->name[0] << " -- "
             << current->next->name[0] << endl;
        if (node->name[0] <= current->name[0]) {
            node->next = current;
            prev->next = node;

            found = true;
        }

        prev = current;
        current = current->next;
    }

    if (found == false) {
        if (node->name[0] <= current->name[0]) {
            node->next = current;
            prev->next = node;

        } else {
            current->next = node;
        }
    }
}
*/

// recursively look for a node to insert at or append to end of list
void LinkedList::insert_order(Todo *node, Todo *current, Todo *prev) {
    // if the new node has a smaller (ie higher in the
    // alphabet) or equal first letter then the current node insert it before
    // else if current->next is null append the new node the end of the list
    if (node->name[0] <= current->name[0]) {
        if (prev) {
            prev->next = node;
            node->next = current;
        } else {
            node->next = current;
            head = node;
        }

        return;
    } else if (current->next == NULL) {
        current->next = node;

        return;
    }

    // didn't find a place to insert then recurse... or something
    return insert_order(node, current->next, current);
}

// add add a link to the list
bool LinkedList::add_link() {
    // make a new dynamic node
    Todo *new_node = new Todo();
    // call read_in_data()
    if (!new_node->read_in_data()) {
        // if read_in_data fails then make sure to delete the node
        delete new_node;

        return false;
    }

    if (head == NULL) {
        // if head is NULL we have a new list
        head = new_node;

    } else {
        insert_order(new_node, head, NULL);
    }

    // increment the internal length
    ++internal_length;
    return true;
}

/*
// add add a link to the list
bool LinkedList::add_link() {
    // make a new dynamic node
    Todo *new_node = new Todo();
    // call read_in_data()
    if (!new_node->read_in_data()) {
        // if read_in_data fails then make sure to delete the node
        delete new_node;

        return false;
    }

    if (head == NULL) {
        // if head is NULL we have a new list
        head = new_node;

    } else {
        // get ready to traverse
        Todo *current = head;

        // while the current can traverse
        while (current->next) {
            // traverse
            current = current->next;
        }

        // add the new node to the lasts next continuing the chain
        current->next = new_node;
    }

    // increment the internal length
    ++internal_length;
    return true;
}
*/

// loop over every element and check if it should print
void LinkedList::display_loop(Todo *current, int *filter) {
    if (current == NULL) {
        return;
    }

    // if filter is empty we can print
    // if filter is present and the current->priority matches we can print
    if (!filter || current->priority == *filter) {
        current->display();
    }

    // traverse
    return display_loop(current->next, filter);
}

/*
// loop over every element and check if it should print
void LinkedList::display_loop(int *filter) {
    if (head == NULL) {
        cout << "list is empty" << endl;
        return;
    }

    // set up traversal pointers
    Todo *current = head;

    // traverse until current is no longer a node
    while (current) {
        // if filter is empty we can print
        // if filter is present and the current->priority matches we can print
        if (!filter || current->priority() == *filter) {
            current->display();
        }

        // traverse
        current = current->next;
    }
}
*/

// call display_loop with NULL making it print every node
void LinkedList::display() { display_loop(head, NULL); }

// call display_loop with a given priority, printing only matching node
void LinkedList::display_priority(int to_filter) {
    display_loop(head, &to_filter);
}

// remove by name, this can easily remove all, by name or just one, ill
// leave is as just one for now
bool LinkedList::remove_item(char *to_remove) {
    if (head == NULL) {
        return false;
    }

    // to let main know if we removed an item
    bool match = false;

    // check it the match is head so we can replace where head points too
    if (strcmp(head->name, to_remove) == 0) {
        // get a temp to hold on too
        Todo *temp = head;
        // make head the nre node
        head = head->next;

        // remove old head
        delete temp;

        // let the loop know to not run
        match = true;
    }

    // set up traversal pointers
    Todo *current = head->next;
    Todo *prev = head;

    // while we have a nodes and not a match
    while (current && !match) {
        // check the current node
        if (strcmp(current->name, to_remove) == 0) {
            match = true;

            // connect the next node
            prev->next = current->next;

            // remove the chosen node
            delete current;

        } else {
            // traverse
            prev = current;
            current = current->next;
        }
    }

    // return if we found a match
    return match;
}

// recursively count nodes
int length_recursion(Todo *node) {
    // if the next node exists then call length_recursion again
    // with the next node as the new *node, add one to the result
    // else return one as its sill a node
    if (node->next != NULL) {
        return 1 + length_recursion(node->next);
    } else {
        return 1;
    }
}

// a function to call length from main recursively
int LinkedList::length() { return length_recursion(head); }

/*
// return the internal length
int LinkedList::length() { return internal_length; }
*/

// find the length by looping over every node
int LinkedList::length_loop() {
    int count = 0;

    if (head == NULL) {
        // if noting in head then the list is empty
        return 0;
    }

    Todo *current = head;

    while (current) {
        ++count;

        current = current->next;
    }

    // return the finale count
    return count;
}
