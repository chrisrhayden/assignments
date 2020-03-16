#include "list.h"
#include "meal_data.h"

struct Node {
    Node();
    ~Node();
    bool display();
    MealData *data;
    Node *left;
    Node *right;
};

class Tree {
  public:
    Tree();
    ~Tree();

    // user functions, or the way to use the adt
    int get_height();
    bool is_efficient();
    bool display(char *meal_name);
    bool display_all();
    bool add(MealData *new_data);
    int search_meal(char *meal_name, List *&matches);
    bool remove(char *meal_name, char *restaurant, MealData *&to_fill);
    int remove_all();

  private:
    // recursive functions made private to keep the user from having to muck
    // with the internals
    bool display(Node *current, char *meal_name);
    bool add(Node *current, MealData *new_data);
    bool remove(char *meal_name, char *restaurant, MealData *&to_fill,
                Node *&current);

    bool remove_node(Node *&current);
    int remove_all(Node *current);
    int search_meal(char *meal_name, List *&matches, Node *current);

    int get_height(Node *current);

    // internal utils
    bool display_inorder(Node *current);
    Node *leftmost_node(Node *current);
    // root data
    Node *root;
};

bool fill_data_from_file(Tree *to_fill, char *path);
