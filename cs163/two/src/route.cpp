#include <cstring>
#include <iostream>

#include "route.h"

void Route::clear() {
    delete[] street;
    street = 0;

    delete[] length;
    length = 0;

    delete[] traffic;
    traffic = 0;

    delete[] note;
    note = 0;

    delete[] construction;
    construction = 0;
}

bool Route::copy_into(Route *&to_fill) {
    if (!street || !length || !traffic || !note || !construction) {
        return false;
    }

    to_fill->street = new char[strlen(street)];
    strcpy(to_fill->street, street);

    to_fill->length = new char[strlen(length)];
    strcpy(to_fill->length, length);

    to_fill->traffic = new char[strlen(traffic)];
    strcpy(to_fill->traffic, traffic);

    to_fill->note = new char[strlen(note)];
    strcpy(to_fill->note, note);

    to_fill->construction = new char[strlen(construction)];
    strcpy(to_fill->construction, construction);

    return true;
}

bool Route::is_empty() {
    if (!street || !length || !traffic || !note || !construction) {
        return true;
    } else {
        return false;
    }
}

bool Route::display() {
    if (!street || !length || !traffic || !note || !construction) {
        return false;
    }

    std::cout << "street: " << street << "\nlength: " << length
              << "\ntraffic: " << traffic << "\nnote: " << note
              << "\nconstruction: " << construction << '\n'
              << std::endl;

    return true;
}
