#include "meal_data.h"

struct Node {
    Node(MealData *to_add);
    ~Node();
    bool display();

    // let the node own the data
    MealData data;
    Node *next;
};

class List {
  public:
    List();
    ~List();
    bool add(MealData *to_add);
    bool get(char *key, MealData *to_fill);
    bool remove(DataKey data_key, char *key, MealData *to_fill);
    bool retrieve(DataKey data_key, char *sub_str, List *meal_collect);
    bool display();
    bool is_empty();

  private:
    bool match_data_key(DataKey data_key, char *sub_str);
    Node *head;
};
