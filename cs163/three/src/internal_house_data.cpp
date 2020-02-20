#include <cstring>
#include <iostream>

#include "internal_house_data.h"

InternalHouseData::InternalHouseData() {
    location = 0;
    size = 0;
    bedrooms = 0;
    distance_to_psu = 0;
    notes = 0;
}

InternalHouseData::~InternalHouseData() {
    delete[] location;
    delete[] size;
    delete[] bedrooms;
    delete[] distance_to_psu;
    delete[] notes;
}

bool InternalHouseData::copy_from_house_data(HouseData *to_add) {
    location = new char[strlen(to_add->location)];
    strcpy(location, to_add->location);

    size = new char[strlen(to_add->size)];
    strcpy(size, to_add->size);

    bedrooms = new char[strlen(to_add->bedrooms)];
    strcpy(bedrooms, to_add->bedrooms);

    distance_to_psu = new char[strlen(to_add->distance_to_psu)];
    strcpy(distance_to_psu, to_add->distance_to_psu);

    notes = new char[strlen(to_add->notes)];
    strcpy(notes, to_add->notes);

    return true;
}

bool InternalHouseData::is_empty() {
    if (!location || !size || !bedrooms || !distance_to_psu || !notes) {
        return true;
    } else if (location[0] == '\0' && size[0] == '\0' && bedrooms[0] == '\0' &&
               distance_to_psu[0] == '\0' && notes[0] == '\0') {
        return true;
    } else {
        return false;
    }
}

bool InternalHouseData::display() {
    if (is_empty()) {
        return false;
    }

    std::cout << "Location: " << location << "\nSize: " << size
              << "\nBedrooms: " << bedrooms
              << "\nDistance to PSU : " << distance_to_psu
              << "\nNotes: " << notes << std::endl;

    return true;
}
