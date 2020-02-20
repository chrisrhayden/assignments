#include <cstring>
#include <fstream>
#include <iostream>

#include "house_data.h"
#include "table.h"

bool parse_and_add(char new_key[], HouseData &to_fill, char *to_parse);

HouseData::HouseData() {
    bedrooms = 0;
    size = 0;
    location = 0;
    distance_to_psu = 0;
    notes = 0;
}

HouseData::~HouseData() {
    delete[] location;
    delete[] size;
    delete[] bedrooms;
    delete[] distance_to_psu;
    delete[] notes;
}

bool HouseData::is_empty() {
    if (location[0] == '\0' && size[0] == '\0' && bedrooms[0] == '\0' &&
        distance_to_psu[0] == '\0' && notes[0] == '\0') {
        return true;
    } else {
        return false;
    }
}

bool HouseData::display() {
    if (is_empty()) {
        return false;
    }

    std::cout << "Location: " << location << "\nSize: " << size
              << "\nBedrooms:" << bedrooms
              << "\nDistance to PSU: " << distance_to_psu
              << "\nNotes: " << notes << std::endl;

    return true;
}
