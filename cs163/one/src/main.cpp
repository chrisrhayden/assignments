#include <cstring>
#include <iostream>

#include "smart_home.h"

using namespace std;

// util functions to make or fill arrays
void fill_array_by_size(char *&dest, char *&temp, int size) {
    cin.get(temp, size, '\n');
    cin.clear();
    cin.ignore(size, '\n');

    dest = new char[strlen(temp)];
    strcpy(dest, temp);
}

// util functions to make or fill arrays
void fill_array_by_size(char *to_fill, int size) {
    cin.get(to_fill, size, '\n');
    cin.clear();
    cin.ignore(size, '\n');
}

// a function to take in data for an accessory
void make_accessory_data(Accessory *&accessory, char *&temp, int size) {
    // Accessory is just basic data so for convenience we just use a struct
    // and instantiate it our selves
    cout << "\nwhat is the name of this accessory\n -> ";
    fill_array_by_size(accessory->name, temp, size);

    cout << "\nwhat is the category of this accessory\n -> ";
    fill_array_by_size(accessory->category, temp, size);

    cout << "\nwhat is the status of this accessory\n -> ";
    fill_array_by_size(accessory->status, temp, size);
}

// add accessories to the given home
void make_accessorys(SmartHome *&home) {
    const int size = 1000;

    int accessory_count = 0;

    bool success = true;

    // size an array
    char *temp = new char[size];

    cout << "\n\nwhat room will you add to\n -> ";

    // get a str
    char *room_name;
    fill_array_by_size(room_name, temp, size);

    // get a room pointer
    Room *room;
    // if we cant get a room then its an error
    if (!home->retrieve(room_name, room)) {
        cerr << "cant get room" << endl;
        success = false;
    } else {
        cout << "\nhow many accessory's: -> ";
        cin >> accessory_count;
        cin.clear();
        cin.ignore(size, '\n');
    }

    // loop for accessory_count or dont if we have an error
    for (int i = 0; i < accessory_count && success; ++i) {
        Accessory *data = new Accessory();

        make_accessory_data(data, temp, size);

        if (!room->append(data)) {
            cerr << "cant add accessory" << endl;
            success = false;
        }
    }

    delete[] room_name;
    delete[] temp;
}

// add rooms to the main list
void make_roooms(SmartHome *&home) {
    const int size = 1000;
    char *temp = new char[size];

    cout << "\nhow many rooms: -> ";
    int room_count;
    cin >> room_count;
    cin.ignore(size, '\n');

    for (int i = 0; i < room_count; ++i) {
        cout << "\nwhat is the name of this room\n -> ";

        fill_array_by_size(temp, size);
        home->append(temp);

        temp[0] = '\0';
    }

    delete[] temp;
}

// take user input and delete ask for node
void remove_room(SmartHome *&home) {
    const int size = 1000;
    char *temp = new char[size];

    cout << "pleas enter the room to remove\n -> ";
    fill_array_by_size(temp, size);

    if (!home->remove_room(temp)) {
        cerr << "cant remove room" << endl;
    }

    delete[] temp;
}

// remove accessory form a given room
void remove_accessory(SmartHome *&home) {
    const int size = 1000;
    char *temp = new char[size];
    char *room_name;
    char *accessory;

    cout << "pleas enter the room to find\n -> ";
    fill_array_by_size(room_name, temp, size);
    cout << "pleas enter the accessory to remove\n -> ";
    fill_array_by_size(accessory, temp, size);

    if (!home->remove_accessory(room_name, accessory)) {
        cerr << "error cant find accessory or room " << endl;
    }

    delete[] room_name;
    delete[] accessory;
    delete[] temp;
}

// display all rooms
void display_rooms(SmartHome *home) {
    cout << '\n';
    if (!home->display_rooms()) {
        cerr << "no rooms to display" << endl;
    }
}

// display accessories for a room
void display_accessories(SmartHome *home) {
    const int size = 1000;

    char *temp = new char[size];

    cout << "to print accessories pleas give a room\n -> ";
    fill_array_by_size(temp, size);

    if (!home->display_accessories(temp)) {
        cerr << "error displaying accessories" << endl;
    }

    delete[] temp;
}

// just a menu
int menu() {
    int user_input = 0;

    bool bad_input = false;

    do {
        cout << "\npleas pick one of the following"
                "\n    1) add rooms to the home"
                "\n    2) add an accessories to a room"
                "\n    3) remove a room"
                "\n    4) remove an accessory from a room"
                "\n    5) display all rooms"
                "\n    6) display all accessories in a room"
                "\n    7) display all accessories in all rooms"
                "\n    8) quit\n\n -> ";

        cin >> user_input;
        cin.clear();
        cin.ignore(1000, '\n');

        if (user_input <= 0 || user_input >= 9) {
            cout << "\npleas give a valid input\n" << endl;
            bad_input = true;
        } else {
            // to rest if we got bad input last time
            bad_input = false;
        }
    } while (bad_input);

    return user_input;
}

// call the function for the given selection
bool run_logic(SmartHome *&home, int selection) {
    bool again = true;

    // i would use something else if i knew of anything better, too bad about
    // case fall through

    // wrapper functions to the data type to take input or display properly for
    // the client
    if (selection == 1) {
        make_roooms(home);

    } else if (selection == 2) {
        make_accessorys(home);

    } else if (selection == 3) {
        remove_room(home);

    } else if (selection == 4) {
        remove_accessory(home);

    } else if (selection == 5) {
        display_rooms(home);

    } else if (selection == 6) {
        display_accessories(home);

    } else if (selection == 7) {
        home->display_accessories();

    } else if (selection == 8) {
        again = false;

    } else {
        cout << "error bad selection" << endl;
    }

    // return if we should quit or not
    return again;
}

// the starting point
int main() {
    SmartHome *home = new SmartHome();

    // get an int to use in the loop
    int selection = 0;

    cout << "welcome to the barely sorted house data thing" << endl;

    do {
        // get a user selection
        selection = menu();

        // run while user wants to
    } while (run_logic(home, selection));

    cout << "good bye" << endl;

    // call the de-constructor to cascade down the list
    delete home;

    // return success
    return 0;
}
