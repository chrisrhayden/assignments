#include "house_data.h"

struct InternalHouseData {
    InternalHouseData();
    ~InternalHouseData();
    bool copy_from_house_data(HouseData *to_add);
    bool display();
    bool is_empty();

    char *location;
    char *size;
    char *bedrooms;
    char *distance_to_psu;
    char *notes;
};

