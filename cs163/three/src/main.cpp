#include <cstring>
#include <iostream>

#include "list.h"
#include "meal_data.h"
#include "table.h"

using namespace std;

// get ether a 'y' or a 'n' from the user
int get_user_input_yes_or_no() {
    bool bad_input = true;
    char user_input = 'n';
    char lower_input = 'n';

    do {
        // make a prompt for the user
        cout << " (y|n) -> ";

        // get a char from input
        cin >> user_input;
        cin.clear();
        cin.ignore(1000, '\n');

        // make the given character lower case if it is not
        lower_input = tolower(user_input);
        if (lower_input != 'y' || lower_input != 'n') {
            cout << "bad input pleas give ether a 'y' or an 'n'" << endl;
            bad_input = true;
        } else {
            bad_input = false;
        }

        // loop if the user_input was not a 'y' or an 'n'
    } while (bad_input);

    return lower_input;
}

// get a user input between an exclusive range
int get_user_input_int(int start, int stop) {
    int user_input = 0;
    bool success = false;
    do {
        // make the prompt show the range we need
        cout <<  " (" << start + 1 << "|" << stop - 1 << ")"  << " -> ";

        // get user_input as an int
        cin >> user_input;
        cin.clear();
        cin.ignore(1000, '\n');

        // make sure the input is within the range
        if (user_input < start || user_input > stop) {
            cout << "bad input" << endl;
            success = false;
        } else {
            success = true;
        }
    } while (!success);

    return user_input;
}

// fill an array from user_input
bool get_user_input_array(char *&to_fill) {
    bool success = true;

    // get a array buf sized 1000
    const int buf_size = 1000;
    char *temp = new char[buf_size];

    do {
        cout << " (text) -> ";
        // get user_input as a string
        cin.get(temp, buf_size, '\n');
        cin.clear();
        cin.ignore(buf_size, '\n');

        if (temp[0] == '\0') {
            cout << "bad input" << endl;
            success = false;
        } else {
            success = true;
        }

    } while (!success);

    // copy data to the passed in array
    to_fill = new char[strlen(temp)];
    strcpy(to_fill, temp);

    // remove temp array
    delete[] temp;

    return success;
}

// get a DataKey enum from the user
DataKey get_data_key() {
    // print menu
    cout << "what value will you remove on:\n"
            "   1) name_of_meal\n"
            "   2) name_of_venue\n"
            "   3) approximate_price\n"
            "   4) rating\n"
            "   5) review\n";

    // get input
    int user_input = get_user_input_int(0, 6);

    // pattern match off input returning the right enum
    switch (user_input) {
        case 1: {
            return NameOfMeal;
        }
        case 2: {
            return NameOfVenue;
        }
        case 3: {
            return ApproximatePrice;
        }
        case 4: {
            return Rating;
        }
        case 5: {
            return Review;
        }
        default: {
            return NameOfMeal;
        }
    }
}

// hand make a meal and add it to a table
bool add_to_table(Table *table) {
    // get a temp meal to make the data
    MealData *temp_meal = new MealData();

    cout << "pleas give meal name" << endl;
    bool success = get_user_input_array(temp_meal->name_of_meal);

    cout << "pleas give venue name" << endl;
    success = get_user_input_array(temp_meal->name_of_venue);

    cout << "pleas give approximate price" << endl;
    success = get_user_input_array(temp_meal->approximate_price);

    cout << "pleas give rating (e.g. 3 stars)" << endl;
    success = get_user_input_array(temp_meal->rating);

    cout << "pleas give review" << endl;
    success = get_user_input_array(temp_meal->review);

    cout << "is the place a restaurant" << endl;
    char input = get_user_input_yes_or_no();
    if (tolower(input) == 'y') {
        temp_meal->venue_type = Restaurant;
    } else {
        temp_meal->venue_type = Cart;
    }

    // do the actual add
    success = table->add(temp_meal->name_of_meal, temp_meal);

    delete temp_meal;

    return success;
}

// call the remove function for the table with the correct arguments
bool remove_by(Table *table, DataKey data_key, char *key) {
    // make a new list to retrieve data form the remove function
    List *list = new List();

    // do the thing
    bool success = table->remove_by(data_key, key, list);

    // print if we are successful or not
    if (success && list->is_empty()) {
        cout << "did not find match for " << key << "\n--------------------\n"
             << endl;

    } else if (success) {
        cout << "removed the following node(s) from the table.\n"
                "\n--------------------";
        if (list) {
            list->display();
        }

        cout << "\nnow sowing whats left in the table\n--------------------";
        table->display_all();

    } else {
        cout << "table error" << endl;
    }

    // if list exists then remove it
    if (list) {
        delete list;
    }

    return success;
}

// call the remove function keyed by NameOfMeal
bool remove_by_key(Table *table) {
    char *key = 0;
    cout << "what is the key:\n";
    bool success = get_user_input_array(key);

    success = remove_by(table, NameOfMeal, key);

    delete[] key;

    return success;
}

// call the remove function but with user defined key
bool remove_by_value(Table *table) {
    DataKey data_key = get_data_key();

    cout << "what is the full string you want to look for:\n";
    char *key = 0;
    bool success = get_user_input_array(key);

    success = remove_by(table, data_key, key);

    if (key) {
        delete[] key;
    }

    return success;
}

// retrieve data based on a substring
bool retrieve(Table *table) {
    DataKey data_key = get_data_key();

    // get the substring
    cout << "what is the sub string you want to look for:\n";
    char *sub_str = 0;
    bool success = get_user_input_array(sub_str);

    // get a new list
    List *list = new List();

    // do the retrieve
    success = table->retrieve(data_key, sub_str, list);

    // if successful then print results
    if (success && list->is_empty()) {
        cout << "no match for " << sub_str << "\n--------------------\n"
             << endl;

    } else if (success) {
        cout << "got data from sub string\n--------------------";
        list->display();

        cout << "\n\nshowing that the table is still intact"
                "\n--------------------";
        table->display_all();

    } else {
        cout << "table error" << endl;
    }

    delete[] sub_str;

    if (list) {
        delete list;
    }

    return success;
}

// give the user a few options to test the ADT
int test_menu(Table *table) {
    bool success = true;
    int user_input = 0;

    do {
        cout << "how would you like to test data:\n"
                "    1) quit\n"
                "    2) return to last menu\n"
                "    3) add by hand\n"
                "    4) remove by key (meal name)\n"
                "    5) remove by value (any value not just meal name)\n"
                "    6) retrieve (print) by value (any value not just meal "
                "name)\n"
                "    7) display all (no sort order) \n";

        user_input = get_user_input_int(0, 7);

        // runt the asked for function
        if (user_input == 3) {
            success = add_to_table(table);

        } else if (user_input == 4) {
            success = remove_by_key(table);

        } else if (user_input == 5) {
            success = remove_by_value(table);

        } else if (user_input == 6) {

            success = retrieve(table);

        } else if (user_input == 7) {
            success = table->display_all();
        }

    } while (user_input >= 3 && success);

    // if not successful then return -1 to signify failure
    if (!success) {
        return -1;
    } else {
        return user_input;
    }
}

// the main program menu
bool main_menu(Table *table) {
    int user_input = 0;
    bool success = true;

    do {
        cout << "\nwhat would yo like to do\n"
                "    1) quit\n"
                "    2) load data from file\n"
                "    3) add by hand\n"
                "    4) test data\n";

        // run the asked for function
        user_input = get_user_input_int(0, 5);
        if (user_input == 2) {
            char path[] = "data.txt";
            cout << "\nfilling data from " << path << endl;
            success = fill_data_from_file(table, path);

        } else if (user_input == 3) {
            success = add_to_table(table);

        } else if (user_input == 4) {
            user_input = test_menu(table);

            // if user_input == -1 then it failed
            if (user_input == -1) {
                success = false;
            } else {
                success = true;
            }
        }

        // while everything is fine and user_input is not a 1
    } while (user_input != 1 && success);

    return success;
}

// print a welcome message
void welcome_menu() {
    cout << "Welcome to the meal helper\nPleas make use of the load from  file "
            "feature.\nThe default path is PWD/data.txt\nThe format is\n meal "
            "name, venue name, price, meal rating, meal review\n and if it is "
            "a restaurant\n\nAn example would be as follows\n note that any "
            "line STARTING with a # is ignored\ncoffee$cafe cool place$2.50$5 "
            "stars$good coffee$false\n"
         << endl;
}

// the function to be called by the os/gcc
int main() {
    // welcome the user
    welcome_menu();

    const int table_size = 11;

    // make a new table
    Table *table = new Table(table_size);

    // start the rest of the program
    main_menu(table);

    // removed allocated table
    delete table;

    return 0;
}
