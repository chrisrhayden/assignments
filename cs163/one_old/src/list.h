#include <iostream>

// forward declare these types
struct Room;
struct Accessory;

// make a node struct to holed the data
struct Node {
    // a constructor
    Node();
    // a destructor
    ~Node();
    // return true if the node is a room not an accessory
    bool isroom();
    // copy this node in to another
    bool copy(Node *&to_fill);
    // call display() ether the room or the accessory
    bool display();

    // List needs access to the data and next
    Room *room;
    Accessory *accessory;
    // the next node
    Node *next;
};

class List {
  public:
    List();
    ~List();

    // overloaded to make the correct node to give the real append
    // append a room
    bool append(char *&name);
    // append an accessory
    bool append(char *&name, char *&category, char *&status);
    // a generic append for the actual node
    bool append(Node *&new_node);

    // remove a node in  the list
    bool remove(char *name);
    // overload retrieve to get the right data
    bool retrieve(Room *&room_to_fill, char *name);
    bool retrieve(Accessory *&accessory_to_fill, char *name);

    // copy the list
    bool copy(List *&new_list);

    // call display() on each node
    bool display();

  private:
    // the first node
    Node *head;
    // the last node
    Node *tail;
};
