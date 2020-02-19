#include "route.h"

struct SNode {
    SNode(int array_len);
    ~SNode();
    bool add(Route *to_add);
    bool remove(Route *&to_fill);
    bool peek(Route *&to_fill);
    bool display();
    bool is_empty();
    bool is_full();

    int max_length;
    int length;

    Route *elements;
    SNode *next;
};

class Stack {
  public:
    Stack(int array_len);
    ~Stack();
    bool push(Route *to_add);
    bool pop(Route *&to_fill);
    bool peek(Route *&to_fill);
    bool is_empty();
    bool display();

  private:
    SNode *head;
    SNode *tail;
    int array_length;
};
