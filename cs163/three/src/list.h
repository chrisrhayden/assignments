#include "internal_house_data.h"

struct Node {
    Node(long int hash, HouseData *to_add);
    ~Node();
    bool display();

    // let the node own the data
    InternalHouseData data;
    // this might be convent
    long int hash;
    Node *next;
};

class List {
  public:
    List();
    ~List();
    bool add(long int new_hash, HouseData *to_add);
    bool remove(long int hash);
    bool display();
    bool display_all();
    bool is_empty();

  private:
    Node *head;
};
