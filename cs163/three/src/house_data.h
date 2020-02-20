struct HouseData {
    HouseData();
    ~HouseData();
    bool is_empty();
    bool display();

    char *location;
    char *size;
    char *bedrooms;
    char *distance_to_psu;
    char *notes;
};
