#include <cstring>
#include <iostream>

#include "list.h"
#include "meal_data.h"
#include "table.h"

using namespace std;

int get_user_input_yes_or_no() {
    bool bad_input = true;
    char user_input = 'n';

    do {
        cout << " (y|n) -> ";

        cin >> user_input;
        cin.clear();
        cin.ignore(1000, '\n');

        if (tolower(user_input) == 'y' || towlower(user_input) == 'n') {
            bad_input = false;
        }

    } while (bad_input);

    return user_input;
}

// get a user input between an exclusive range
int get_user_input_int(int start, int stop) {
    int user_input = 0;
    bool success = false;
    do {
        cout << " -> ";
        cin >> user_input;
        cin.clear();
        cin.ignore(1000, '\n');

        if (user_input < start || user_input > stop) {
            cout << "bad input" << endl;
            success = false;
        } else {
            success = true;
        }
    } while (!success);

    return user_input;
}

bool get_user_input_array(char *&to_fill) {
    bool success = true;
    const int buf_size = 1000;
    char *temp = new char[buf_size];

    do {
        cout << " (text) -> ";
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

    to_fill = new char[strlen(temp)];
    strcpy(to_fill, temp);

    delete[] temp;

    return success;
}

DataKey get_data_key() {
    cout << "what value will you remove on:\n"
            "   1) name_of_meal\n"
            "   2) name_of_venue\n"
            "   3) approximate_price\n"
            "   4) rating\n"
            "   5) review\n";

    int user_input = get_user_input_int(0, 6);

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

bool add_to_table(Table *table) {
    MealData *new_meal = new MealData();

    cout << "pleas give meal name" << endl;
    bool success = get_user_input_array(new_meal->name_of_meal);

    cout << "pleas give venue name" << endl;
    success = get_user_input_array(new_meal->name_of_venue);

    cout << "pleas give approximate price" << endl;
    success = get_user_input_array(new_meal->approximate_price);

    cout << "pleas give rating (e.g. 3 stars)" << endl;
    success = get_user_input_array(new_meal->rating);

    cout << "pleas give review" << endl;
    success = get_user_input_array(new_meal->review);

    cout << "is the place a restaurant" << endl;
    char input = get_user_input_yes_or_no();
    if (tolower(input) == 'y') {
        new_meal->venue_type = Restaurant;
    } else {
        new_meal->venue_type = Cart;
    }

    success = table->add(new_meal->name_of_meal, new_meal);

    delete new_meal;

    return success;
}

bool remove_by(Table *table, DataKey data_key, char *key) {
    List *list = new List();

    bool success = table->remove_by(data_key, key, list);

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

    if (list) {
        delete list;
    }

    return success;
}

bool remove_by_key(Table *table) {
    char *key = 0;
    cout << "what is the key:\n";
    bool success = get_user_input_array(key);

    success = remove_by(table, NameOfMeal, key);

    delete[] key;

    return success;
}

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

bool retrieve(Table *table) {
    DataKey data_key = get_data_key();

    cout << "what is the sub string you want to look for:\n";
    char *sub_str = 0;
    bool success = get_user_input_array(sub_str);

    List *list = new List();

    success = table->retrieve(data_key, sub_str, list);

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

    if (!success) {
        return -1;
    } else {
        return user_input;
    }
}

bool main_menu(Table *table) {
    int user_input = 0;
    bool success = true;

    do {
        cout << "\nwhat would yo like to do\n"
                "    1) quit\n"
                "    2) load data from file\n"
                "    3) add by hand\n"
                "    4) test data\n";

        user_input = get_user_input_int(0, 5);
        if (user_input == 2) {
            char path[] = "data.txt";
            cout << "\nfilling data from " << path << endl;
            success = fill_data_from_file(table, path);

        } else if (user_input == 3) {
            success = add_to_table(table);

        } else if (user_input == 4) {
            user_input = test_menu(table);

            if (user_input == -1) {
                success = false;
            } else {
                success = true;
            }
        }

    } while (user_input != 1 && success);

    return success;
}

void welcome_menu() {
    cout << "Welcome to the meal helper\nPleas make use of the load from  file "
            "feature.\nThe default path is PWD/data.txt\nThe format is\n meal "
            "name, venue name, price, meal rating, meal review\n and if it is "
            "a restaurant\n\nAn example would be as follows\n note that any "
            "line STARTING with a # is ignored\ncoffee$cafe cool place$2.50$5 "
            "stars$good coffee$false\n"
         << endl;
}

int main() {
    welcome_menu();

    const int table_size = 11;

    Table *table = new Table(table_size);

    main_menu(table);

    delete table;

    return 0;
}
