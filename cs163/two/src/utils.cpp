#include <cstring>
#include <iostream>

using namespace std;

// get user input as an int and make sure its in a range
int user_input(int start, int stop) {
    int user_input = 0;
    bool bad_input = false;

    // set the range to be inclusive
    start -= 1;
    stop += 1;

    do {
        cout << " -> ";
        cin >> user_input;
        cin.clear();
        cin.ignore(1000, '\n');

        if (user_input <= start || user_input >= stop) {
            cerr << "bad input" << endl;
            bad_input = true;
        } else {
            bad_input = false;
        }

    } while (bad_input);

    return user_input;
}

// get user_input as a char array
void user_input_str(char *&to_fill) {
    bool bad_input = false;
    do {
        cout << " -> ";
        cin.get(to_fill, 1000, '\n');
        cin.clear();
        cin.ignore(1000, '\n');

        if (to_fill[0] == '\0') {
            bad_input = true;
        } else {
            bad_input = false;
        }

    } while (bad_input);
}

void user_input_str(char *&temp, char *&to_fill) {
    user_input_str(temp);

    to_fill = new char[strlen(temp)];
    strcpy(to_fill, temp);

    temp[0] = '\0';
}
