#include <cstring>
#include <fstream>

#include <iostream>
using namespace std;

#include "list.h"
#include "table.h"

// prototype so we can define it below and use it in the  class's and not add
// it to the table.h so it cant be imported by the outside

// parse_line and add the tokens to the right struct members
bool parse_line(ToParse *to_parse, char *&new_key, HouseData *to_fill);
// the basic hash function used by the table class
long int hash_function(int table_size, char *key);

// the table constructor
Table::Table(int size) {
    // set the table size
    table_size = size;

    // make a new list
    table = new List *[table_size];

    // make a list pointer
    List **current = table;

    // iterate over the while table and set each index to null
    for (int i = 0; i < size; ++i) {
        // set the current index to null
        current = 0;
        // get to the next table index or list node
        ++current;
    }

    return;
}

// the table deconstructor
Table::~Table() {
    // if no table then were good to go
    if (!table) {
        return;
    }

    // get a list pointer
    List **current = table;

    // iterate to end of table
    for (int i = 0; i < table_size; ++i) {
        // remove List class
        delete *current;
        // get to the next index / list class
        ++current;
    }

    // finally free the array
    delete[] table;
}

// add to the hash table
bool Table::add(char *key, HouseData *to_add) {
    long int hash = hash_function(table_size, key);

    if (!table[hash]) {
        List *list = new List();
        table[hash] = list;
    }

    return table[hash]->add(hash, to_add);
}

// display all items in the table from the beginning of the array to the end,
// mostly for debugging
bool Table::display_all() {
    List **current = table;

    bool success = true;

    for (int i = 0; i < table_size && success; ++i) {
        // dereference to get to the node
        if (*current) {
            // if there is data then ask it to display itself
            success = (*current)->display();
        }

        ++current;
    }

    return success;
}

long int hash_function(int table_size, char *key) {
    // lol, just for now
    return key[0] % table_size;
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

// add source to dest but safely, revers c order because I dont like c's way
bool strcpy_safe(char *source, char *&dest) {
    // if source and it has data then
    if (!source && source[0] == '\0') {
        return false;
    }

    dest = new char[strlen(source)];
    // c is fucking stupid
    strcpy(dest, source);
    return dest[0] != '\0';
}

bool parse_line(ToParse *to_parse, char *&new_key, HouseData *to_fill) {
    bool success = true;

    char delimiter[] = "$";

    // this function is kinda confusing but
    // first call strtok with a string to tokenize and a delimiter
    // then every subsequent call to strtok with null instead of a string
    // will give a pointer to a new array with the next token from the
    // string I guess strtok will clean everything up, idk
    char *split = strtok(to_parse->source, delimiter);

    success = strcpy_safe(split, new_key);

    if (success) {
        split = strtok(0, delimiter);
        success = strcpy_safe(split, to_fill->location);
    }

    if (success) {
        split = strtok(0, delimiter);
        success = strcpy_safe(split, to_fill->size);
    }

    if (success) {
        split = strtok(0, delimiter);
        success = strcpy_safe(split, to_fill->bedrooms);
    }

    if (success) {
        split = strtok(0, delimiter);
        success = strcpy_safe(split, to_fill->distance_to_psu);
    }

    if (success) {
        split = strtok(0, delimiter);
        success = strcpy_safe(split, to_fill->notes);
    }

    // TODO: maybe do a few checks if the data is correct
    // explicitly check for false to be clear
    return to_fill->is_empty() == false;
}

bool parse_line_and_add_to_table(Table *to_fill, ToParse *to_parse) {
    // ignore any line starting with a #
    if (to_parse->source[0] == '#') {
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
    bool success = to_fill->add(new_key, new_house);

    delete[] new_key;
    delete new_house;

    return success;
}

// fill the table from a file
bool fill_data_from_file(Table *to_fill, char *path) {
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

    // while its not the end of the file, we can still get data and the
    // parsing worked last time
    while (input_file.peek() && !input_file.eof() && success) {
        input_file.getline(to_parse->source, to_parse->max_size);

        success = parse_line_and_add_to_table(to_fill, to_parse);

        to_parse->source[0] = '\0';
    }

    // close as were done
    input_file.close();

    // delete the temporary array
    delete to_parse;
    return success;
}
