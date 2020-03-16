#include <cstring>
#include <iostream>
#include <mcheck.h>

#include "bst.h"

using namespace std;

int user_input_int(int start, int end) {
    bool success = false;
    int user_input = -1;

    do {
        cout << " -> ";

        cin >> user_input;
        // ignore any errors
        cin.clear();
        cin.ignore(1000, '\n');

        if (user_input < start || user_input > end) {
            cout << "bad user input" << end;
            success = false;
        } else {
            success = true;
        }
    } while (!success);

    return user_input;
}

bool test_add_to_tree(Tree *tree) {
    MealData *new_meal = new MealData();
    char temp[1000];

    cout << "what is the name of the meal ->";
    cin.get(temp, 1000, '\n');
    cin.ignore(1000, '\n');

    new_meal->name_of_meal = new char[strlen(temp)];
    strcpy(new_meal->name_of_meal, temp);

    temp[0] = '\0';

    cout << "what is the name of the venue ->";
    cin.get(temp, 1000, '\n');
    cin.ignore(1000, '\n');

    new_meal->name_of_venue = new char[strlen(temp)];
    strcpy(new_meal->name_of_venue, temp);

    temp[0] = '\0';

    cout << "what is the price ->";
    cin.get(temp, 1000, '\n');
    cin.ignore(1000, '\n');

    new_meal->approximate_price = new char[strlen(temp)];
    strcpy(new_meal->approximate_price, temp);

    temp[0] = '\0';

    cout << "what is the rating ->";
    cin.get(temp, 1000, '\n');
    cin.ignore(1000, '\n');

    new_meal->rating = new char[strlen(temp)];
    strcpy(new_meal->rating, temp);

    temp[0] = '\0';

    cout << "what is the review ->";
    cin.get(temp, 1000, '\n');
    cin.ignore(1000, '\n');

    new_meal->review = new char[strlen(temp)];
    strcpy(new_meal->review, temp);

    temp[0] = '\0';

    cout << "is the venue a restaurant (y|n) -> ";

    char user_input;

    cin >> user_input;
    cin.ignore(1000, '\n');

    if (tolower(user_input) == 'y') {
        new_meal->venue_type = Restaurant;
    } else {
        new_meal->venue_type = Cart;
    }

    tree->add(new_meal);

    delete new_meal;
    return true;
}

bool test_tree_display(Tree *tree) {
    bool success = false;
    char temp[1000];
    do {

        cout << "what meals do you want to display\n -> ";
        cin.get(temp, 1000, '\n');
        cin.clear();
        cin.ignore(1000, '\n');

        if (temp[0] == '\0') {
            cout << "bad input" << endl;
            success = false;
        } else {
            success = true;
        }
    } while (!success);

    return tree->display(temp);
}

bool test_search_tree(Tree *tree) {
    bool success = false;
    char temp[1000];
    do {

        cout << "what meal do you want to search\n -> ";
        cin.get(temp, 1000, '\n');
        cin.clear();
        cin.ignore(1000, '\n');

        if (temp[0] == '\0') {
            cout << "bad input" << endl;
            success = false;
        } else {
            success = true;
        }
    } while (!success);

    List *matches;

    tree->search_meal(temp, matches);

    if (matches) {
        cout << "\nthe found nodes are\n";
        matches->display();
        return true;
    } else {
        cout << "no matches found" << endl;
        return false;
    }
}

bool test_remove_meal(Tree *tree) {
    bool success = false;
    char meal[1000];
    char rest[1000];
    do {

        cout << "what meal do you want to remove\n -> ";
        cin.get(meal, 1000, '\n');
        cin.clear();
        cin.ignore(1000, '\n');

        if (meal[0] == '\0') {
            cout << "bad input" << endl;
            success = false;
        } else {
            success = true;
        }
    } while (!success);

    success = false;

    do {

        cout << "what is the venue that to remove from\n";
        cin.get(rest, 1000, '\n');
        cin.clear();
        cin.ignore(1000, '\n');

        if (rest[0] == '\0') {
            cout << "bad input" << endl;
            success = false;
        } else {
            success = true;
        }
    } while (!success);

    MealData *to_fill = new MealData();

    success = tree->remove(meal, rest, to_fill);

    cout << "the removed node is:\n";
    success = to_fill->display();

    delete to_fill;

    return success;
}

void test_is_efficient(Tree *tree) {
    if (tree->is_efficient()) {
        cout << "the tree is efficient" << endl;
    } else {
        cout << "the tree is not efficient" << endl;
    }
}

void test_height(Tree *tree) {
    cout << "the tree size is: " << tree->get_height() << endl;
}

bool test_tree(Tree *tree) {
    bool quit = false;
    bool success = true;

    do {

        cout << "what do you want to do:\n"
                "   1) quit\n"
                "   2) add new meal\n"
                "   3) search for meals\n"
                "   4) display some meals\n"
                "   5) display all meals\n"
                "   6) remove a meal\n"
                "   7) is efficient\n"
                "   8) height\n"

            ;

        int input = user_input_int(1, 8);

        if (input == 2) {
            success = test_add_to_tree(tree);
        } else if (input == 3) {
            success = test_search_tree(tree);
        } else if (input == 4) {
            success = test_tree_display(tree);
        } else if (input == 5) {
            success = tree->display_all();
        } else if (input == 6) {
            success = test_remove_meal(tree);
        } else if (input == 7) {
            test_is_efficient(tree);
        } else if (input == 8) {
            test_height(tree);
        } else {
            quit = true;
        }

    } while (!quit && success);

    return success;
}

int main_menu(Tree *tree) {
    char path[] = "data.txt";
    bool quit = false;
    bool success = false;

    do {
        cout << "what do you what\n"
                " 1) quit\n"
                " 2) load test data from data.txt\n"
                " 3) test tree\n";

        int input = user_input_int(1, 3);

        if (input == 2) {
            success = fill_data_from_file(tree, path);
        } else if (input == 3) {
            success = test_tree(tree);
        } else {
            quit = true;
        }

    } while (!quit);

    return success;
}

int main() {
    Tree main_tree = Tree();

    if (main_menu(&main_tree)) {
        cout << "failed to test tree" << endl;

        return 0;
    }

    return 0;
}
