#include <cstring>

#include "list.h"
#include "room.h"

Accessory::Accessory() {
    name = 0;
    category = 0;
    status = 0;
}

Accessory::~Accessory() {
    delete[] name;
    delete[] category;
    delete[] status;
}

bool Accessory::add_data(char *&new_name, char *&new_category,
                         char *&new_status) {
    if (new_name == 0 || new_category == 0 || new_status == 0) {
        return false;
    }

    name = new_name;
    category = new_category;
    status = new_status;

    return true;
}

bool Accessory::display() {
    std::cout << "    name: " << name << "\n    category: " << category
              << "\n    status: " << status << '\n';

    return true;
}

bool Accessory::copy(Accessory *&new_accessory) {
    new_accessory->name = new char[strlen(name)];
    strcpy(new_accessory->name, name);

    new_accessory->category = new char[strlen(category)];
    strcpy(new_accessory->category, category);

    new_accessory->status = new char[strlen(status)];
    strcpy(new_accessory->status, status);

    return true;
}

Room::Room() {
    name = 0;
    accessories = 0;
    accessory_count = 0;
}

Room::~Room() {
    delete[] name;
    delete accessories;
}

bool Room::display() {
    std::cout << "\n\nRoom: " << name << std::endl;

    return true;
}

bool Room::append(char *&name, char *&category, char *&status) {
    if (!accessories) {
        accessories = new List();
    }

    return accessories->append(name, category, status);
}

bool Room::copy(Room *&to_fill) {
    to_fill->name = new char[strlen(name)];
    strcpy(to_fill->name, name);

    to_fill->accessories = new List();

    return accessories->copy(to_fill->accessories);
}
