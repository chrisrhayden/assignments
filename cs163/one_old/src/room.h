class List;

struct Accessory {
    Accessory();
    ~Accessory();
    bool add_data(char *&new_name, char *&new_category, char *&new_status);
    bool display();
    bool copy(Accessory *&new_accessory);

    char *name;
    char *category;
    char *status;
};

struct Room {
    Room();
    ~Room();
    // bool add_data(char *room_name, List *new_room);
    bool display();
    bool append(char *&name, char *&category, char *&status);
    bool copy(Room *&to_fill);

    char *name;
    List *accessories;
    int accessory_count;
};
