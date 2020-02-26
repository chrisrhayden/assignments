#include <cstring>
#include <fstream>

#include "list.h"
#include "table.h"

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
bool Table::add(char *key, MealData *to_add) {
    // get the hash
    long int hash = hash_function(table_size, key);

    // make a new list in the hash index if it dose not exist
    if (!table[hash]) {
        table[hash] = new List();
    }

    // ask the list to add the data
    return table[hash]->add(to_add);
}

// get data based on key
bool Table::get(char *key, MealData *to_fill) {
    long int hash = hash_function(table_size, key);

    List *maybe_list = table[hash];

    // if key dose not exists return false;
    if (!maybe_list && maybe_list->is_empty()) {
        return false;
    }

    // return whether we get data from list
    return maybe_list->get(key, to_fill);
}

// remove from the table
bool Table::_remove(DataKey data_key, char *key, MealData *to_fill) {
    long int hash = hash_function(table_size, key);

    List *maybe_list = table[hash];

    // if table dose not have the key return false
    if (!maybe_list || maybe_list->is_empty()) {
        return false;
    }

    // weather the list removed the data
    return maybe_list->remove(data_key, key, to_fill);
}

// call _remove with the right values
bool Table::remove(char *key, MealData *to_fill) {
    if (!to_fill) {
        return false;
    }

    return _remove(NameOfMeal, key, to_fill);
}

// remove by the given FULL value and a key to match
bool Table::remove_by(DataKey data_key, char *sub_str, List *meal_list) {
    // if neath exist the return false
    if (!table || !meal_list) {
        return false;
    }

    bool success = true;
    List **current = table;

    for (int i = 0; i < table_size && success; ++i) {
        // if data try and remove
        if (*current && !(*current)->is_empty()) {
            MealData *new_meal = new MealData();

            // ask the list to remove if matches
            success = (*current)->remove(data_key, sub_str, new_meal);

            // add to the returned list
            if (success && !new_meal->is_empty()) {
                success = meal_list->add(new_meal);
            }

            delete new_meal;
        }

        ++current;
    }

    return success;
}

// get data based on the data_key given
bool Table::retrieve(DataKey data_key, char *sub_str, List *meal_list) {
    if (!table || !meal_list) {
        return false;
    }

    bool success = true;
    List **current = table;

    for (int i = 0; i < table_size; ++i) {
        if (*current && !(*current)->is_empty()) {
            // ask the list if it has nodes with a value match by sub_str
            success = (*current)->retrieve(data_key, sub_str, meal_list);
        }

        ++current;
    }

    return success;
}

// display all items in the table from the beginning of the array to the end,
// mostly for debugging
bool Table::display_all() {
    List **current = table;

    bool success = true;

    for (int i = 0; i < table_size && success; ++i) {
        // dereference to get to the node
        if (current[i] && !current[i]->is_empty()) {
            // if there is data then ask it to display itself
            success = current[i]->display();
        }
    }

    return success;
}

long int hash_function(int table_size, char *key) {
    // lol, just for now
    return key[0] % table_size;
}

// these functions kinda suck but oh well ---------->
// a quick wrapper around an array and its size
struct ToParse {
    ToParse(int size);
    ~ToParse();
    char *source;
    int max_size;
};

// ToParse constructor
ToParse::ToParse(int size) {
    source = new char[size];
    source[0] = '\0';
    max_size = size;
}

// ToParse deconstructor
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

// parse the string given in to smaller string and make a new meal based on it
bool parse_line(ToParse *to_parse, MealData *to_fill) {
    bool success = true;

    char delimiter[] = "$";

    // this function is kinda confusing but
    // first call strtok with a string to tokenize and a delimiter
    // then every subsequent call to strtok with null instead of a string
    // will give a pointer to a new array with the next token from the
    // string I guess strtok will clean everything up, idk
    char *split = strtok(to_parse->source, delimiter);

    success = strcpy_safe(split, to_fill->name_of_meal);

    // if success then keep going, else just stop an d return false
    if (success) {
        split = strtok(0, delimiter);
        success = strcpy_safe(split, to_fill->name_of_venue);
    }

    if (success) {
        split = strtok(0, delimiter);
        success = strcpy_safe(split, to_fill->approximate_price);
    }

    if (success) {
        split = strtok(0, delimiter);
        success = strcpy_safe(split, to_fill->rating);
    }

    if (success) {
        split = strtok(0, delimiter);
        success = strcpy_safe(split, to_fill->review);
    }

    if (success) {

        split = strtok(0, delimiter);

        if (!split) {
            success = false;
        } else if (strcmp(split, "true") == 0) {
            to_fill->venue_type = Restaurant;
        } else {
            to_fill->venue_type = Cart;
        }
    }

    // TODO: maybe do a few checks if the data is correct
    // explicitly check for false to be clear
    return success && to_fill->is_empty() == false;
}

// call parse_line and add the meal to the given table
bool parse_line_and_add_to_table(Table *to_fill, ToParse *to_parse) {
    // ignore any line starting with a #
    if (to_parse->source[0] == '#') {
        return true;
    }

    // parse_line will allocate all the needed memory
    MealData *new_meal = new MealData();

    // parse the data and add to the queue
    if (!parse_line(to_parse, new_meal)) {
        delete new_meal;

        return false;
    }

    // add the new key to the table
    bool success = to_fill->add(new_meal->name_of_meal, new_meal);

    delete new_meal;

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
