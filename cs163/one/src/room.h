// a struct to hold the accessory data
struct Accessory {
    Accessory();
    ~Accessory();

    // a function that will display if a room exists
    bool display();
    bool copy(Accessory *&to_fill);

    char *name;
    char *category;
    char *status;

    Accessory *next;
};

// a class to hold accessories and a room name
class Room {
  public:
    // basic con/de-structures
    Room(char *new_name);
    ~Room();

    bool append(Accessory *&to_add);
    bool remove(char *to_find);
    // copy in to a given node
    bool copy(Room *&to_fill);

    bool display_name();
    bool display_accessories();

    // make a str cmp to the room name
    bool cmp(char *to_compare);
    // return a cont pointer to the name keeping th data private, kinda
    char *name_str() const;
    void add_ord(Accessory *&to_add);

    // the room data
  private:
    char *name;
    Accessory *head;
    Accessory *tail;
};
