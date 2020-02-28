#include "meal_data.h"

// the nodes to contain th e data and connect the list
struct Node {
    Node(MealData *to_add);
    ~Node();
    bool display();

    // let the node own the data
    MealData data;
    Node *next;
};

// the class containing all the data nodes
class List {
    // public methods
  public:
    List();
    ~List();
    bool add(MealData *to_add);
    bool get(char *key, MealData *to_fill);
    bool remove(DataKey data_key, char *key, MealData *to_fill);
    bool retrieve(DataKey data_key, char *sub_str, List *meal_collect);
    bool display();
    bool is_empty();

    // private data and methods
  private:
    // this is recursive so keep it private to not have the use see node
    void display(Node *current);
    Node *head;
};
