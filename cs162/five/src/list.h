// all functions have a comments in the relevant files

// a struct to hold todo data
struct Todo {
    Todo();
    ~Todo();

    bool read_in_data();
    void display();

    // the data used in this program
    // pointers, will become dynamic arrays
    char *name;
    char *description;
    char *due_date;

    // an integer to show the priority
    int priority;

    // the next node
    Todo *next;
};

// a struct to hold a list
struct LinkedList {
    LinkedList();
    ~LinkedList();

    void insert_order(Todo *node, Todo *current, Todo *prev);
    bool add_link();
    void build();
    void display();
    void display_priority(int filter);

    bool remove_item(char *to_remove);

    int length();
    // int length();
    int length_loop();

  private:
    void display_loop(Todo *current, int *filter);

    // the head of the list, so we dont loose in memory
    Todo *head;
    // th internal length, for easy use
    int internal_length;
};

// prototypes
void read_into_buf(char *&temp, char *&buf);
int length_recursion(Todo *node);
