struct Route {
    Route();
    ~Route();
    void clear();
    bool copy_into(Route *&to_fill);
    bool is_empty();
    bool display();

    char *street;
    char *length;
    char *traffic;
    char *note;
    char *construction;
};
