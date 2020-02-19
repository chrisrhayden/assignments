#include <cctype>
#include <iostream>

#include "list.h"

using namespace std;

// prototypes
void build_user_data(LinkedList *list);
void display_by_user_priority(LinkedList *list);
void display_menu(LinkedList *list);
void main_menu(LinkedList *list);
void remove_menu(LinkedList *list);

int main() {
    // make a new list
    LinkedList main_list = LinkedList();

    build_user_data(&main_list);

    main_menu(&main_list);

    // show length i guess
    cout << "\n\nlength " << main_list.length() << endl;

    return 0;
}

// a function to print a message and call list.build()
void build_user_data(LinkedList *list) {
    cout << "\npleas enter todo items\nleave the name field blank to "
            "finish entering items\n"
         << endl;

    // ask the user for data in a loop
    list->build();
}

// the menu function
void main_menu(LinkedList *list) {
    // set up user input verbals
    char lower_in = 'e';
    char user_input = 'e';

    // display the list
    do {
        cout << "would you like to [r]emove item, [d]isplay list or [e]xit\n "
                "-> ";
        cin >> user_input;
        cin.ignore(1000, '\n');

        // make user_input lower to so we dont have to do this more then once
        lower_in = tolower(user_input);

        if (lower_in == 'r') {
            remove_menu(list);
        } else if (lower_in == 'd') {
            // display the list
            display_menu(list);
        }

    } while (lower_in != 'e');
}

// let the user select what to remove
void remove_menu(LinkedList *list) {
    char temp[1000];
    cout << "what item would you like to remove (by name)\n -> ";

    cin.get(temp, 1000, '\n');
    cin.clear();
    cin.ignore(1000, '\n');

    list->remove_item(temp);
}

// the display menu
void display_menu(LinkedList *list) {
    // get user input as a char
    char user_input = 'n';
    cout << "\n--------------------\nwould you like to display [a]ll, by "
            "[p]riority, or [n]one\n (p|a|n) -> ";
    cin >> user_input;
    cin.ignore(1000, '\n');

    // check if its a y || Y
    if (tolower(user_input) == 'y') {
        // ask the user to give a priority
        display_by_user_priority(list);
    } else if (tolower(user_input) == 'a') {
        cout << "\n--------------------\n# All items" << endl;
        list->display();
    }
}

// get a priority from the user
void display_by_user_priority(LinkedList *list) {
    int priority = 0;

    cout << "\n--------------------\nwhat priority do you want to filter by: 1 "
            "- 10\n -> ";
    cin >> priority;
    cin.ignore(1000, '\n');

    cout << "\n--------------------\n# Items with priority " << priority
         << endl;

    // call display_priority with user input
    list->display_priority(priority);
}
