#include <cstring>
#include <iostream>

#include "smart_home.h"

using namespace std;

Node::Node() {
    room = 0;
    next = 0;
}

// constructor
Node::~Node() {
    // if a room exist delete it
    if (room) {
        delete room;
    }

    // set next to null/zeroth address
    next = 0;
}

// print a room name
bool Node::display() {
    if (!room) {
        return false;
    }

    return room->display_name();
}

// generic constructor
SmartHome::SmartHome() {
    // set data to null
    head = 0;
    tail = 0;
}

// generic list destructor
SmartHome::~SmartHome() {
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

// make a new Node with a Room to append to the list
bool SmartHome::append(char *name) {
    // set up a new node
    Node *new_node = new Node();

    // add the room
    new_node->room = new Room(name);

    // append the node
    return append(new_node);
}

// a quick hack as i forgot to order the nodes
void SmartHome::add_ord(Node *&to_add) {
    bool success = false;

    // already checked in append
    Node *current = head;
    Node *prev = 0;

    // while we haven't found a match and we still have data
    while (current && !success) {
        // compare the first letter of each room name case sensitive
        if (to_add->room->name_str()[0] <= current->room->name_str()[0]) {
            if (current == head) {
                // we are at the head
                to_add->next = head;
                head = to_add;
            } else {
                // we are some where in the middle, including z
                prev->next = to_add;
                to_add->next = current;
            }

            success = true;
        }

        // traverse
        prev = current;
        current = current->next;
    }

    // if to_add is a new low add to tail
    if (!success) {
        tail->next = to_add;
        tail = to_add;
    }
}

// add a node to the list by name
bool SmartHome::append(Node *&to_add) {
    if (!to_add) {
        // i guess this is an error
        return false;
    }

    // if head dose not exist start a new list
    if (!head) {
        cout << "add to head" << endl;
        head = to_add;
        tail = to_add;
    } else {
        add_ord(to_add);
    }

    return true;
}

// add an accessory to a room by a given name
bool SmartHome::append_accessory(char *room_to_find, Accessory *to_add) {
    // if list is empty then no room to ad an accessory
    if (!head) {
        return false;
    }

    bool success = false;

    Node *current = head;

    // while we have data and not found what were looking for
    while (current && !success) {
        // compare current room name to the given str to find
        if (current->room->cmp(room_to_find)) {
            // stop the loop and return success
            success = true;

            // add the accessory toe the found room
            current->room->append(to_add);
        }
    }

    // return whether we are successful
    return success;
}

// remove a node calling delete on it cascading down to the node and the given
// data
bool SmartHome::remove_room(char *to_find) {
    // if empty i guess this is an error
    if (!head) {
        return false;
    }

    bool success = false;

    Node *current = head;
    Node *prev = 0;

    // loop while we have nodes and not found a success
    while (current && !success) {
        if (current->room && current->room->cmp(to_find)) {
            if (prev) {
                // connect the previous to the next node
                prev->next = current->next;

                if (current == tail) {
                    tail = prev;
                }

            } else {
                // we are at the beginning, set next nod if any to head
                head = current->next;

                if (current == tail) {
                    tail = 0;
                }
            }

            // remove current node
            delete current;

            // stop the loop and to return true
            success = true;
        } else {
            // just traverse
            prev = current;
            current = current->next;
        }
    }

    // return whether we are successful
    return success;
}

// remove an accessory by name
bool SmartHome::remove_accessory(char *room_to_find, char *accessory_to_find) {
    // if empty i guess this is an error
    if (!head) {
        return false;
    }

    // make a room to fill
    Room *the_room;

    // get a room by name
    if (!retrieve(room_to_find, the_room)) {
        return false;
    }

    // remove an accessory from the given room
    return the_room->remove(accessory_to_find);
}

// retrieve a room by name, take a pointer reference so we can user the data in
// the calling function
bool SmartHome::retrieve(char *name, Room *&to_fill) {
    if (!head) {
        return false;
    }

    Node *current = head;

    bool found = false;

    while (current && !found) {
        // well still loop through the whole list even if the first doesn't have
        // a room i guess
        if (current->room && current->room->cmp(name)) {
            to_fill = current->room;
            found = true;
        }

        current = current->next;
    }

    return found;
}

// copy all rooms to a new list
bool SmartHome::copy(SmartHome *&new_list) {
    if (!head) {
        return false;
    }

    Node *current = head;

    while (current) {
        // make a new node and room
        Node *new_node = new Node();
        Room *new_room = new Room(current->room->name_str());

        // add the room to the node
        new_node->room = new_room;

        // copy data in to the new room, i guess i did this backwards
        current->room->copy(new_room);

        // add the node
        new_list->append(new_node);
    }

    return true;
}

// display all the rooms in s a list
bool SmartHome::display_rooms() {
    if (!head) {
        return false;
    }

    Node *current = head;

    while (current) {
        // call display on each node if it has data
        current->display();

        // traverse
        current = current->next;
    }

    return true;
}

// display all accessories for a given room
bool SmartHome::display_accessories(char *room_name) {
    // get a room pinter
    Room *to_show;
    // get a room
    if (!retrieve(room_name, to_show)) {
        return false;
    }

    // call display on that room
    return to_show->display_accessories();
}

bool SmartHome::display_accessories() {
    // return false if no rooms
    if (!head) {
        return false;
    }

    Node *current = head;

    while (current) {
        // call display on each node if it has data
        cout << "\n----------\n" << flush;
        if (current->display()) {
            // if the firs display succeeds we have a room
            current->room->display_accessories();
        }

        // traverse
        current = current->next;
    }

    return true;
}
