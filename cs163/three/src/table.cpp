#include <cstring>
#include <fstream>

#include <iostream>
using namespace std;

#include "list.h"
#include "table.h"

bool parse_line(ToParse *to_parse, char *&new_key, HouseData *to_fill);

long int hash_function(char *key, int table_size) {
    // lol, just for now
    return key[0] % table_size;
}

Table::Table(int size) {
    table = new List *[size];

    List **current = table;

    for (int i = 0; i < size; ++i) {
        current = 0;
        ++current;
    }

    table_size = size;
    return;
}

Table::~Table() {
    if (!table) {
        return;
    }

    List **current = table;

    for (int i = 0; i < table_size; ++i) {
        delete *current;
        ++current;
    }

    // delete *current;

    delete[] table;
}

bool Table::add(char *key, HouseData *to_add) {
    long int hash = hash_function(key, table_size);

    if (!table[hash]) {
        List *list = new List();
        table[hash] = list;
    }

    return table[hash]->add(hash, to_add);
}

bool Table::display_all() {
    List **current = table;

    bool success = true;

    for (int i = 0; i < table_size && success; ++i) {
        if (*current) {
            success = (*current)->display();
        }

        ++current;
    }

    return success;
}

bool Table::fill_data_from_file(char *path) {
    int max_size = 1000;
    // get a handle on the input file
    std::ifstream input_file;

    // open the file
    input_file.open(path);

    // check if there is data and we really do have a handle on the file
    if (!input_file.peek()) {
        // close to be sure
        input_file.close();
        return false;
    }

    ToParse *to_parse = new ToParse(max_size);

    bool success = true;

    // while its not the end of the file, we can still get data and the parsing
    // worked last time
    while (input_file.peek() && !input_file.eof() && success) {
        input_file.getline(to_parse->source, to_parse->max_size);

        success = parse_line_and_add_to_data(to_parse);
        to_parse->source[0] = '\0';
    }

    // close as were done
    input_file.close();

    // delete the temporary array
    delete to_parse;
    return success;
}

bool Table::parse_line_and_add_to_data(ToParse *to_parse) {
    // ignore any line starting with a #
    if (to_parse->source[0] == '#') {
        // clear the temp array more or less
        to_parse->source[0] = '\0';
        return true;
    }

    // parse_line will allocate all the needed memory
    char *new_key = 0;
    HouseData *new_house = new HouseData();

    // parse the data and add to the queue
    if (!parse_line(to_parse, new_key, new_house)) {
        delete[] new_key;
        delete new_house;

        return false;
    }

    // add the new key to the table
    bool success = add(new_key, new_house);

    delete[] new_key;
    delete new_house;

    return success;
}

// these functions kinda suck but oh well ---------->
ToParse::ToParse(int size) {
    source = new char[size];
    source[0] = '\0';
    max_size = size;
}

ToParse::~ToParse() {
    max_size = 0;
    delete[] source;
}

bool add_if_exists(char *source, char *&to_fill) {
    if (source) {
        to_fill = new char[strlen(source)];
        strcpy(to_fill, source);
        return true;
    }

    return false;
}

bool parse_line(ToParse *to_parse, char *&new_key, HouseData *to_fill) {
    bool success = true;

    char delimiter[] = "$";

    char *split = strtok(to_parse->source, delimiter);

    success = add_if_exists(split, new_key);

    if (success) {
        split = strtok(0, delimiter);
        success = add_if_exists(split, to_fill->location);
    }

    if (success) {
        split = strtok(0, delimiter);
        success = add_if_exists(split, to_fill->size);
    }

    if (success) {
        split = strtok(0, delimiter);
        success = add_if_exists(split, to_fill->bedrooms);
    }

    if (success) {
        split = strtok(0, delimiter);
        success = add_if_exists(split, to_fill->distance_to_psu);
    }

    if (success) {
        split = strtok(0, delimiter);
        success = add_if_exists(split, to_fill->notes);
    }

    // TODO: maybe do a few checks if the data is correct
    return to_fill->is_empty() == false;
}

// fill a sting until a pattern
// int fill_from_str(ToParse *to_parse, char *&to_fill, int stop) {
//     if (stop == -1) {
//         return -1;
//     }
//
//     // make a temporary array to hold the data from the source string
//     char *temp = new char[to_parse->max_size];
//     // get the full source length as a default stopping condition
//     int parse_len = strlen(to_parse->source);
//
//     // instantiate i and target outside the loop to use later in the function
//     int i = 0;
//     int end = stop;
//     // fill a given sting hard code a pattern for ease of use
//     for (; i < parse_len && to_parse->source[end] != '$'; ++i, ++end) {
//         temp[i] = to_parse->source[end];
//     }
//
//     // if i is 0 then noting was done and so an error is in the file
//     if (i == 0) {
//         end = -1;
//
//     } else {
//         // cap off the string
//         temp[i] = '\0';
//
//         // now make a perfectly fitting array for the segment
//         to_fill = new char[strlen(temp)];
//
//         // copy the segment in to the given array
//         strcpy(to_fill, temp);
//     }
//
//     // remove the temporary array
//     delete[] temp;
//
//     // return new end
//     return end;
// }
//
// bool parse_and_add(ToParse *to_parse, char *&new_key, HouseData *to_fill) {
//     int stopped = 0;
//
//     char delimiter[] = "$";
//
//     char *split = strtok(to_parse->source, delimiter);
//
//     // fill the key first
//     stopped = fill_from_str(to_parse, new_key, stopped);
//     // add 1 to the stopped variable to skip the last $ char
//     stopped = fill_from_str(to_parse, to_fill->distance_to_psu, stopped + 1);
//     stopped = fill_from_str(to_parse, to_fill->size, stopped + 1);
//     stopped = fill_from_str(to_parse, to_fill->bedrooms, stopped + 1);
//     stopped = fill_from_str(to_parse, to_fill->location, stopped + 1);
//     stopped = fill_from_str(to_parse, to_fill->notes, stopped + 1);
//     // TODO: maybe do a few checks if the data is correct
//
//     return stopped;
// }

// <----------
