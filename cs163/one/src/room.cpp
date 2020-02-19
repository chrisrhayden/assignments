#include <cstring>
#include <iostream>

#include "room.h"

// basic constructor
Accessory::Accessory() {
    name = 0;
    category = 0;
    status = 0;

    next = 0;
}

// basic destructor
Accessory::~Accessory() {
    delete[] name;
    delete[] category;
    delete[] status;

    next = 0;
}

// copy this data in to another Accessory
bool Accessory::copy(Accessory *&to_fill) {
    to_fill->name = new char[strlen(name)];
    strcpy(to_fill->name, name);

    to_fill->category = new char[strlen(category)];
    strcpy(to_fill->category, category);

    to_fill->status = new char[strlen(status)];
    strcpy(to_fill->status, status);

    return true;
}

// display data
bool Accessory::display() {
    std::cout << "\n\nAccessory:\nname: " << name << "\ncategory: " << category
              << "\nstatus: " << status << std::endl;

    return true;
}

// basic constructor
Room::Room(char *name_str) {
    char *new_name = new char[strlen(name_str)];
    strcpy(new_name, name_str);

    name = new_name;
    head = 0;
    tail = 0;
}

// basic destructor
Room::~Room() {
    delete[] name;

    Accessory *current = head;
    Accessory *temp = 0;

    while (current) {
        temp = current->next;

        delete current;

        current = temp;
    }
}

// a quick hack as i forgot to order the nodes, same as add_ord in
// smart_home.cpp but compare the whole category string this time
void Room::add_ord(Accessory *&to_add) {
    bool success = false;

    Accessory *current = head;
    Accessory *prev = 0;

    while (current && !success) {
        // compare category string case sensitive
        if (strcmp(to_add->category, current->category) == 0) {
            if (current == head) {
                to_add->next = head;
                head = to_add;
            } else {
                prev->next = to_add;
                to_add->next = current;
            }

            success = true;
        }

        prev = current;
        current = current->next;
    }

    if (!success) {
        tail->next = to_add;
        tail = to_add;
    }
}

// add an Accessory to the list of other accessories
bool Room::append(Accessory *&to_add) {
    if (!to_add) {
        return false;
    }

    if (!head) {
        // new list
        head = to_add;
        tail = to_add;
    } else {
        add_ord(to_add);
    }

    return true;
}

// remove a node keeping the others attached
bool Room::remove(char *to_find) {
    bool success = false;
    Accessory *current = head;
    Accessory *prev = 0;

    // while we haven't found the node and still have data
    while (current && !success) {
        // cmp the accessory name
        if (strcmp(current->name, to_find) == 0) {
            // if the previous exists the we have to connect ether in the middle
            // or end
            if (prev) {
                // connect the previous to the next node
                prev->next = current->next;

                // we are at the end
                if (current == tail) {
                    tail = prev;
                }

            } else {
                head = current->next;

                // list is new empty and current->next should be a 0 as well
                if (current == tail) {
                    tail = 0;
                }
            }

            // remove current node
            delete current;

            // stop the loop and to return true
            success = true;
        } else {
            prev = current;
            current = current->next;
        }
    }

    return success;
}

// fill a new room from this one
bool Room::copy(Room *&to_fill) {
    if (!head) {
        return false;
    }

    to_fill->name = new char[strlen(name)];
    strcpy(to_fill->name, name);

    Accessory *current = head;

    // add this rooms accessories if any
    while (current) {
        Accessory *new_accessory = new Accessory();

        current->copy(new_accessory);

        to_fill->append(new_accessory);
    }

    return true;
}

// display own name
bool Room::display_name() {
    std::cout << "room: " << name << std::endl;
    return true;
}

// display all accessories for this room
bool Room::display_accessories() {
    // return false if no accessories
    if (!head) {
        return false;
    }

    Accessory *current = head;

    while (current) {
        current->display();

        current = current->next;
    }

    return true;
}

// just a simple cmp wrapper
bool Room::cmp(char *to_cmp) { return strcmp(name, to_cmp) == 0; }

// return a str of the room name to keep data sorta private
char *Room::name_str() const { return name; }
