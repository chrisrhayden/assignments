#include "room.h"

// a basic node struct so that the parent class can access data easily
struct Node {
    Node();
    ~Node();
    bool display();

    Room *room;
    Node *next;
};

// the smart home data structure interface
class SmartHome {
  public:
    SmartHome();
    ~SmartHome();

    // add a new node/room by the given name
    bool append(char *name);
    // actually add the node to the list
    bool append(Node *&new_node);
    // add an accessory to a given room
    bool append_accessory(char *room_to_add_to, Accessory *to_add);

    // remove a room by name
    bool remove_room(char *name);
    // remove an accessory by room name and accessory name
    bool remove_accessory(char *room_to_find, char *accessory_to_find);

    // fill a room with a given room by name
    bool retrieve(char *name, Room *&to_fill);
    // copy the whole list to another
    bool copy(SmartHome *&to_fill);
    // display all the rooms
    bool display_rooms();
    // display all the accessory for a given room
    bool display_accessories(char *room_name);
    bool display_accessories();

    // the data
  private:
    void add_ord(Node *&to_add);
    Node *head;
    Node *tail;
};
