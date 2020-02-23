#include "meal_data.h"

class List;

class Table {
  public:
    Table(int size);
    ~Table();

    bool add(char *key, MealData *to_add);
    bool get(char *key, MealData *to_fill);
    bool remove(char *key);
    bool remove(char *key, MealData *to_fill);
    int retrieve(DataKey data_key, char *substr, MealData *meal_arry_to_fill);
    bool display_all();

  private:
    bool _remove(char *key, MealData *to_fill);
    int table_size;
    List **table;
};

bool fill_data_from_file(Table *table_to_fill, char *path);
