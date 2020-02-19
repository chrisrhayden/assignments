#include <cstring>
#include <iostream>

#include "list.h"
#include "room.h"

using namespace std;

void fill_array_to_size(int size, char *&dest, char *temp) {
    cin.get(temp, size, '\n');
    cin.clear();
    cin.ignore(size, '\n');

    dest = new char[strlen(temp)];
    strcpy(dest, temp);

    temp[0] = '\0';
}

void fill_array(char *&dest, char *temp) {
    return fill_array_to_size(1000, dest, temp);
}

bool make_accessories(List *&rooms, char *to_find) {
    bool success = true;

    cout << "how many accessories would yo like to add for the room\n -> ";

    int accessories_to_add;
    cin >> accessories_to_add;
    cin.ignore(1000, '\n');

    char *temp = new char[1000];

    Room *room_to_fill;

    if (!rooms->retrieve(room_to_fill, to_find)) {
        cout << "cant retrieve room" << endl;
        success = false;
    }

    for (int i = 0; i < accessories_to_add && success; ++i) {
        cout << "what is the name of the accessory\n -> ";
        char *name;
        fill_array(name, temp);

        cout << "what is the category of the accessory\n -> ";
        char *category;
        fill_array(category, temp);

        cout << "what is the status of the accessory\n -> ";
        char *status;
        fill_array(status, temp);

        if (!room_to_fill->append(name, category, status)) {
            cerr << "can append to accessories" << endl;
            success = false;
        }
    }

    delete[] temp;

    return success;
}

bool make_rooms(List *&to_fill) {
    int rooms_to_add;
    cout << "how many rooms would yo like to add\n -> ";
    cin >> rooms_to_add;
    cin.ignore(1000, '\n');

    char *temp = new char[1000];

    bool success = true;

    for (int i = 0; i < rooms_to_add && success; ++i) {
        cout << "\n\nadding new room\nwhat is the name of the room would you "
                "like to add\n -> ";
        char *name;

        fill_array(name, temp);

        to_fill->append(name);

        cout << "would yo like to add accessories\n (n|Y) -> ";
        char user_input;
        cin >> user_input;
        cin.ignore(1000, '\n');

        if (tolower(user_input) == 'y') {
            if (!make_accessories(to_fill, name)) {
                success = false;
            }
        }
    }

    delete[] temp;

    return success;
}

void pint_menu() {
    cout << "welcome the smart home thing\npleas chose one of the following\n"
            "  1) add room['s] to list\n"
            "  2) add accessory to room\n"
            "  3) remove a room\n"
            "  4) remove an accessory from a room\n"
            "  5) print all rooms (no accessories)\n"
            "  6) print all rooms (with accessories)\n"
            "  7) print room by name\n"
            "  8) print accessory from a room by name\n";
    cout << flush;
}

int main() {
    List *main_list = new List();

    make_rooms(main_list);

    main_list->display();

    delete main_list;

    return 0;
}
