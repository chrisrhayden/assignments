#include <cstring>
#include <iostream>

#include "meal_data.h"
#include "table.h"

using namespace std;

void print_example_data_file() {
    cout << "# meal name / key, venue name, price, review, if it is a "
            "restaurant\nthe bowl$whole bowl$cheap$5 stars$its good$false\n"
            "cooked rat$a restaurant place$expensive af$3 stars$its not "
            "bad$true\nhash cakes$terrible food cart 01$cheap$2 stars$its "
            "pretty bad dont go$false\nkrabby patty's$amazing restaurant "
            "thing$cheap$2 stars$its pretty bad dont go$false\ntrash burger "
            "01$terrible food cart 03$cheap$2 stars$its pretty bad dont "
            "go$false\ntrash burger 02$terrible food cart 04$cheap$2 "
            "stars$its pretty bad dont go$false\ntrash burger 03$terrible "
            "food cart 05$cheap$2 stars$its pretty bad dont go$false\ntrash "
            "burger 04$terrible food cart 06$cheap$2 stars$its pretty bad dont "
            "go$false\ntrash burger 05$terrible food cart 07$cheap$2 "
            "stars$its pretty bad dont go$false\ntrash burger 06$terrible "
            "food cart 08$cheap$2 stars$its pretty bad dont go$false\ntrash "
            "burger 07$terrible food cart 09$cheap$2 stars$its pretty bad dont "
            "go$false\ntrash burger 08$terrible food cart 10$cheap$2 "
            "stars$its pretty bad dont go$false\ntrash burger 09$terrible "
            "food cart 11$cheap$2 stars$its pretty bad dont go$false\ntrash "
            "burger 10$terrible food cart 12$cheap$2 stars$its pretty bad dont "
            "go$false"
         << endl;
}

void print_help() {
    cout << "Welcome to the meal helper\nPleas make use of the load from  file "
            "feature.\nThe default path is PWD/data.txt\nThe format is\n meal "
            "name, venue name, price, meal rating, meal review\n and if it is "
            "a restaurant\n\nAn example would be as follows\n note that any "
            "line STARTING with a # is ignored\ncoffee$cafe cool place$2.50$5 "
            "stars$good coffee$false\n\n"
         << endl;
}

bool test_data(Table *to_test) {
    // MealData *to_display = new MealData();

    // char bowl[] = "the bowl";

    // to_test->get(bowl, to_display);

    // cout << "removed from table: \n";
    // to_display->display();
    // delete to_display;

    MealData **meals;

    char bowl[] = "the bowl";

    DataKey key = NameOfMeal;

    int len = to_test->retrieve(key, bowl, meals);

    if (!meals || len == -1) {
        cout << "bad retrieve" << endl;
        // delete[] meals;
        return false;
    }

    for (int i = 0; i < len; ++i) {
        meals[i]->display();
    }

    delete[] meals;

    return true;
}

int main() {
    bool success = true;
    const int table_size = 11;

    char path[] = "/home/chris/proj/assignments/cs163/three/data.txt";

    Table *table = new Table(table_size);

    success = fill_data_from_file(table, path);

    if (success) {
        test_data(table);
    } else {
        cout << "bad data from file" << endl;
    }

    delete table;

    return 0;
}
