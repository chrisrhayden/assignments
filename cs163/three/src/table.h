#include "meal_data.h"

// forward declare List to be used by Table
class List;

// overarching class / user interface
class Table {
    // public methods
  public:
    Table(int size);
    ~Table();

    bool add(char *key, MealData *to_add);
    bool get(char *key, MealData *to_fill);
    bool remove(char *key, MealData *to_fill);
    bool remove_by(DataKey data_key, char *key, List *meal_list);
    bool retrieve(DataKey data_key, char *sub_str, List *meal_list);
    bool display_all();

    // private data and methods
  private:
    bool _remove(DataKey data_key, char *key, MealData *to_fill);
    int table_size;
    List **table;
};

// make this prototype available to other files
bool fill_data_from_file(Table *table_to_fill, char *path);
