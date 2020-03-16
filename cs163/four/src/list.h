#include "meal_data.h"

// a basic node struct so that the parent class can access data easily
struct ListNode {
    ListNode();
    ~ListNode();
    bool display();

    MealData *data;

    ListNode *next;
};

// the smart home data structure interface
class List {
  public:
    List();
    ~List();

    // actually add the node to the list
    bool append(MealData *data);

    // remove a room by name
    bool remove(char *name);
    bool display();

  private:
    ListNode *head;
    ListNode *tail;
};
