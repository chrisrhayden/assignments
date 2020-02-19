#include <cstring>
#include <iostream>

#include "list.h"
#include "room.h"

// set all data to the zeroth addres
Node::Node() {
    room = 0;
    accessory = 0;
    next = 0;
}

// call delete on the data
Node::~Node() {
    if (room) {
        delete room;
    }
    // `if else` is not used as there could be a mistake and both could have
    // data
    if (accessory) {
        delete accessory;
    }

    // set the next to null just to be sure
    next = 0;
}

// check if this node is a room
bool Node::isroom() {
    if (room) {
        return true;
    }

    return false;
}

// copy the node to another given one
bool Node::copy(Node *&new_node) {
    if (room) {
        // instantiate a Room
        new_node->room = new Room();

        // copy the existing one to the new one
        room->copy(new_node->room);

        // return success
        return true;

    } else if (accessory) {
        new_node->accessory = new Accessory();
        accessory->copy(new_node->accessory);
        return true;
    }

    // if nether exist the we fucked
    return false;
}

// call display() on the right value
bool Node::display() {
    if (isroom()) {
        room->display();
    } else {
        accessory->display();
    }

    return true;
}

// generic constructor
List::List() {
    head = 0;
    tail = 0;
}

// generic list destructor
List::~List() {
    // get head
    Node *current = head;
    // make a temp
    Node *temp = 0;

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

// call display() on each node
bool List::display() {
    // if no data the this is an error i guess
    if (!head) {
        return false;
    }

    Node *current = head;

    while (current) {
        current->display();

        current = current->next;
    }

    return true;
}

// make a new Node with a Room to append to the list
bool List::append(char *&name) {
    Node *new_node = new Node();

    new_node->room = new Room();

    // associate the passed name with room->name
    new_node->room->name = name;

    // append the node
    return append(new_node);
}

// make a new Node with an Accessory
bool List::append(char *&name, char *&category, char *&status) {
    Node *new_node = new Node();

    new_node->accessory = new Accessory();

    new_node->accessory->add_data(name, category, status);

    return append(new_node);
}

// the actual appending to the list
bool List::append(Node *&new_node) {
    // if the node dose not exist the i dont know what happened
    if (!new_node) {
        return false;
    }

    // if no head start a new list
    if (!head) {
        head = new_node;
        tail = new_node;
    } else {
        // add node to end of list
        tail->next = new_node;
        // make end of list point to node
        tail = new_node;
    }

    return true;
}

// remove a node calling delete on it cascading down to the node and the given
// data
bool List::remove(char *name) {
    // if empty i guess this is an error
    if (!head) {
        return false;
    }

    bool success = false;

    Node *current = head;
    Node *prev = 0;

    // loop while we have nodes and not found a success
    while (current || !success) {
        int cmp = -1;

        // compare the given name with node
        if (current->room) {
            cmp = strcmp(current->room->name, name);
        } else if (current->accessory) {
            cmp = strcmp(current->accessory->name, name);
        }

        // if cmp == 0 the we found a match
        if (cmp == 0) {
            success = true;

            // connect the previous to the next node
            prev->next = current->next;

            // remove current node
            delete current;
        } else {
            prev = current;
            current = current->next;
        }
    }

    return success;
}

bool List::retrieve(Accessory *&to_fill, char *name) {
    if (!head->accessory) {
        return false;
    }

    Node *current = head;

    bool found = false;

    while (current && !found) {
        if (strcmp(current->room->name, name) == 0) {
            // success = current->accessory->copy(to_fill);
            to_fill = current->accessory;
            found = true;
        }

        current = current->next;
    }

    return found;
}

bool List::retrieve(Room *&to_fill, char *name) {
    if (!head->room) {
        return false;
    }

    Node *current = head;

    bool found = false;

    while (current && !found) {
        if (strcmp(current->room->name, name) == 0) {
            // success = current->room->copy(to_fill);
            to_fill = current->room;
            found = true;
        }

        current = current->next;
    }

    return found;
}

bool List::copy(List *&new_list) {
    if (!head) {
        return false;
    }

    Node *current = head;

    while (current) {
        Node *new_node = new Node();

        current->copy(new_node);

        new_list->append(new_node);
    }

    return true;
}
