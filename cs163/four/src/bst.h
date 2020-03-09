struct Node {
    struct MealData *data;
    Node *left;
    Node *right;
};

class Tree {
  public:
    Tree();
    ~Tree();
    bool add();
    bool remove(char *meal_name, char *restaurant);
    int remove_all();
    bool display(char *meal_name);
    bool display_all();
    int get_height();
    bool is_efficient();

  private:
    int remove_all(Node *current);
    Node *root;
};
