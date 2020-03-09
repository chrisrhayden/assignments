struct MealData;

struct Node {
    MealData *data;
    Node *left;
    Node *right;
};

class Tree {
  public:
    Tree();
    ~Tree();
    int get_height();
    bool is_efficient();
    bool display(char *meal_name);
    bool display_all();
    bool add(MealData *new_data);
    bool remove(char *meal_name, char *restaurant);
    int remove_all();

  private:
    int remove_all(Node *current);
    Node *root;
};
