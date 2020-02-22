#include <iostream>

using namespace std;

#include "house_data.h"
#include "table.h"

int main() {
    const int table_size = 10;

    Table *table = new Table(table_size);

    char path[] = "/home/chris/proj/assignments/cs163/three/data.txt";

    table->fill_data_from_file(path);

    if (!table->display_all()) {
        cout << "cant display table" << endl;
    }

    delete table;

    return 0;
}
